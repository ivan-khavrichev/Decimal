#ifndef S21_DECIMAL_H_
#define S21_DECIMAL_H_

#include <math.h>
#include <stdio.h>

#define MASK_POWER 16711680   // 0000 0000 1111 1111 0000 0000 0000 0000
#define MASK_SIGN 2147483648  // 1000 0000 0000 0000 0000 0000 0000 0000

#define MASK_LOW_WORLD 65535  // 0000 0000 0000 0000 1111 1111 1111 1111

#define MASK_CHECK_SHIFT 2147483648  // 1000 0000 0000 0000 0000 0000 0000 0000
#define MASK_SHIFT 2147483647        // 0111 1111 1111 1111 1111 1111 1111 1111

#define SEGMENT_FOR_FLOAT 8388608

#define MAX_FLOAT pow(2, 96)
#define MAX_FLOAT_IN_DECIMAL 99999999
#define MIN_FLOAT 1E-28

// максимальная допустимая степень (десятичная система счисления)
#define MAX_POW 28
// последний по номеру бит в инте из bits[4]
#define LAST_BIT 31
// последний по номеру индекс bits[4]
#define LAST_INT 3
// первый бит коэффициента масштабирования ( 10^(-POW) )

#define OK 0
#define OVERFLOW_DEC 1
#define DIV_BY_ZERO 2

typedef struct {
  unsigned int bits[4];
} s21_decimal;

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);

int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

// ДОП. ФУНКЦИИ

//  Печать, тесты

//  конвертирует числа в двоичные и печатает их в виде децимала
void convert_and_print_decimal(s21_decimal value);
//  печать децимала
void print_decimal(int decimal[32][4]);
//  возвращает 0, если децималы равны (без последнего бита)
int test_decimal(s21_decimal value_1, s21_decimal value_2);

//  Работа с 1-м битом

//  возвращает значение бита на заданной позиции
int get_bit(s21_decimal *value, int position, int elem);
//  инвертирует бит на заданной позиции
void invers_bit(s21_decimal *value, int position, int elem);

//  Анализ децимала

//  поиск первого ненулевого бита в децимале: возвращает позицию бита, при его
//  отутствии возвращает -1
int search_first_bit(s21_decimal *value);
//  сравнение целых частей 2-х децималов: если первый больше возвращает 1, иначе
//  0
int comparison_decimal(s21_decimal *value_1, s21_decimal *value_2);
//  проверка на равенство двух децималов: равны возвращает 1, иначе 0
int equal_decimal(s21_decimal *value_1, s21_decimal *value_2);
//  проверяет децимал на переполнение: если переполнение, изменяет переданный
//  флаг на 0
void check_overflow(s21_decimal *value, int *flag);

//  Простейшая работа с децималом

//  сдвигает децимал на 1 бит влево
void shift_left(s21_decimal *value);
//  сдвигает децимал на 1 бит вправо
void shift_right(s21_decimal *value);
//  вычитает бит из децимала: возвращает 1, если вычитание произвелось, иначе 0
int sub_bit(s21_decimal *value, int position, int elem);
//  добавляет бит к децималу: возвращает 1, если успешно, иначе 0 -- произошло
//  переполнение
int add_bit(s21_decimal *value, int position, int elem);
//  возвращает значение степени
int get_power(s21_decimal *value);
//  возвращает значение знака: 0 это `+`, 1 это `-`
int get_sign(s21_decimal *value);
//  записывает степень и знак децимала
void write_power_and_sign(s21_decimal *value, int power, int sign);

// Арифметческие и пр. операции с децималом

//  вычитает децимал из децимала, работает только с целыми частями, первый
//  децимал должен быть больше, чем второй результат запишется в первый децимал
void sub_decimal(s21_decimal *value_1, s21_decimal *value_2);
//  складывает децимал с децималом, работает только с целыми частями, результат
//  записывается во второй
int add_decimal(s21_decimal *value_1, s21_decimal *value_2);
//  складывает децимал с децималом, работает только с целыми частями, результат
//  записывается во второй если при сложении возникает переполнение,
//  скаладываются децималы, делённые на 10 возвращает 1, если успешно, иначе 0 и
//  результат при переполнении
int add_decimal_with_overflow(s21_decimal *value_1, s21_decimal *value_2);
//  перенос разряда для вычитания
int transfer(s21_decimal *mant_1, s21_decimal *mant_2, int norm_power,
             s21_decimal *mantissa_full);
