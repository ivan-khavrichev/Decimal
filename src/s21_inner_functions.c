#include "s21_decimal.h"

int div_greater(s21_decimal *value_1, s21_decimal *value_2, s21_decimal *result,
                int flag_switch) {
  s21_decimal null_decimal = {{0, 0, 0, 0}};
  int power_res = 0;
  int status = 0;
  int position_shift = search_first_bit(value_1) - search_first_bit(value_2);
  for (int i = 0; i < position_shift; i++) {
    shift_left(value_2);
  }
  for (int i = 0; i < position_shift + 1; i++) {
    shift_left(result);
    if (comparison_decimal(value_1, value_2) == 1 ||
        equal_decimal(value_1, value_2) == 1) {
      sub_decimal(value_1, value_2);
      result->bits[0] = (result->bits[0] | 1);
    }
    shift_left(value_1);
  }

  if (flag_switch == 0) {
    power_res = get_power(value_1) - get_power(value_2);
    if (power_res < 0) {
      power_res *= -1;
      s21_decimal tmp_decimal = *result;
      *result = null_decimal;
      mul_ten_n_times(&tmp_decimal, result, power_res);
    } else {
      result->bits[3] = result->bits[3] | (power_res << 16);
    }
    if (power_res > 28) {
      status = 2;
      *result = null_decimal;
    }
  }

  if (search_first_bit(value_1) != -1 && flag_switch == 0 && status != 3) {
    for (int i = 0; i < position_shift; i++) {
      shift_right(value_1);
      shift_right(value_2);
    }
    shift_right(value_1);

    s21_decimal tmp_result = null_decimal;
    s21_decimal tmp_decimal = null_decimal;
    div_less(value_1, value_2, &tmp_result);
    s21_add(*result, tmp_result, &tmp_decimal);
    *result = tmp_decimal;
  }

  return status;
}

int div_less(s21_decimal *value_1, s21_decimal *value_2, s21_decimal *result) {
  s21_decimal decimal_1 = *value_1;
  s21_decimal decimal_2 = *value_2;
  s21_decimal null_decimal = {{0, 0, 0, 0}};
  s21_decimal tmp_decimal = null_decimal;
  s21_decimal tmp_result = null_decimal;
  int power_1 = get_power(value_1);
  int power_2 = get_power(value_2);
  mul_ten_n_times(&decimal_1, &tmp_decimal, power_2);
  write_power_and_sign(&decimal_2, 0, 0);
  decimal_1 = tmp_decimal;
  tmp_decimal = null_decimal;
  int position_shift = 0;
  int power_res = 0;
  int status = 0;
  int flag_switch = 1;
  while (search_first_bit(&decimal_1) != -1 && power_res < 28 && power_1 < 28 &&
         power_2 < 28) {
    tmp_result = *result;
    *result = null_decimal;
    mul_ten(&tmp_result, result);
    tmp_decimal = null_decimal;
    if (comparison_decimal(&decimal_1, &decimal_2) != 1 ||
        equal_decimal(&decimal_1, &decimal_2) != 1) {
      while (s21_is_less(decimal_1, decimal_2) == 1 && power_res < 28) {
        mul_ten(&decimal_1, &tmp_decimal);
        decimal_1 = tmp_decimal;
        tmp_decimal = null_decimal;
        power_res++;
      }
    }
    tmp_result = null_decimal;
    position_shift =
        search_first_bit(&decimal_1) - search_first_bit(&decimal_2);
    div_greater(&decimal_1, &decimal_2, &tmp_result, flag_switch);
    for (int i = 0; i < position_shift; i++) {
      shift_right(&decimal_1);
      shift_right(&decimal_2);
    }
    shift_right(&decimal_1);
    add_decimal(&tmp_result, result);
    tmp_decimal = *result;
  }
  power_res += power_1;
  result->bits[3] = result->bits[3] | (power_res << 16);
  if (power_res > 28) {
    status = 1;
    *result = null_decimal;
  }
  return status;
}

