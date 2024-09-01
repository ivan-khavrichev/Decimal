#include <check.h>
#include <math.h>
#include <stdlib.h>

#include "s21_decimal.h"

START_TEST(add_1) {
  s21_decimal value_1 = {{15, 0, 0, 0}};
  s21_decimal value_2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{25, 0, 0, 0}};
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(add_2) {
  s21_decimal value_1 = {{15, 0, 0, 2147483648}};
  s21_decimal value_2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{5, 0, 0, 2147483648}};
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(add_3) {
  s21_decimal value_1 = {{15, 0, 0, 0}};
  s21_decimal value_2 = {{10, 0, 0, 2147483648}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{5, 0, 0, 0}};
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(add_4) {
  s21_decimal value_1 = {{15, 0, 0, 2147483648}};
  s21_decimal value_2 = {{10, 0, 0, 2147483648}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{25, 0, 0, 2147483648}};
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(add_5) {
  s21_decimal value_1 = {{15, 0, 0, 65536}};
  s21_decimal value_2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{115, 0, 0, 65536}};
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(add_6) {
  s21_decimal value_1 = {{15, 0, 0, 0}};
  s21_decimal value_2 = {{10, 0, 0, 65536}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{16, 0, 0, 0}};
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

// OVERFLOW
START_TEST(add_7) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal value_2 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{0, 0, 0, 0}};
  ck_assert_int_eq(1, s21_add(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

// OVERFLOW
START_TEST(add_8) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal value_2 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{0, 0, 0, 0}};
  ck_assert_int_eq(2, s21_add(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

// OVERFLOW
START_TEST(add_9) {
  s21_decimal value_1 = {{199, 0, 0, 65536}};
  s21_decimal value_2 = {{1, 0, 0, 65536}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{20, 0, 0, 0}};
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(add_10) {
  s21_decimal value_1 = {{55555, 0, 0, 0}};
  s21_decimal value_2 = {{66666, 0, 0, 262144}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{555616666, 0, 0, 262144}};
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(add_11) {
  s21_decimal value_1 = {{5555, 0, 0, 2147483648}};
  s21_decimal value_2 = {{333333333, 0, 0, 327680}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{222166667, 0, 0, 2147811328}};
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(add_12) {
  s21_decimal value_1 = {{4294967295, 0, 0, 327680}};
  s21_decimal value_2 = {{4294967295, 100, 0, 2148139008}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{4294867297, 99898, 0, 655360}};
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(add_13) {
  s21_decimal value_1 = {{4294967295, 613566756, 0, 2147811328}};
  s21_decimal value_2 = {{4294967295, 214748364, 0, 2147745792}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{4294967285, 2761050406, 0, 2147811328}};
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(add_14) {
  s21_decimal value_1 = {{346456, 53345, 0, 2147942400}};
  s21_decimal value_2 = {{567567, 3456567, 0, 262144}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{567220544, 3456513655, 0, 458752}};
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(add_15) {
  s21_decimal value_1 = {{4294967295, 4294967295, 2147483647, 1638400}};
  s21_decimal value_2 = {{4294967295, 4294967295, 0, 2148466688}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{4153960755, 858993458, 785251635, 2149056512}};
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(add_16) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 1638400}};
  s21_decimal value_2 = {{4294967295, 4294967295, 4294967295, 2148466688}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{2701727008, 2450292888, 4294967295, 2148466688}};
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

// 79228162514264337593543950335 + (-0.54) = 79228162514264337593543950334
START_TEST(add_17) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal value_2 = {{54, 0, 0, ((1 << 31) | (2 << 16))}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{0xFFFFFFFE, 4294967295, 4294967295, 0}};
  ck_assert_int_eq(0, s21_add(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

// 79228162514264337593543950334 + 1.5 = INF
START_TEST(add_18) {
  s21_decimal value_1 = {{4294967294, 4294967295, 4294967295, 0}};
  s21_decimal value_2 = {{15, 0, 0, 65536}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{0, 0, 0, 0}};
  ck_assert_int_eq(1, s21_add(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(add_19) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal value_2 = {{1, 0, 0, 2147483648}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{0, 0, 0, 0}};
  ck_assert_int_eq(2, s21_add(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(sub_1) {
  s21_decimal value_1 = {{55555, 0, 0, 0}};
  s21_decimal value_2 = {{66666, 0, 0, 262144}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{555483334, 0, 0, 262144}};
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(sub_2) {
  s21_decimal value_1 = {{4294967295, 0, 0, 2147614720}};
  s21_decimal value_2 = {{23465246, 0, 0, 2147549184}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{4060314835, 0, 0, 2147614720}};
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(sub_3) {
  s21_decimal value_1 = {{4294967295, 0, 0, 0}};
  s21_decimal value_2 = {{4294967295, 100, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{0, 100, 0, 2147483648}};
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(sub_4) {
  s21_decimal value_1 = {{4294967295, 4563654, 0, 2148139008}};
  s21_decimal value_2 = {{23465246, 364563, 0, 2148270080}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{4271501950, 456000936, 0, 2148270080}};
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(sub_5) {
  s21_decimal value_1 = {{4294967295, 345634, 0, 2147876864}};
  s21_decimal value_2 = {{23465246, 45634, 0, 327680}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{234652459, 801975, 0, 2147876864}};
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(sub_6) {
  s21_decimal value_1 = {{4294967295, 345634, 0, 393216}};
  s21_decimal value_2 = {{23465246, 45634, 0, 2147811328}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{234652459, 801975, 0, 393216}};
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(sub_7) {
  s21_decimal value_1 = {{4294967295, 4294967295, 2147483647, 1638400}};
  s21_decimal value_2 = {{4294967295, 4294967295, 0, 983040}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{4153960755, 858993458, 785251635, 2149056512}};
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(sub_8) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal value_2 = {{4294967294, 4294967295, 4294967295, 0}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{1, 0, 0, 0}};
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(sub_9) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 1835008}};
  s21_decimal value_2 = {{4294967294, 4294967295, 4294967295, 0}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{4294967286, 4294967295, 4294967295, 2147483648}};
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

// 79228162514264337593543950335 - 0.54 = 79228162514264337593543950334
START_TEST(sub_10) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295}};
  s21_decimal value_2 = {{54, 0, 0, (2 << 16)}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{0xFFFFFFFE, 4294967295, 4294967295}};
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(sub_11) {
  s21_decimal value_1 = {{0x88c7bcb6, 0x9bdf88, 0, ((1 << 31) | (2 << 16))}};
  s21_decimal value_2 = {{4294967295, 4294967295, 4294967295, (1 << 31)}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{0xf4646712, 0xfffe70f6, 0xffffffff}};
  ck_assert_int_eq(0, s21_sub(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(sub_12) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 2147483648}};
  s21_decimal value_2 = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{0, 0, 0, 0}};
  ck_assert_int_eq(2, s21_sub(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(sub_13) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 0}};
  s21_decimal value_2 = {{1, 0, 0, (1 << 31)}};
  s21_decimal result = {{0}};
  s21_decimal answer = {{0, 0, 0, 0}};
  ck_assert_int_eq(1, s21_sub(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(mul_1) {
  s21_decimal value_1 = {{15, 0, 0, 0}};
  s21_decimal value_2 = {{10, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{150, 0, 0, 0}};
  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(mul_2) {
  s21_decimal value_1 = {{0x26687e73, 0, 0, (4 << 16)}};
  s21_decimal value_2 = {{0xd3, 0, 0, (1 << 16)}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{0xa82038c9, 0x1f, 0, (5 << 16)}};
  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(mul_3) {
  s21_decimal value_1 = {{0x1, 0, 0, ((1 << 31) | (14 << 16))}};
  s21_decimal value_2 = {{0x1, 0, 0, ((1 << 31) | (14 << 16))}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{0x1, 0, 0, (28 << 16)}};
  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(mul_4) {
  s21_decimal value_1 = {{0x6, 0, 0, ((1 << 31) | (0 << 16))}};
  s21_decimal value_2 = {{0x1, 0, 0, ((1 << 31) | (0 << 16))}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{0x6, 0, 0, (0 << 16)}};
  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(mul_5) {
  s21_decimal value_1 = {{0}};
  s21_decimal value_2 = {{0xffffffff, 0, 0, ((1 << 31) | (2 << 16))}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{0, 0, 0, ((1 << 31) | (2 << 16))}};
  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(mul_6) {
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_decimal value_2 = {{0xffffffff, 0, 0, ((1 << 31) | (2 << 16))}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{0xffffffff, 0, 0, ((1 << 31) | (2 << 16))}};
  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(mul_7) {
  s21_decimal value_1 = {{2, 0, 0, 0}};
  s21_decimal value_2 = {{0, 1, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{0, 2, 0, 0}};
  ck_assert_int_eq(0, s21_mul(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(div_1) {
  s21_decimal value_1 = {{150, 0, 0, 0}};
  s21_decimal value_2 = {{15, 0, 0, 0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{10, 0, 0, 0}};
  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(div_2) {
  s21_decimal value_1 = {{1000, 0, 0, (2 << 16)}};
  s21_decimal value_2 = {{10, 0, 0, (1 << 16)}};
  s21_decimal result = {0};
  s21_decimal answer = {{100, 0, 0, (1 << 16)}};
  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(div_3) {
  s21_decimal value_1 = {{133, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal answer = {{266, 0, 0, (1 << 16)}};
  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(div_4) {
  s21_decimal value_1 = {{133, 0, 0, (29 << 16)}};
  s21_decimal value_2 = {{5, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal answer = {0};
  ck_assert_int_eq(1, s21_div(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(div_5) {
  s21_decimal value_1 = {{133, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, (29 << 16)}};
  s21_decimal result = {0};
  s21_decimal answer = {0};
  ck_assert_int_eq(2, s21_div(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(div_6) {
  s21_decimal value_1 = {{133, 0, 0, 0}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_decimal result = {0};
  s21_decimal answer = {0};
  ck_assert_int_eq(3, s21_div(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(div_7) {
  s21_decimal value_1 = {{133, 0, 0, 0}};
  s21_decimal value_2 = {{5, 0, 0, (1 << 31)}};
  s21_decimal result = {0};
  s21_decimal answer = {{266, 0, 0, ((1 << 31) | (1 << 16))}};
  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(div_8) {
  s21_decimal value_1 = {{30, 0, 0, 0}};
  s21_decimal value_2 = {{40, 0, 0, (1 << 31)}};
  s21_decimal result = {0};
  s21_decimal answer = {{75, 0, 0, ((1 << 31) | (2 << 16))}};
  ck_assert_int_eq(0, s21_div(value_1, value_2, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(compare_1) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(compare_2) {
  s21_decimal a = {{123, 123, 123, 0}};
  s21_decimal b = {{123, 123, 123, 0}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(compare_3) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{123, 0, 0, -2147483648}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(compare_4) {
  s21_decimal a = {{0xffffffff, 0xffffffff, 0, 1835008}};
  s21_decimal b = {{0xffffffff, 0xfffffffe, 0, 1835008}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(compare_5) {
  s21_decimal a = {{0xffffffff, 0xffffffff, 0xffffffff, 65536}};
  s21_decimal b = {{0xffffffff, 0xffffffff, 0xffffffff, 196608}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(compare_7) {
  s21_decimal a = {{12345600, 0, 0, 196608}};
  s21_decimal b = {{123456, 0, 0, 65536}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(compare_8) {
  s21_decimal a = {{12345678, 0, 0, 0}};
  s21_decimal b = {{123456781, 0, 0, 65536}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(compare_9) {
  s21_decimal a = {{0, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, -2147483648}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(compare_10) {
  s21_decimal a = {{2631000, 0, 0, (4 << 16)}};
  s21_decimal b = {{263103, 0, 0, (3 << 16)}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(compare_11) {
  s21_decimal a = {{263100, 0, 0, ((1 << 31) | (1 << 16))}};
  s21_decimal b = {{263103, 0, 0, (1 << 16)}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater(a, b), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
  ck_assert_int_eq(s21_is_equal(a, b), 0);
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(int_to_decimal1) {
  int a = 9999;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{9999, 0, 0, 0}};
  int j = s21_from_int_to_decimal(a, &result);
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
  ck_assert_int_eq(j, 0);
}
END_TEST

START_TEST(int_to_decimal2) {
  int a = -9999;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{9999, 0, 0, 1 << 31}};
  int j = s21_from_int_to_decimal(a, &result);
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
  ck_assert_int_eq(j, 0);
}
END_TEST

START_TEST(int_to_decimal3) {
  int a = 1;
  int j = s21_from_int_to_decimal(a, NULL);
  ck_assert_int_eq(j, 1);
}
END_TEST

START_TEST(int_to_decimal4) {
  int a = 0;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{0, 0, 0, ((0 << 31) | (0 << 16))}};
  int j = s21_from_int_to_decimal(a, &result);
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
  ck_assert_int_eq(j, 0);
}
END_TEST

START_TEST(int_to_decimal5) {
  int a = 1234567;
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{1234567, 0, 0, 0}};
  int j = s21_from_int_to_decimal(a, &result);
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
  ck_assert_int_eq(j, 0);
}
END_TEST

START_TEST(float_to_decimal1) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{15500000, 0, 0, 7 << 16}};
  int j = 0;
  j = s21_from_float_to_decimal(1.55, &result);
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
  ck_assert_int_eq(j, 0);
}
END_TEST

START_TEST(float_to_decimal2) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{15500000, 0, 0, ((1 << 31) | (6 << 16))}};
  int j = 0;
  j = s21_from_float_to_decimal(-15.5, &result);
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
  ck_assert_int_eq(j, 0);
}
END_TEST

START_TEST(float_to_decimal3) {
  int j = 0;
  j = s21_from_float_to_decimal(-1.5555555, NULL);
  ck_assert_int_eq(j, 1);
}
END_TEST

START_TEST(float_to_decimal4) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{15555550, 0, 0, ((1 << 31) | (7 << 16))}};
  int j = 0;
  j = s21_from_float_to_decimal(-1.555555, &result);
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
  ck_assert_int_eq(j, 0);
}
END_TEST

START_TEST(float_to_decimal5) {
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal answer = {{12345679, 0, 0, ((1 << 31) | (7 << 16))}};
  int j = 0;
  j = s21_from_float_to_decimal((float)-1.23456789, &result);
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
  ck_assert_int_eq(j, 0);
}
END_TEST

START_TEST(decimal_to_int1) {
  int a = 1;
  int b = 0;
  s21_decimal answer = {{1, 0, 0, ((0 << 31) | (0 << 16))}};
  int j = 0;
  j = s21_from_decimal_to_int(answer, &b);
  ck_assert_int_eq(a, b);
  ck_assert_int_eq(j, 0);
}
END_TEST

START_TEST(decimal_to_int2) {
  int a = -1;
  int b = 0;
  s21_decimal answer = {{1, 0, 0, ((1 << 31) | (0 << 16))}};
  int j = 0;
  j = s21_from_decimal_to_int(answer, &b);
  ck_assert_int_eq(a, b);
  ck_assert_int_eq(j, 0);
}
END_TEST

START_TEST(decimal_to_int3) {
  int a = -1;
  int b = 0;
  s21_decimal answer = {{1, 0, 0, ((1 << 31) | (0 << 16))}};
  int j = 0;
  j = s21_from_decimal_to_int(answer, &b);
  ck_assert_int_eq(a, b);
  ck_assert_int_eq(j, 0);
}
END_TEST

START_TEST(decimal_to_int4) {
  int a = 0;
  int b = 0;
  s21_decimal answer = {{2, 0, 0, ((0 << 31) | (1 << 16))}};
  int j = 0;
  j = s21_from_decimal_to_int(answer, &b);
  ck_assert_int_eq(a, b);
  ck_assert_int_eq(j, 0);
}
END_TEST

START_TEST(decimal_to_int5) {
  int b = 0;
  s21_decimal answer = {{2, 1, 0, ((0 << 31) | (0 << 16))}};
  int j = 0;
  j = s21_from_decimal_to_int(answer, &b);
  ck_assert_int_eq(j, 1);
}
END_TEST

START_TEST(decimal_to_float1) {
  s21_decimal answer = {{2, 1, 0, ((0 << 31) | (0 << 16))}};
  float j = 0;
  j = s21_from_decimal_to_float(answer, NULL);
  ck_assert_int_eq(j, 1);
}
END_TEST

START_TEST(decimal_to_float2) {
  float a = 1.1;
  float b = 0;
  s21_decimal answer = {{11, 0, 0, ((0 << 31) | (1 << 16))}};
  float j = 0;
  j = s21_from_decimal_to_float(answer, &b);
  ck_assert_float_eq(a, b);
  ck_assert_int_eq(j, 0);
}
END_TEST

START_TEST(decimal_to_float3) {
  float a = -1.1;
  float b = 0;
  s21_decimal answer = {{11, 0, 0, ((1 << 31) | (1 << 16))}};
  float j = 0;
  j = s21_from_decimal_to_float(answer, &b);
  ck_assert_float_eq(a, b);
  ck_assert_int_eq(j, 0);
}
END_TEST

START_TEST(decimal_to_float4) {
  float a = 1.2345678;
  float b = 0;
  s21_decimal answer = {{123456781, 0, 0, ((0 << 31) | (8 << 16))}};
  int j = 0;
  j = s21_from_decimal_to_float(answer, &b);
  ck_assert_float_eq(b, a);
  ck_assert_int_eq(j, 0);
}
END_TEST

START_TEST(decimal_to_float5) {
  s21_decimal answer = {
      {UINT32_MAX, UINT32_MAX, UINT32_MAX, ((0 << 31) | (5 << 16))}};
  float a = 1234.567;
  int j = s21_from_decimal_to_float(answer, &a);
  ck_assert_int_eq(j, 1);
}
END_TEST

START_TEST(floor_1) {
  s21_decimal value = {{0, 0, 0, (14 << 16)}};
  s21_decimal answer = {{0, 0, 0, 0}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_floor(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(floor_2) {
  s21_decimal value = {{362732873, 0, 0, (1 << 31)}};
  s21_decimal answer = {{362732873, 0, 0, (1 << 31)}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_floor(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(floor_3) {
  s21_decimal value = {{572963473, 0, 0, (4 << 16)}};
  s21_decimal answer = {{57296, 0, 0, 0}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_floor(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

// -438732872.43743877 => -438732872
START_TEST(floor_4) {
  s21_decimal value = {{0xb54ac285, 0x9bde85, 0, ((1 << 31) | (8 << 16))}};
  s21_decimal answer = {{0x1a268849, 0, 0, (1 << 31)}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_floor(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

//  8684958394.00000000 => 8684958394
START_TEST(floor_5) {
  s21_decimal value = {{0x4C577A00, 0xC0D845D, 0, ((0 << 31) | (8 << 16))}};
  s21_decimal answer = {{0x5A9F2BA, 0x2, 0, 0}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_floor(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

//  -7.9228162514264337593543950335 => -8
START_TEST(floor_6) {
  s21_decimal value = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, ((1 << 31) | (28 << 16))}};
  s21_decimal answer = {{8, 0, 0, (1 << 31)}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_floor(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(floor_7) {
  s21_decimal value = {{0, 0, 0, 0}};
  s21_decimal answer = {{0, 0, 0, 0}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_floor(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(floor_8) {
  s21_decimal value = {{0, 0, 0, ((1 << 31) | (7 << 16))}};
  s21_decimal answer = {{0, 0, 0, 0}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_floor(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(floor_9) {
  s21_decimal value = {{5, 0, 0, ((1 << 31) | (1 << 16))}};
  s21_decimal answer = {{1, 0, 0, (1 << 31)}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_floor(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(floor_10) {
  s21_decimal value = {{5, 0, 0, ((0 << 31) | (1 << 16))}};
  s21_decimal answer = {{0, 0, 0, 0}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_floor(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(floor_11) {
  s21_decimal value = {{0}};
  int k = s21_floor(value, NULL);
  ck_assert_int_eq(1, k);
}
END_TEST

START_TEST(round_1) {
  s21_decimal value = {{0, 0, 0, ((0 << 31) | (15 << 16))}};
  s21_decimal answer = {{0}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(0, s21_round(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(round_2) {
  s21_decimal value = {{362732873, 0, 0, (1 << 31)}};
  s21_decimal answer = {{362732873, 0, 0, (1 << 31)}};
  s21_decimal result = {{0}};
  ck_assert_int_eq(0, s21_round(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

// -4.5 => -4
START_TEST(round_3) {
  s21_decimal value = {{45, 0, 0, (1 << 16)}};
  s21_decimal answer = {{4, 0, 0, 0}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_round(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

//  -438732872.43743877 => -438732872
START_TEST(round_4) {
  s21_decimal value = {{0xb54ac285, 0x9bde85, 0, ((1 << 31) | (8 << 16))}};
  s21_decimal answer = {{0x1a268848, 0, 0, (1 << 31)}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_round(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

//  8684958394.00000000 => 8684958394
START_TEST(round_5) {
  s21_decimal value = {{0x4C577A00, 0xC0D845D, 0, (8 << 16)}};
  s21_decimal answer = {{0x5A9F2BA, 0x2, 0, 0}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_round(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

// -7.9228162514264337593543950335 => -8
START_TEST(round_6) {
  s21_decimal value = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, ((1 << 31) | (28 << 16))}};
  s21_decimal answer = {{8, 0, 0, (1 << 31)}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_round(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(round_7) {
  s21_decimal value = {{0}};
  int k = s21_round(value, NULL);
  ck_assert_int_eq(1, k);
}
END_TEST

START_TEST(truncate_1) {
  s21_decimal value = {{0, 0, 0, (15 << 16)}};
  s21_decimal answer = {{0}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_truncate(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

// 36273287.3 = 36273287
START_TEST(truncate_2) {
  s21_decimal value = {{362732873, 0, 0, (1 << 31)}};
  s21_decimal answer = {{362732873, 0, 0, (1 << 31)}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_truncate(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

// 57296.3473 => 57296
START_TEST(truncate_3) {
  s21_decimal value = {{572963473, 0, 0, (4 << 16)}};
  s21_decimal answer = {{57296, 0, 0, 0}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_truncate(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

// -438732872.43743877 => -438732872
START_TEST(truncate_4) {
  s21_decimal value = {{0xb54ac285, 0x9bde85, 0, ((1 << 31) | (8 << 16))}};
  s21_decimal answer = {{0x1a268848, 0, 0, (1 << 31)}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_truncate(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

// 8684958394.00000000 => 8684958394
START_TEST(truncate_5) {
  s21_decimal value = {{0x4C577A00, 0xC0D845D, 0, (8 << 16)}};
  s21_decimal answer = {{0x5A9F2BA, 0x2, 0, 0}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_truncate(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

// -7.9228162514264337593543950335 => -7
START_TEST(truncate_6) {
  s21_decimal value = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, ((1 << 31) | (28 << 16))}};
  s21_decimal answer = {{7, 0, 0, (1 << 31)}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_truncate(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(truncate_7) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, (29 << 16)}};
  s21_decimal result;
  ck_assert_int_eq(1, s21_truncate(value, &result));
}
END_TEST

START_TEST(truncate_8) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, (27 << 16)}};
  int k = s21_negate(value, NULL);
  ck_assert_int_eq(1, k);
}
END_TEST

START_TEST(negate_1) {
  s21_decimal value = {{0, 0, 0, (2 << 16)}};
  s21_decimal answer = {{0, 0, 0, 0}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_negate(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(negate_2) {
  s21_decimal value = {{2, 3, 7, (1 << 31)}};
  s21_decimal answer = {{2, 3, 7, 0}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_negate(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(negate_3) {
  s21_decimal value = {{2, 3, 7, ((1 << 31) | (7 << 16))}};
  s21_decimal answer = {{2, 3, 7, (7 << 16)}};
  s21_decimal result;
  ck_assert_int_eq(0, s21_negate(value, &result));
  int k = test_decimal(result, answer);
  ck_assert_int_eq(k, 0);
}
END_TEST

START_TEST(negate_4) {
  s21_decimal value = {{0}};
  int k = s21_negate(value, NULL);
  ck_assert_int_eq(1, k);
}
END_TEST

Suite *s21_decimal_tests_create() {
  {
    Suite *s21_decimal = suite_create("s21_decimal");
    TCase *s21_decimal_tests = tcase_create("S21_DECIMAL");

    tcase_add_test(s21_decimal_tests, add_1);
    tcase_add_test(s21_decimal_tests, add_2);
    tcase_add_test(s21_decimal_tests, add_3);
    tcase_add_test(s21_decimal_tests, add_4);
    tcase_add_test(s21_decimal_tests, add_5);
    tcase_add_test(s21_decimal_tests, add_6);
    tcase_add_test(s21_decimal_tests, add_7);
    tcase_add_test(s21_decimal_tests, add_8);
    tcase_add_test(s21_decimal_tests, add_9);
    tcase_add_test(s21_decimal_tests, add_10);
    tcase_add_test(s21_decimal_tests, add_11);
    tcase_add_test(s21_decimal_tests, add_12);
    tcase_add_test(s21_decimal_tests, add_13);
    tcase_add_test(s21_decimal_tests, add_14);
    tcase_add_test(s21_decimal_tests, add_15);
    tcase_add_test(s21_decimal_tests, add_16);
    tcase_add_test(s21_decimal_tests, add_17);
    tcase_add_test(s21_decimal_tests, add_18);
    tcase_add_test(s21_decimal_tests, add_19);

    tcase_add_test(s21_decimal_tests, sub_1);
    tcase_add_test(s21_decimal_tests, sub_2);
    tcase_add_test(s21_decimal_tests, sub_3);
    tcase_add_test(s21_decimal_tests, sub_4);
    tcase_add_test(s21_decimal_tests, sub_5);
    tcase_add_test(s21_decimal_tests, sub_6);
    tcase_add_test(s21_decimal_tests, sub_7);
    tcase_add_test(s21_decimal_tests, sub_8);
    tcase_add_test(s21_decimal_tests, sub_9);
    tcase_add_test(s21_decimal_tests, sub_10);
    tcase_add_test(s21_decimal_tests, sub_11);
    tcase_add_test(s21_decimal_tests, sub_12);
    tcase_add_test(s21_decimal_tests, sub_13);

    tcase_add_test(s21_decimal_tests, mul_1);
    tcase_add_test(s21_decimal_tests, mul_2);
    tcase_add_test(s21_decimal_tests, mul_3);
    tcase_add_test(s21_decimal_tests, mul_4);
    tcase_add_test(s21_decimal_tests, mul_5);
    tcase_add_test(s21_decimal_tests, mul_6);
    tcase_add_test(s21_decimal_tests, mul_7);

    tcase_add_test(s21_decimal_tests, div_1);
    tcase_add_test(s21_decimal_tests, div_2);
    tcase_add_test(s21_decimal_tests, div_3);
    tcase_add_test(s21_decimal_tests, div_4);
    tcase_add_test(s21_decimal_tests, div_5);
    tcase_add_test(s21_decimal_tests, div_6);
    tcase_add_test(s21_decimal_tests, div_7);
    tcase_add_test(s21_decimal_tests, div_8);

    tcase_add_test(s21_decimal_tests, compare_1);
    tcase_add_test(s21_decimal_tests, compare_2);
    tcase_add_test(s21_decimal_tests, compare_3);
    tcase_add_test(s21_decimal_tests, compare_4);
    tcase_add_test(s21_decimal_tests, compare_5);
    tcase_add_test(s21_decimal_tests, compare_7);
    tcase_add_test(s21_decimal_tests, compare_8);
    tcase_add_test(s21_decimal_tests, compare_9);
    tcase_add_test(s21_decimal_tests, compare_10);
    tcase_add_test(s21_decimal_tests, compare_11);

    tcase_add_test(s21_decimal_tests, int_to_decimal1);
    tcase_add_test(s21_decimal_tests, int_to_decimal2);
    tcase_add_test(s21_decimal_tests, int_to_decimal3);
    tcase_add_test(s21_decimal_tests, int_to_decimal4);
    tcase_add_test(s21_decimal_tests, int_to_decimal5);

    tcase_add_test(s21_decimal_tests, float_to_decimal1);
    tcase_add_test(s21_decimal_tests, float_to_decimal2);
    tcase_add_test(s21_decimal_tests, float_to_decimal3);
    tcase_add_test(s21_decimal_tests, float_to_decimal4);
    tcase_add_test(s21_decimal_tests, float_to_decimal5);

    tcase_add_test(s21_decimal_tests, decimal_to_int1);
    tcase_add_test(s21_decimal_tests, decimal_to_int2);
    tcase_add_test(s21_decimal_tests, decimal_to_int3);
    tcase_add_test(s21_decimal_tests, decimal_to_int4);
    tcase_add_test(s21_decimal_tests, decimal_to_int5);

    tcase_add_test(s21_decimal_tests, decimal_to_float1);
    tcase_add_test(s21_decimal_tests, decimal_to_float2);
    tcase_add_test(s21_decimal_tests, decimal_to_float3);
    tcase_add_test(s21_decimal_tests, decimal_to_float4);
    tcase_add_test(s21_decimal_tests, decimal_to_float5);

    tcase_add_test(s21_decimal_tests, floor_1);
    tcase_add_test(s21_decimal_tests, floor_2);
    tcase_add_test(s21_decimal_tests, floor_3);
    tcase_add_test(s21_decimal_tests, floor_4);
    tcase_add_test(s21_decimal_tests, floor_5);
    tcase_add_test(s21_decimal_tests, floor_6);
    tcase_add_test(s21_decimal_tests, floor_7);
    tcase_add_test(s21_decimal_tests, floor_8);
    tcase_add_test(s21_decimal_tests, floor_9);
    tcase_add_test(s21_decimal_tests, floor_10);
    tcase_add_test(s21_decimal_tests, floor_11);

    tcase_add_test(s21_decimal_tests, round_1);
    tcase_add_test(s21_decimal_tests, round_2);
    tcase_add_test(s21_decimal_tests, round_3);
    tcase_add_test(s21_decimal_tests, round_4);
    tcase_add_test(s21_decimal_tests, round_5);
    tcase_add_test(s21_decimal_tests, round_6);
    tcase_add_test(s21_decimal_tests, round_7);

    tcase_add_test(s21_decimal_tests, truncate_1);
    tcase_add_test(s21_decimal_tests, truncate_2);
    tcase_add_test(s21_decimal_tests, truncate_3);
    tcase_add_test(s21_decimal_tests, truncate_4);
    tcase_add_test(s21_decimal_tests, truncate_5);
    tcase_add_test(s21_decimal_tests, truncate_6);
    tcase_add_test(s21_decimal_tests, truncate_7);
    tcase_add_test(s21_decimal_tests, truncate_8);

    tcase_add_test(s21_decimal_tests, negate_1);
    tcase_add_test(s21_decimal_tests, negate_2);
    tcase_add_test(s21_decimal_tests, negate_3);
    tcase_add_test(s21_decimal_tests, negate_4);

    suite_add_tcase(s21_decimal, s21_decimal_tests);
    return s21_decimal;
  }
}

int main() {
  Suite *s21_decimal = s21_decimal_tests_create();
  SRunner *s21_decimal_runner = srunner_create(s21_decimal);
  int number_failed;
  srunner_run_all(s21_decimal_runner, CK_NORMAL);
  number_failed = srunner_ntests_failed(s21_decimal_runner);
  srunner_free(s21_decimal_runner);

  return number_failed == 0 ? 0 : 1;
}