//  делит децимал на 10, остаток отбрасывается, если успешно вовзвращает 1,
//  иначе 0
int div_ten(s21_decimal *value, s21_decimal *result);
//  умножает децимал на 10, если успешно вовзвращает 1, иначе 0
int mul_ten(s21_decimal *value, s21_decimal *result);
//  n раз умножает децимал на 10, возвращает количество успешных умножений (до
//  переполнения)
int mul_ten_n_times(s21_decimal *value, s21_decimal *result, int n);
//  n раз умножает децимал на 10, при переполнении делит на 10 столько раз,
//  сколько степеней переполнили
int mul_ten_n_times_with_overflow(s21_decimal *value, s21_decimal *result,
                                  int *norm_power);
//  n раз делит децимал на 10, возвращает степень результата
int div_ten_n_times(s21_decimal *value, s21_decimal *result, int n);
//  выделяет мантиссу (дробную часть) из децимала
void get_mantissa(s21_decimal value, s21_decimal *mantissa);
//  уравнивает степени децимала: возвращает 1, если успешно, иначе 0 --
//  произошло переполнение принимает децимал, степень которого нужно увеличить,
//  саму степень до которой нужно увеличить и разницу между степенями
int power_normalization(s21_decimal *value, int power, int final_power);
//  (для арифметических операций)уравнивает степени децимала: возвращает 1, если
//  успешно, иначе 0 -- произошло переполнение
int power_normalization_for_arithmetic(int power_1, int power_2,
                                       s21_decimal *value_1,
                                       s21_decimal *value_2);

//  div

//  делит децимал на децимал, первый больше второго
//  возвращает 0, если всё ок, 1, если число слишком велико или равно
//  бесконечности
int div_greater(s21_decimal *value_1, s21_decimal *value_2, s21_decimal *result,
                int flag_switch);
//  делит децимал на децимал, первый меньше второго
//  возвращает 0, если всё ок, 2, если число слишком мало или равно
//  отрицательной бесконечности
int div_less(s21_decimal *value_1, s21_decimal *value_2, s21_decimal *result);

//  add и sub

//  возвращает целые части и мантиссы двух децималов
void trunc_and_get_mantissa(s21_decimal value_1, s21_decimal value_2,
                            s21_decimal *int_part_1, s21_decimal *int_part_2,
                            s21_decimal *mantissa_1, s21_decimal *mantissa_2);
// учет переполнений после умножения инта на 10
void check_diff_pow(int diff_pow, int *norm_pow, s21_decimal *mantissa_2,
                    s21_decimal *mantissa_full, int *overflow,
                    int *overflow_round);
// приводит ответ к нужной степени
void bringing_an_answer(s21_decimal *result);
// округление при переполнении в add
void rounding_in_add(s21_decimal *result, s21_decimal *mantissa_2,
                     int norm_power, int *overflow);
// округление при переполнении в sub
void rounding_in_sub(s21_decimal *result, s21_decimal *mantissa_full,
                     int norm_power);
// работа со значениями разных знаков в add
void different_signs_add(s21_decimal *value_1, s21_decimal *value_2,
                         int power_1, int power_2, s21_decimal *result,
                         int sign_1, int sign_2, int *status);
// работа со значениями разных знаков в add
void different_signs_sub(s21_decimal *value_1, s21_decimal *value_2,
                         int power_1, int power_2, s21_decimal *result,
                         int sign_1, int *status);
// вывод функции (при одинаковых знаках)
void status_out(int norm_power, int overflow, int sign_1, int *status,
                s21_decimal *result);
// работа в sub со случаями без переноса разряда
void simple_case(s21_decimal *int_part_1, s21_decimal *int_part_2,
                 int *norm_power, s21_decimal *mantissa_1,
                 s21_decimal *mantissa_2, int *overflow_round, int sign,
                 s21_decimal *int_part_full, s21_decimal *mantissa_full);
// работа в sub со случаями c переносом разряда
void transfer_case(s21_decimal *int_part_1, s21_decimal *int_part_2,
                   int *norm_power, s21_decimal *mantissa_1,
                   s21_decimal *mantissa_2, int *overflow_round, int sign,
                   s21_decimal *int_part_full, s21_decimal *mantissa_full);

#endif  // S21_DECIMAL_H_