void rounding_in_sub(s21_decimal *result, s21_decimal *mantissa_full,
                     int norm_power) {
  s21_decimal half = {{5, 0, 0, (1 << 16)}};
  power_normalization_for_arithmetic(get_power(&half), get_power(mantissa_full),
                                     &half, mantissa_full);
  write_power_and_sign(mantissa_full, norm_power, 0);
  if (equal_decimal(mantissa_full, &half) == 1) {
    get_bit(result, 0, 0);
    // а при четном не делаем ничего
  } else if (comparison_decimal(mantissa_full, &half) == 1) {
    add_bit(result, 0, 0);
  }  // если < 0.5 ничего не делаем
}

// работа со значениями разных знаков в add
void different_signs_sub(s21_decimal *value_1, s21_decimal *value_2,
                         int power_1, int power_2, s21_decimal *result,
                         int sign_1, int *status) {
  write_power_and_sign(value_1, power_1, 0);
  write_power_and_sign(value_2, power_2, 0);
  *status = s21_add(*value_1, *value_2, result);
  write_power_and_sign(result, get_power(result), sign_1);
}

void transfer_case(s21_decimal *int_part_1, s21_decimal *int_part_2,
                   int *norm_power, s21_decimal *mantissa_1,
                   s21_decimal *mantissa_2, int *overflow_round, int sign,
                   s21_decimal *int_part_full, s21_decimal *mantissa_full) {
  s21_decimal zero_decimal = {{0, 0, 0, 0}};
  sub_decimal(int_part_1, int_part_2);
  sub_bit(int_part_1, 0, 0);
  int diff_powers =
      mul_ten_n_times_with_overflow(int_part_1, int_part_full, norm_power);
  transfer(mantissa_1, mantissa_2, *norm_power, mantissa_full);
  if (diff_powers != 0) {
    s21_decimal tmp_mant = *mantissa_full;
    s21_decimal mant_rounding = *mantissa_full;
    s21_decimal tmp_mantissa_rounding_sub = *mantissa_full;
    s21_decimal tmp_mantissa_rounding_mul_10 = zero_decimal;
    *mantissa_full = zero_decimal;
    div_ten_n_times(&tmp_mant, mantissa_full, diff_powers);
    *norm_power = *norm_power - diff_powers;
    mul_ten_n_times_with_overflow(mantissa_full, &tmp_mantissa_rounding_mul_10,
                                  &diff_powers);
    sub_decimal(&tmp_mantissa_rounding_sub, &tmp_mantissa_rounding_mul_10);
    s21_decimal tmp_mant_res_div = zero_decimal;
    div_ten_n_times(&tmp_mantissa_rounding_sub, &tmp_mant_res_div,
                    diff_powers - 1);
    s21_decimal five = {{5, 0, 0, 0}};
    if (comparison_decimal(&tmp_mant_res_div, &five) == 1 ||
        equal_decimal(&tmp_mant_res_div, &five) == 1) {
      add_bit(mantissa_full, 0, 0);
    }
    if (s21_is_equal(zero_decimal, *mantissa_full)) {
      *mantissa_full = mant_rounding;
      *overflow_round = 1;
    }
  }
  if (*overflow_round != 1) {
    if (add_decimal_with_overflow(mantissa_full, int_part_full) == 0) {
      s21_decimal tmp_int = *int_part_full;
      *overflow_round = 1;
      *int_part_full = tmp_int;
    }
  }
  write_power_and_sign(int_part_full, *norm_power, sign);
}

void simple_case(s21_decimal *int_part_1, s21_decimal *int_part_2,
                 int *norm_power, s21_decimal *mantissa_1,
                 s21_decimal *mantissa_2, int *overflow_round, int sign,
                 s21_decimal *int_part_full, s21_decimal *mantissa_full) {
  sub_decimal(int_part_1, int_part_2);
  int diff_powers =
      mul_ten_n_times_with_overflow(int_part_1, int_part_full, norm_power);
  sub_decimal(mantissa_1, mantissa_2);
  if (diff_powers != 0) {
    div_ten_n_times(mantissa_1, mantissa_full, diff_powers);
    *norm_power = *norm_power - diff_powers;
  } else {
    mantissa_full = mantissa_1;
  }
  // складываем дробную и целую части, записываем степень
  if (add_decimal_with_overflow(mantissa_full, int_part_full) == 0) {
    *overflow_round = 1;
  }
  write_power_and_sign(int_part_full, *norm_power, sign);
}

