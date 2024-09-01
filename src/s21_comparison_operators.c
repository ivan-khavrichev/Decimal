#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int status = 0;
  if (s21_is_equal(value_1, value_2) != 1) {
    int sign_1 = get_sign(&value_1);
    int sign_2 = get_sign(&value_2);
    if (sign_1 > sign_2) {
      status = 1;
    } else if (sign_1 == sign_2) {
      int power_1 = get_power(&value_1);
      int power_2 = get_power(&value_2);
      if ((power_1 - power_2) > 0) {
        power_normalization(&value_2, power_1, (power_1 - power_2));
      } else if ((power_1 - power_2) < 0) {
        power_normalization(&value_1, power_2, (power_2 - power_1));
      }
      s21_decimal null_decimal = {{0, 0, 0, 0}};
      s21_decimal decimal_1 = null_decimal;
      s21_decimal decimal_2 = null_decimal;
      s21_truncate(value_1, &decimal_1);
      s21_truncate(value_2, &decimal_2);
      if (equal_decimal(&decimal_1, &decimal_2)) {
        decimal_1 = null_decimal;
        decimal_2 = null_decimal;
        get_mantissa(value_1, &decimal_1);
        get_mantissa(value_2, &decimal_2);
        if (!comparison_decimal(&decimal_1, &decimal_2) && !sign_1) {
          status = 1;
        } else if ((comparison_decimal(&decimal_1, &decimal_2) && sign_1)) {
          status = 1;
        }
      } else if (!comparison_decimal(&decimal_1, &decimal_2) && !sign_1) {
        status = 1;
      } else if ((comparison_decimal(&decimal_1, &decimal_2) && sign_1)) {
        status = 1;
      }
    }
  }
  return status;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int status = 0;
  if (s21_is_less(value_1, value_2) == 1 ||
      s21_is_equal(value_1, value_2) == 1) {
    status = 1;
  }
  return status;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  int status = 0;
  if (s21_is_less(value_1, value_2) != 1 &&
      s21_is_equal(value_1, value_2) != 1) {
    status = 1;
  }
  return status;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int status = 0;
  if (s21_is_greater(value_1, value_2) == 1 ||
      s21_is_equal(value_1, value_2) == 1) {
    status = 1;
  }
  return status;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  s21_decimal null_decimal = {{0, 0, 0, 0}};
  s21_decimal decimal_1 = null_decimal;
  s21_decimal decimal_2 = null_decimal;
  int status = 0;
  int sign_1 = get_sign(&value_1);
  int sign_2 = get_sign(&value_2);
  int power_1 = get_power(&value_1);
  int power_2 = get_power(&value_2);
  int norm_power = 1;
  if (sign_1 == sign_2) {
    if ((power_1 - power_2) > 0) {
      norm_power = power_normalization(&value_2, power_1, (power_1 - power_2));
    } else if ((power_1 - power_2) < 0) {
      norm_power = power_normalization(&value_1, power_2, (power_2 - power_1));
    }
    s21_truncate(value_1, &decimal_1);
    s21_truncate(value_2, &decimal_2);
    if (equal_decimal(&decimal_1, &decimal_2) == 1 && norm_power == 1) {
      decimal_1 = null_decimal;
      decimal_2 = null_decimal;
      get_mantissa(value_1, &decimal_1);
      get_mantissa(value_2, &decimal_2);
      if (equal_decimal(&decimal_1, &decimal_2) == 1) {
        status = 1;
      }
    }
  } else if (search_first_bit(&value_1) == -1 &&
             search_first_bit(&value_2) == -1) {
    status = 1;
  }
  return status;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}
