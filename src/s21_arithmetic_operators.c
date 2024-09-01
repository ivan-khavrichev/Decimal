#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal zero_decimal = {{0, 0, 0, 0}};
  int status = 0;
  int overflow = 0;
  int overflow_round = 0;
  // получаем знаки децималов
  int sign_1 = get_sign(&value_1);
  int sign_2 = get_sign(&value_2);
  // получаем степени значений и нормализуем значения
  int power_1 = get_power(&value_1);
  int power_2 = get_power(&value_2);
  int norm_power = 0;

  if (sign_1 == sign_2) {
    // инициализируем децималы для целых и дробных частей
    s21_decimal int_part_1 = zero_decimal;
    s21_decimal int_part_2 = zero_decimal;
    s21_decimal mantissa_1 = zero_decimal;
    s21_decimal mantissa_2 = zero_decimal;
    s21_decimal int_part_full = zero_decimal;
    s21_decimal mantissa_full = zero_decimal;
    trunc_and_get_mantissa(value_1, value_2, &int_part_1, &int_part_2,
                           &mantissa_1, &mantissa_2);
    // нормализация - величина, требуемая степень, разница между требуемой
    // степенью и имеющейся
    norm_power = power_normalization_for_arithmetic(power_1, power_2,
                                                    &mantissa_1, &mantissa_2);
    // проверяем переполнение
    if (add_decimal(&int_part_1, &int_part_2) == 0) {
      overflow = 1;
    }
    if (overflow == 0) {
      if (add_decimal(&mantissa_1, &mantissa_2) == 0) {
        overflow_round = 1;
      }

      // домножаем целую часть на 10^norm_power
      int diff_powers = mul_ten_n_times_with_overflow(
          &int_part_2, &int_part_full, &norm_power);
      check_diff_pow(diff_powers, &norm_power, &mantissa_2, &mantissa_full,
                     &overflow, &overflow_round);

      // складываем дробную и целую части, записываем степень
      if (add_decimal(&mantissa_full, &int_part_full) == 0) {
        overflow_round = 1;
        overflow = 0;
      }
      write_power_and_sign(&int_part_full, norm_power, sign_1);
      *result = int_part_full;
      // приведение ответа
      bringing_an_answer(result);

      // в сабе отличаются функции сравнения: уточнить
      if (overflow_round == 1) {
        rounding_in_add(result, &mantissa_2, norm_power, &overflow);
      }
    }
    status_out(norm_power, overflow, sign_1, &status, result);

  } else {  // если 1+ 2-
    different_signs_add(&value_1, &value_2, power_1, power_2, result, sign_1,
                        sign_2, &status);
  }

  return status;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal zero_decimal = {{0, 0, 0, 0}};
  // получаем степени значений и нормализуем значения
  int status = 0;
  int power_1 = get_power(&value_1);
  int power_2 = get_power(&value_2);
  // получаем знаки децималов
  int sign_1 = get_sign(&value_1);
  int sign_2 = get_sign(&value_2);
  int norm_power = 0;
  if (power_1 > 29 || power_2 > 29) {
    status = 1;
  }
  int overflow_round = 0;
  int inverted_sign = 0;
  if (sign_1 == sign_2) {
    inverted_sign = (sign_1 == 0) ? 1 : 0;
    s21_decimal int_part_1 = zero_decimal;
    s21_decimal int_part_2 = zero_decimal;
    s21_decimal mantissa_1 = zero_decimal;
    s21_decimal mantissa_2 = zero_decimal;
    s21_decimal abs_val_1 = value_1;
    write_power_and_sign(&abs_val_1, power_1, 0);
    s21_decimal abs_val_2 = value_2;
    write_power_and_sign(&abs_val_2, power_2, 0);

    int first_val_is_bigger = s21_is_greater(abs_val_1, abs_val_2);
    trunc_and_get_mantissa(abs_val_1, abs_val_2, &int_part_1, &int_part_2,
                           &mantissa_1, &mantissa_2);
    write_power_and_sign(&mantissa_1, power_1, 0);
    norm_power = power_normalization_for_arithmetic(power_1, power_2,
                                                    &mantissa_1, &mantissa_2);
    // сравниваем дробные части
    int first_mantissa_is_bigger =
        s21_is_greater_or_equal(mantissa_1, mantissa_2);

    s21_decimal int_part_full = zero_decimal;
    s21_decimal mantissa_full = zero_decimal;

    if (first_val_is_bigger == 1 && first_mantissa_is_bigger == 1) {
      simple_case(&int_part_1, &int_part_2, &norm_power, &mantissa_1,
                  &mantissa_2, &overflow_round, sign_1, &int_part_full,
                  &mantissa_full);
    } else if (first_val_is_bigger == 1 && first_mantissa_is_bigger == 0) {
      transfer_case(&int_part_1, &int_part_2, &norm_power, &mantissa_1,
                    &mantissa_2, &overflow_round, sign_1, &int_part_full,
                    &mantissa_full);
    } else if (first_val_is_bigger == 0 && first_mantissa_is_bigger == 1) {
      transfer_case(&int_part_2, &int_part_1, &norm_power, &mantissa_2,
                    &mantissa_1, &overflow_round, inverted_sign, &int_part_full,
                    &mantissa_full);
    } else if (first_val_is_bigger == 0 && first_mantissa_is_bigger == 0) {
      simple_case(&int_part_2, &int_part_1, &norm_power, &mantissa_2,
                  &mantissa_1, &overflow_round, inverted_sign, &int_part_full,
                  &mantissa_full);
    }

    *result = int_part_full;

    if (overflow_round == 1) {
      rounding_in_sub(result, &mantissa_full, norm_power);
    }

    // приведение ответа
    s21_decimal res_mantissa = {{0, 0, 0, 0}};
    get_mantissa(*result, &res_mantissa);
    if (status == 1 && sign_1 == 1) {  // если имеем переполнение - чекаем знаки
      status = 1;
      *result = zero_decimal;

    } else if (status == 1 && sign_1 == 0) {
      *result = zero_decimal;
      status = 2;
    }

    if (test_decimal(res_mantissa, zero_decimal) == 0) {
      s21_decimal tmp_result = *result;
      s21_truncate(tmp_result, result);
    }
  } else if (sign_1 == 0 && sign_2 == 1) {  // если 1+ 2-

    different_signs_sub(&value_1, &value_2, power_1, power_2, result, sign_1,
                        &status);

  } else if (sign_1 == 1 && sign_2 == 0) {  // если 1- 2+

    different_signs_sub(&value_1, &value_2, power_1, power_2, result, sign_1,
                        &status);
    if (status == 1) {
      *result = zero_decimal;
      status = 2;
    }
  }

  return status;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int err_code = OK;

  int power_1 = get_power(&value_1);
  int power_2 = get_power(&value_2);
  int power_result = power_1 + power_2;

  // Multiplying
  int overflow = 1;
  s21_decimal null_decimal = {{0, 0, 0, 0}};
  *result = null_decimal;

  for (int i = 2; i >= 0; i--) {
    for (int j = 31; j >= 0; j--) {
      shift_left(result);
      if (get_bit(&value_2, j, i)) {
        overflow = add_decimal_with_overflow(&value_1, result);
        if (!overflow) {
          s21_decimal tmp = *result;
          div_ten(&tmp, result);
          power_result -= 1;
          if (power_result > MAX_POW) {
            // OVERFLOW EXIT
            err_code = OVERFLOW_DEC;
          }
        }
      }
    }
  }

  // Get sign and replace result's one:
  if (get_sign(&value_1) == get_sign(&value_2)) {
    write_power_and_sign(result, power_result, 0);
  } else {
    write_power_and_sign(result, power_result, 1);
  }

  check_overflow(result, &err_code);

  return err_code;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int status = 0;
  if (result != NULL) {
    s21_decimal *decimal_1 = &value_1;
    s21_decimal *decimal_2 = &value_2;
    s21_decimal null_decimal = {{0, 0, 0, 0}};
    *result = null_decimal;
    int sign_res = 0;
    if (search_first_bit(decimal_2) != -1) {
      int flag_switch = 0;
      int sign_1 = get_sign(decimal_1);
      int sign_2 = get_sign(decimal_2);
      int power_1 = get_power(decimal_1);
      int power_2 = get_power(decimal_2);
      if (sign_1 != sign_2) {
        sign_res = 1;
        write_power_and_sign(decimal_1, power_1, 0);
        write_power_and_sign(decimal_2, power_2, 0);
      }
      if (s21_is_greater_or_equal(*decimal_1, *decimal_2) == 1) {
        status = div_greater(decimal_1, decimal_2, result, flag_switch);
      } else {
        status = div_less(decimal_1, decimal_2, result);
      }
    } else {
      status = 3;
    }
    if (status == 0) {
      result->bits[3] = result->bits[3] | (sign_res << 31);
    }
  }
  return status;
}