void status_out(int norm_power, int overflow, int sign_1, int *status,
                s21_decimal *result) {
  s21_decimal zero_decimal = {{0, 0, 0, 0}};
  if (norm_power > 28) {
    *status = 2;
  }
  if (overflow == 1 && sign_1 == 1) {
    *status = 2;
    *result = zero_decimal;
  } else if (overflow == 1 && sign_1 == 0) {
    *status = 1;
    *result = zero_decimal;
  }
}

void rounding_in_add(s21_decimal *result, s21_decimal *mantissa_2,
                     int norm_power, int *overflow) {
  s21_decimal half = {{5, 0, 0, (1 << 16)}};
  write_power_and_sign(mantissa_2, norm_power, 0);
  if (s21_is_equal(*mantissa_2, half) == 1) {
    if (get_bit(result, 0, 0) == 1) {
      if (add_bit(result, 0, 0) == 0) {
        *overflow = 1;
      }
    }  // а при четном не делаем ничего
  } else if (s21_is_greater(*mantissa_2, half) == 1) {
    if (add_bit(result, 0, 0) == 0) {
      *overflow = 1;
    }
  }  // если < 0.5 ничего не делаем
}

void different_signs_add(s21_decimal *value_1, s21_decimal *value_2,
                         int power_1, int power_2, s21_decimal *result,
                         int sign_1, int sign_2, int *status) {
  write_power_and_sign(value_1, power_1, 0);  // скорее всего можно убрать
  write_power_and_sign(value_2, power_2, 0);
  int first_is_bigger = s21_is_greater(*value_1, *value_2);
  *status = s21_sub(*value_1, *value_2, result);
  if (first_is_bigger == 1) {
    write_power_and_sign(result, get_power(result), sign_1);
  } else {
    write_power_and_sign(result, get_power(result), sign_2);
  }
}

void bringing_an_answer(s21_decimal *result) {
  s21_decimal zero_decimal = {{0, 0, 0, 0}};
  s21_decimal res_mantissa = {{0, 0, 0, 0}};
  get_mantissa(*result, &res_mantissa);
  if (test_decimal(res_mantissa, zero_decimal) == 0) {
    s21_decimal tmp_result = *result;
    s21_truncate(tmp_result, result);
  }
}

int mul_ten_n_times_with_overflow(s21_decimal *value, s21_decimal *result,
                                  int *norm_power) {
  int num_of_mul_tens = 0;
  int diff_powers = 0;
  num_of_mul_tens = mul_ten_n_times(value, result, *norm_power);
  diff_powers = *norm_power - num_of_mul_tens;
  return diff_powers;
}

int transfer(s21_decimal *mant_1, s21_decimal *mant_2, int norm_power,
             s21_decimal *mantissa_full) {
  int pow = norm_power;
  int num_of_mul_tens = 0;
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal rank_int = {{0, 0, 0, 0}};
  num_of_mul_tens = mul_ten_n_times_with_overflow(&one, &rank_int, &pow);
  add_decimal(&rank_int, mant_1);
  sub_decimal(mant_1, mant_2);
  *mantissa_full = *mant_1;

  return num_of_mul_tens;
}

int power_normalization_for_arithmetic(int power_1, int power_2,
                                       s21_decimal *value_1,
                                       s21_decimal *value_2) {
  int norm_power = 0;
  int overflow_exit = 30;
  if (power_1 > power_2) {
    norm_power = power_1;
    if (power_normalization(value_2, power_1, power_1 - power_2) == 0) {
      norm_power = overflow_exit;
    }
  } else if (power_2 > power_1) {
    norm_power = power_2;
    if (power_normalization(value_1, power_2, power_2 - power_1) == 0) {
      norm_power = overflow_exit;
    }
  } else if (power_1 == power_2) {
    norm_power = power_1;
    if (power_normalization(value_1, power_2, power_2 - power_1) == 0) {
      norm_power = overflow_exit;
    }
  }
  return norm_power;
}

