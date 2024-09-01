#include <math.h>

#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int status = 0;
  if (dst == NULL) {
    status = 1;
  } else {
    s21_decimal null_decimal = {{0, 0, 0, 0}};
    *dst = null_decimal;
    if (src < 0) {
      invers_bit(dst, 31, 3);
      src *= -1;
    }
    dst->bits[0] = src;
  }
  return status;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int status = 0;
  if (dst == NULL || fabs(src) >= (MAX_FLOAT - 1)) {
    status = 1;
  } else if (fabs(src) < MIN_FLOAT) {
    status = 1;
  } else {
    s21_decimal null_decimal = {{0, 0, 0, 0}};
    *dst = null_decimal;
    if (src < 0) {
      invers_bit(dst, 31, 3);
      src *= -1;
    }
    if (src >= MAX_FLOAT_IN_DECIMAL) {
      while (src > MAX_FLOAT_IN_DECIMAL) {
        src /= 10;
      }
    } else {
      int n = 1;
      float number = src;
      while (src < MAX_FLOAT_IN_DECIMAL && n < 8) {
        src = number * pow(10, n);
        n++;
      }
      if (src > MAX_FLOAT_IN_DECIMAL) {
        src /= 10;
        n--;
      }
      dst->bits[3] = dst->bits[3] | ((n - 1) << 16);
    }
    dst->bits[0] = (int)src;
  }
  return status;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int status = 0;
  if (dst == NULL || get_power(&src) > 28) {
    status = 1;
  } else {
    s21_decimal decimal = {{0, 0, 0, 0}};
    s21_truncate(src, &decimal);
    if (decimal.bits[2] == 0 && decimal.bits[1] == 0) {
      if (decimal.bits[0] < MASK_SIGN && get_sign(&decimal) == 0) {
        *dst = decimal.bits[0];
      } else if (decimal.bits[0] < MASK_SIGN && get_sign(&decimal) == 1) {
        *dst = -1 * decimal.bits[0];
      } else {
        status = 1;
      }
    } else {
      status = 1;
    }
  }
  return status;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int status = 0;
  if (dst == NULL || get_power(&src) > 28) {
    status = 1;
  } else {
    s21_decimal null_decimal = {{0, 0, 0, 0}};
    s21_decimal decimal = null_decimal;
    s21_decimal mantissa = null_decimal;
    s21_truncate(src, &decimal);
    get_mantissa(src, &mantissa);
    if (decimal.bits[2] != 0 || decimal.bits[1] != 0) {
      status = 1;
    } else {
      double result = 0;
      int n = 95;
      int power = get_power(&src);
      int sign = get_sign(&src);
      for (int i = 2; i > -1; i--) {
        for (int j = 31; j > -1; j--, n--) {
          result += get_bit(&mantissa, j, i) * pow(2, n);
        }
      }
      for (int i = 0; i < power; i++) {
        result /= 10;
      }
      *dst = decimal.bits[0] + (float)result;
      if (sign == 1) {
        *dst *= -1;
      }
    }
  }
  return status;
}
