#include <check.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_credit_calc.h"

int equal_double(double a_, double b_);

#define IS_TEST_TURN_ON 0

#if IS_TEST_TURN_ON
void print_credit_data(s_credit_data data_) {
  printf("mount first = %Lf\n", data_.mount);
  printf("mount last = %Lf\n", data_.mount_last);
  printf("procents = %Lf\n", data_.procents);
  printf("total = %Lf\n", data_.total);
}
#endif

START_TEST(s21_calculator_credit_different_years_test) {
  s_credit_data res;

  res = calculator_different(0, 1, 0, 0);

#if IS_TEST_TURN_ON
  print_credit_data(res);
#endif

  ck_assert_int_eq(equal_double(res.mount, 0.0), 1);
  ck_assert_int_eq(equal_double(res.mount_last, 0.0), 1);
  ck_assert_int_eq(equal_double(res.procents, 0.0), 1);
  ck_assert_int_eq(equal_double(res.total, 0.0), 1);

  /* *****  ***** */

  res = calculator_different(112300, 2, 1, 9);

#if IS_TEST_TURN_ON
  print_credit_data(res);
#endif

  ck_assert_int_eq(equal_double(res.mount, 5521.42), 1);
  ck_assert_int_eq(equal_double(res.mount_last, 4714.26), 1);
  ck_assert_int_eq(equal_double(res.procents, 10528.13), 1);
  ck_assert_int_eq(equal_double(res.total, 122828.13), 1);

  /* *****  ***** */

  res = calculator_different(240000, 6, 1, 9);

#if IS_TEST_TURN_ON
  print_credit_data(res);
#endif

  ck_assert_int_eq(equal_double(res.mount, 5133.33), 1);
  ck_assert_int_eq(equal_double(res.mount_last, 3358.33), 1);
  ck_assert_int_eq(equal_double(res.procents, 65700.00), 1);
  ck_assert_int_eq(equal_double(res.total, 305700.00), 1);

  /* *****  ***** */

  res = calculator_different(112300, 2, 1, 9);

#if IS_TEST_TURN_ON
  print_credit_data(res);
#endif
  ck_assert_int_eq(equal_double(res.mount, 5521.42), 1);
  ck_assert_int_eq(equal_double(res.mount_last, 4714.26), 1);
  ck_assert_int_eq(equal_double(res.procents, 10528.13), 1);
  ck_assert_int_eq(equal_double(res.total, 122828.13), 1);

  /* *****  ***** */

  res = calculator_different(3830000, 12, 1, 14);

#if IS_TEST_TURN_ON
  print_credit_data(res);
#endif
  ck_assert_int_eq(equal_double(res.mount, 71280.56), 1);
  ck_assert_int_eq(equal_double(res.mount_last, 26907.52), 1);
  ck_assert_int_eq(equal_double(res.procents, 3239541.67), 1);
  ck_assert_int_eq(equal_double(res.total, 7069541.67), 1);

  /* *****  ***** */
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_calculator_credit_different_mount_test) {
  s_credit_data res;

  res = calculator_different(240000, 6, 0, 9);

#if IS_TEST_TURN_ON
  print_credit_data(res);
#endif

  ck_assert_int_eq(equal_double(res.mount, 41800.00), 1);
  ck_assert_int_eq(equal_double(res.mount_last, 40300.00), 1);
  ck_assert_int_eq(equal_double(res.procents, 6300.00), 1);
  ck_assert_int_eq(equal_double(res.total, 246300.00), 1);

  /* *****  ***** */

  res = calculator_different(2300, 6, 0, 9);

#if IS_TEST_TURN_ON
  print_credit_data(res);
#endif
  ck_assert_int_eq(equal_double(res.mount, 400.58), 1);
  ck_assert_int_eq(equal_double(res.mount_last, 386.21), 1);
  ck_assert_int_eq(equal_double(res.procents, 60.38), 1);
  ck_assert_int_eq(equal_double(res.total, 2360.38), 1);

  /* *****  ***** */

  res = calculator_different(3830000, 78, 0, 14);

#if IS_TEST_TURN_ON
  print_credit_data(res);
#endif
  ck_assert_int_eq(equal_double(res.mount, 93785.90), 1);
  ck_assert_int_eq(equal_double(res.mount_last, 49675.43), 1);
  ck_assert_int_eq(equal_double(res.procents, 1764991.67), 1);
  ck_assert_int_eq(equal_double(res.total, 5594991.67), 1);

  /* *****  ***** */

  res = calculator_different(93830000, 94, 0, 23);

#if IS_TEST_TURN_ON
  print_credit_data(res);
#endif
  ck_assert_int_eq(equal_double(res.mount, 2796599.82), 1);
  ck_assert_int_eq(equal_double(res.mount_last, 1017323.49), 1);
  ck_assert_int_eq(equal_double(res.procents, 85424395.83), 1);
  ck_assert_int_eq(equal_double(res.total, 179254395.83), 1);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_calculator_credit_annuit_mount_test) {
  s_credit_data res;

  res = calculator_annuit(20000, 36, 0, 12);

  ck_assert_int_eq(equal_double(res.mount, 664.29), 1);
  ck_assert_int_eq(equal_double(res.procents, 3914.44), 1);
  ck_assert_int_eq(equal_double(res.total, 23914.44), 1);

  /* *****  ***** */

  res = calculator_annuit(2000, 48, 0, 48);

  ck_assert_int_eq(equal_double(res.mount, 94.36), 1);
  ck_assert_int_eq(equal_double(res.procents, 2529.28), 1);
  ck_assert_int_eq(equal_double(res.total, 4529.28), 1);

  /* *****  ***** */

  res = calculator_annuit(30000, 6, 0, 9);

  ck_assert_int_eq(equal_double(res.mount, 5132.07), 1);
  ck_assert_int_eq(equal_double(res.procents, 792.42), 1);
  ck_assert_int_eq(equal_double(res.total, 30792.42), 1);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_calculator_credit_annuit_years_test) {
  s_credit_data res;

  res = calculator_annuit(20000, 18, 1, 12);

  ck_assert_int_eq(equal_double(res.mount, 226.39), 1);
  ck_assert_int_eq(equal_double(res.procents, 28900.24), 1);
  ck_assert_int_eq(equal_double(res.total, 48900.24), 1);

  /* *****  ***** */

  res = calculator_annuit(2000, 4, 1, 48);

  ck_assert_int_eq(equal_double(res.mount, 94.36), 1);
  ck_assert_int_eq(equal_double(res.procents, 2529.28), 1);
  ck_assert_int_eq(equal_double(res.total, 4529.28), 1);

  /* *****  ***** */

  res = calculator_annuit(30000, 12, 1, 9);

  ck_assert_int_eq(equal_double(res.mount, 341.41), 1);
  ck_assert_int_eq(equal_double(res.procents, 19163.04), 1);
  ck_assert_int_eq(equal_double(res.total, 49163.04), 1);
}
END_TEST

// ********************************************************

void calculator_credit_test(TCase *tc1_1) {
  tcase_add_test(tc1_1, s21_calculator_credit_different_years_test);
  tcase_add_test(tc1_1, s21_calculator_credit_annuit_mount_test);
  tcase_add_test(tc1_1, s21_calculator_credit_annuit_years_test);
  tcase_add_test(tc1_1, s21_calculator_credit_different_mount_test);
}