void check_diff_pow(int diff_pow, int *norm_pow, s21_decimal *mantissa_2,
                    s21_decimal *mantissa_full, int *overflow,
                    int *overflow_round) {
  if (diff_pow != 0 && *norm_pow != 0) {
    div_ten_n_times(mantissa_2, mantissa_full, diff_pow);
    *norm_pow = *norm_pow - diff_pow;
    *overflow_round = 1;
    *overflow = 0;
  } else if (diff_pow == 0) {  //нормальный случай
    *mantissa_full = *mantissa_2;
    *overflow_round = 0;
    *overflow = 0;
  }
}

void trunc_and_get_mantissa(s21_decimal value_1, s21_decimal value_2,
                            s21_decimal *int_part_1, s21_decimal *int_part_2,
                            s21_decimal *mantissa_1, s21_decimal *mantissa_2) {
  // сравниваем целые части
  s21_truncate(value_1, int_part_1);
  s21_truncate(value_2, int_part_2);
  // получаем дробные части
  get_mantissa(value_1, mantissa_1);
  get_mantissa(value_2, mantissa_2);
}

int mul_ten_n_times(s21_decimal *value, s21_decimal *result, int n) {
  int status = 1;
  s21_decimal tmp_dec = *value;
  s21_decimal null_decimal = {{0, 0, 0, 0}};
  int i = 0;
  while (i < n && status != 0) {
    status = mul_ten(&tmp_dec, result);
    tmp_dec = *result;
    *result = null_decimal;
    i++;
  }
  *result = tmp_dec;
  if (status == 0) {
    i--;
  }
  return i;
}

void write_power_and_sign(s21_decimal *value, int power, int sign) {
  value->bits[3] = 0;
  unsigned int tmp_bit = sign << 31;
  value->bits[3] = power << 16;
  value->bits[3] += tmp_bit;
}

int power_normalization(s21_decimal *value, int power, int final_power) {
  s21_decimal result = {0};
  s21_decimal tmp_decimal = *value;
  int status = 1;
  int flag = 1;
  int i = 0;
  while (i < final_power && status != 0) {
    status = mul_ten(value, &result);
    add_bit(value, 16, 3);
    *value = result;
    i++;
  }
  write_power_and_sign(value, 0, get_sign(value));
  value->bits[3] = value->bits[3] | (power << 16);
  check_overflow(value, &flag);
  if (status == 0) {
    flag = 0;
    *value = tmp_decimal;
  }
  return flag;
}

void get_mantissa(s21_decimal value, s21_decimal *mantissa) {
  s21_decimal decimal_1 = {0};
  s21_decimal decimal_2 = {0};
  s21_decimal null_decimal = {{0, 0, 0, 0}};
  *mantissa = value;
  int power = get_power(&value);
  s21_truncate(value, &decimal_1);
  for (int i = 0; i < power; i++) {
    mul_ten(&decimal_1, &decimal_2);
    decimal_1 = decimal_2;
    decimal_2 = null_decimal;
  }
  sub_decimal(mantissa, &decimal_1);
  write_power_and_sign(mantissa, 0, 0);
}

int mul_ten(s21_decimal *value, s21_decimal *result) {
  int status = 1;
  s21_decimal tmp_dec = *value;
  *result = tmp_dec;
  shift_left(&tmp_dec);
  for (int i = 0; i < 3; i++) {
    shift_left(result);
  }
  add_decimal(&tmp_dec, result);
  check_overflow(result, &status);
  if (status == 0) {
    *result = *value;
  }
  return status;
}

int div_ten_n_times(s21_decimal *value, s21_decimal *result, int n) {
  int status = 1;
  s21_decimal tmp_dec = *value;
  s21_decimal null_decimal = {{0, 0, 0, 0}};
  for (int i = 0; i < n; i++) {
    status = div_ten(&tmp_dec, result);
    if (status == 0) {
      break;
    }
    tmp_dec = *result;
    *result = null_decimal;
  }
  *result = tmp_dec;
  return get_power(result);
}

