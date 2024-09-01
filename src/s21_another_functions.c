#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int status = 0;
  if (result == NULL || get_power(&value) > 28) {
    status = 1;
  } else {
    s21_decimal null_decimal = {{0, 0, 0, 0}};
    int sign = get_sign(&value);
    int power = get_power(&value);
    *result = null_decimal;
    if (power != 0 && search_first_bit(&value) != -1) {
      if (sign == 0) {
        s21_truncate(value, result);
      } else {
        s21_truncate(value, result);
        add_bit(result, 0, 0);
      }
    } else if (search_first_bit(&value) == -1) {
      *result = value;
      write_power_and_sign(result, 0, 0);
    } else {
      *result = value;
    }
  }
  return status;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int status = 0;
  if (result == NULL || get_power(&value) > 28) {
    status = 1;
  } else {
    s21_decimal null_decimal = {{0, 0, 0, 0}};
    s21_decimal decimal = null_decimal;
    s21_decimal mantissa = null_decimal;
    s21_decimal five = {{5, 0, 0, 0}};
    *result = null_decimal;
    int power = get_power(&value);
    if (power != 0 && search_first_bit(&value) != -1) {
      for (int i = 0; i < power - 1; i++) {
        mul_ten(&five, result);
        five = *result;
        *result = null_decimal;
      }
      get_mantissa(value, &mantissa);
      s21_truncate(value, &decimal);
      if (s21_is_less(mantissa, five) == 1 ||
          (s21_is_equal(mantissa, five) == 1 && get_bit(&decimal, 0, 0) == 0)) {
        *result = decimal;
      } else if (s21_is_greater(mantissa, five) == 1 ||
                 (s21_is_equal(mantissa, five) == 1 &&
                  get_bit(&decimal, 0, 0) == 0)) {
        *result = decimal;
        add_bit(result, 0, 0);
      }
    } else if (search_first_bit(&value) == -1) {
      *result = value;
      write_power_and_sign(result, 0, 0);
    } else {
      *result = value;
    }
  }
  return status;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int status = 0;
  if (result == NULL || get_power(&value) > 28) {
    status = 1;
  } else {
    s21_decimal decimal = value;
    s21_decimal null_decimal = {{0, 0, 0, 0}};
    *result = null_decimal;
    int power = get_power(&value);
    int sign = get_sign(&value);
    for (int i = 0; i < power; i++) {
      div_ten(&decimal, result);
      decimal = *result;
      *result = null_decimal;
    }
    *result = decimal;
    write_power_and_sign(result, 0, sign);
  }
  return status;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int status = 0;
  if (result == NULL || get_power(&value) > 28) {
    status = 1;
  } else {
    s21_decimal null_decimal = {{0, 0, 0, 0}};
    *result = null_decimal;
    *result = value;
    if (search_first_bit(&value) != -1) {
      invers_bit(result, 31, 3);
    } else {
      write_power_and_sign(result, 0, 0);
    }
  }
  return status;
}