int div_ten(s21_decimal *value, s21_decimal *result) {
  int status = 1;
  int position = search_first_bit(value) - 3;
  s21_decimal divisible = *value;
  s21_decimal ten = {{10, 0, 0, 0}};
  for (int i = 0; i < position; i++) {
    shift_left(&ten);
  }
  for (int i = 0; i < position + 1; i++) {
    shift_left(result);
    if (comparison_decimal(&divisible, &ten) == 1 ||
        equal_decimal(&divisible, &ten) == 1) {
      sub_decimal(&divisible, &ten);
      result->bits[0] = (result->bits[0] | 1);
    }
    shift_left(&divisible);
  }
  check_overflow(result, &status);
  return status;
}

int add_decimal(s21_decimal *value_1, s21_decimal *value_2) {
  int status = 1;
  int bit = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 32; j++) {
      bit = get_bit(value_1, j, i);
      if (bit == 1) {
        status = add_bit(value_2, j, i);
        if (status == 0) {
          i = 4;
          break;
        }
      }
    }
  }
  return status;
}

int add_decimal_with_overflow(s21_decimal *value_1, s21_decimal *value_2) {
  s21_decimal tmp_res1 = {{0, 0, 0, 0}};
  s21_decimal tmp_res2 = {{0, 0, 0, 0}};
  s21_decimal tmp_val2 = *value_2;
  int status = 1;
  int bit = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 32; j++) {
      bit = get_bit(value_1, j, i);
      if (bit == 1) {
        status = add_bit(value_2, j, i);
        if (status == 0) {
          div_ten(value_1, &tmp_res1);
          div_ten(&tmp_val2, &tmp_res2);
          add_decimal(&tmp_res1, &tmp_res2);
          *value_2 = tmp_res2;
          i = 4;
          break;
        }
      }
    }
  }
  return status;
}

void sub_decimal(s21_decimal *value_1, s21_decimal *value_2) {
  int bit = 0;
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 32; j++) {
      bit = get_bit(value_2, j, i);
      if (bit == 1) {
        sub_bit(value_1, j, i);
      }
    }
  }
}

int get_sign(s21_decimal *value) {
  int sign = (value->bits[LAST_INT] & MASK_SIGN) >> LAST_BIT;
  return sign;
}

int get_power(s21_decimal *value) {
  int power = (value->bits[3] & MASK_POWER) >> 16;
  return power;
}

int add_bit(s21_decimal *value, int position, int elem) {
  int bit = 0;
  int flag = 1;
  for (int i = elem; i < LAST_INT + 1; i++) {
    for (int j = position; j < LAST_BIT + 1; j++, position++) {
      bit = get_bit(value, position, elem);
      if (bit == 1) {
        invers_bit(value, position, elem);
      } else {
        invers_bit(value, position, elem);
        i = 4;
        break;
      }
    }
    position = 0;
    elem++;
  }
  check_overflow(value, &flag);
  return flag;
}

int sub_bit(s21_decimal *value, int position, int elem) {
  int bit = 0;
  int flag = 1;
  if (search_first_bit(value) != -1) {
    for (int i = elem; i < LAST_INT; i++) {
      for (int j = position; j < LAST_BIT + 1; j++, position++) {
        bit = get_bit(value, position, elem);
        if (bit == 0) {
          invers_bit(value, position, elem);
        } else {
          invers_bit(value, position, elem);
          i = 3;
          break;
        }
      }
      position = 0;
      elem++;
    }
  } else {
    flag = 0;
  }
  return flag;
}

void shift_left(s21_decimal *value) {
  int last_bit = 0;
  for (int i = 2; i > -1; i--) {
    last_bit = (value->bits[i] & MASK_CHECK_SHIFT) >> LAST_BIT;
    if (last_bit == 0) {
      value->bits[i] = value->bits[i] << 1;
    } else {
      value->bits[i + 1] = value->bits[i + 1] | 1;
      value->bits[i] = (value->bits[i] & MASK_SHIFT) << 1;
    }
  }
}

void shift_right(s21_decimal *value) {
  int first_bit = 0;
  for (int i = 0; i < 3; i++) {
    first_bit = get_bit(value, 0, i);
    if (first_bit == 0 || i == 0) {
      value->bits[i] = value->bits[i] >> 1;
    } else {
      value->bits[i - 1] = value->bits[i - 1] | MASK_CHECK_SHIFT;
      value->bits[i] = value->bits[i] >> 1;
    }
  }
}

void check_overflow(s21_decimal *value, int *flag) {
  int overflow = (MASK_LOW_WORLD & value->bits[LAST_INT]);
  if (overflow > 0) {
    *flag = 0;
  }
}

int equal_decimal(s21_decimal *value_1, s21_decimal *value_2) {
  int flag = 1;
  int bit_value_1 = 0;
  int bit_value_2 = 0;
  for (int i = 0; i < LAST_INT; i++) {
    for (int j = 0; j < LAST_BIT + 1; j++) {
      bit_value_1 = get_bit(value_1, j, i);
      bit_value_2 = get_bit(value_2, j, i);
      if (bit_value_1 != bit_value_2) {
        flag = 0;
        i = 4;
        break;
      }
    }
  }
  return flag;
}

int comparison_decimal(s21_decimal *value_1, s21_decimal *value_2) {
  int flag = 0;
  int bit_value_1 = 0;
  int bit_value_2 = 0;
  for (int i = 0; i < LAST_INT; i++) {
    for (int j = 0; j < LAST_BIT + 1; j++) {
      bit_value_1 = get_bit(value_1, j, i);
      bit_value_2 = get_bit(value_2, j, i);
      if (bit_value_1 > bit_value_2) {
        flag = 1;
      } else if (bit_value_1 < bit_value_2) {
        flag = 0;
      }
    }
  }
  return flag;
}

int search_first_bit(s21_decimal *value) {
  int position = 95;
  for (int i = 2; i > -1; i--) {
    for (int j = 31; j > -1; j--) {
      if (get_bit(value, j, i) == 1) {
        i = -1;
        break;
      } else {
        position--;
      }
    }
  }
  return position;
}

void invers_bit(s21_decimal *value, int position, int elem) {
  value->bits[elem] = value->bits[elem] ^ (1 << position);
}

int get_bit(s21_decimal *value, int position, int elem) {
  int result = 0;
  if ((value->bits[elem] & (1 << position)) == 0) {
    result = 0;
  } else {
    result = 1;
  }
  return result;
}

void print_decimal(int decimal[32][4]) {
  for (int i = 0; i < 4; i++) {
    printf("bits[%d]", i);
    for (int j = 0; j < 32; j++) {
      if (j % 4 == 0) {
        printf(" ");
      }
      printf("%d", decimal[j][i]);
    }
    printf("\n");
  }
}

void convert_and_print_decimal(s21_decimal value) {
  int decimal_convert[32][4] = {0};
  unsigned int num = 0;
  unsigned int quo = 0;
  int bit = 0;
  for (int i = 0; i < 3; i++) {
    num = value.bits[i];
    for (int j = 31; j > -1; j--) {
      quo = num / 2;
      bit = num - quo * 2;
      decimal_convert[j][i] = bit;
      num = quo;
    }
  }

  num = (value.bits[3] & MASK_LOW_WORLD);
  for (int j = 31; j > 15; j--) {
    quo = num / 2;
    bit = num - quo * 2;
    decimal_convert[j][3] = bit;
    num = quo;
  }

  num = (value.bits[3] & MASK_POWER) >> 16;
  for (int j = 15; j > 7; j--) {
    quo = num / 2;
    bit = num - quo * 2;
    decimal_convert[j][3] = bit;
    num = quo;
  }

  decimal_convert[0][3] = ((value.bits[3] & MASK_SIGN) >> 31);
  print_decimal(decimal_convert);
}

int test_decimal(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0;
  int bit_value_1 = 0;
  int bit_value_2 = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 32; j++) {
      bit_value_1 = get_bit(&value_1, j, i);
      bit_value_2 = get_bit(&value_2, j, i);
      if (bit_value_1 != bit_value_2) {
        flag = 1;
        i = 4;
        break;
      }
    }
  }
  return flag;
}
