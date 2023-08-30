#include "../s21_credit_calc.h"
#include "../s21_smart_calc.h"
#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define IS_TEST_TURN_ON 0

void trim_str_num(char *p_res_, unsigned n_limit_);
int equal_double(double a_, double b_) { return (fabs(a_ - b_) < 1e-7); }
char *calculate_notation(char const *p_str_);
void remove_zeros(char *p_str_, unsigned limit_str_, int *p_is_error_);

// -------------------------------------------------------

char *str_to_postfix(char *str_);

int add_math_function(char const *p_src_, unsigned *pi_src_, s_stack **p_s_);
int is_check_valid_postfix(char *p_str_);

// -------------------------------------------------------

void push_to_stack_tmp(char *p_tmp_, s_stack **stack_, unsigned *pi_str_,
                       unsigned const size_tmp_);
void add_char_to_str(char **p_tmp_, char const ch_, unsigned i_str_,
                     unsigned *p_size_tmp_);
void add_str_to_str(char **p_dest_, char const *p_src_, unsigned *pi_dest_,
                    unsigned *p_size_dest_);
void check_end_resisze_str(char **p_str_, unsigned pi_str_, unsigned *pn_str_);
int is_digit(char ch_);
double calculate_numbers_mul(double num1_, char *str_, double num2_,
                             int *error_);
int is_math_function(char *str_);
double string_to_double(char const *str_);
char *double_to_string(double num_);
int is_letter(char ch_);
unsigned find_str(char const *str_, char const *needle_, int i_);
int is_find_in_stack_brackets(s_stack *s_);

// -------------------------------------------------------

#if IS_TEST_TURN_ON
void print_debug_str(char *str_, unsigned line_) {
  printf("\n-----------------------------------\n");
  printf("|\n");
  printf("|\n");
  printf("\nline => %u\n%s\n\n", line_, str_);
  printf("|\n");
  printf("|\n");
  printf("-----------------------------------\n");
}
#endif

// ********************************************************

void stack_functions_test(TCase *tc1_1);
void calculator_credit_test(TCase *tc1_1);

// ********************************************************

START_TEST(s21_trim_str_num_test) {
  unsigned n_src = 20;
  char *p_src = create_str(n_src);
  strncpy(p_src, "32.02139483", n_src);
  trim_str_num(p_src, 0);

  ck_assert_str_eq(p_src, "32");
  free_str(p_src);

  /* *****  ***** */

  p_src = create_str(n_src);
  strncpy(p_src, "32.02139483", n_src);
  trim_str_num(p_src, 1);

  ck_assert_str_eq(p_src, "32.0");
  free_str(p_src);

  /* *****  ***** */

  p_src = create_str(n_src);
  strncpy(p_src, "32.02139483", n_src);
  trim_str_num(p_src, 2);

  ck_assert_str_eq(p_src, "32.02");
  free_str(p_src);

  /* *****  ***** */

  p_src = create_str(n_src);
  strncpy(p_src, "32.02139483", n_src);
  trim_str_num(p_src, 3);

  ck_assert_str_eq(p_src, "32.021");
  free_str(p_src);

  /* *****  ***** */

  p_src = create_str(n_src);
  strncpy(p_src, "32.02139483", n_src);
  trim_str_num(p_src, 4);

  ck_assert_str_eq(p_src, "32.0213");
  free_str(p_src);

  /* *****  ***** */

  p_src = create_str(n_src);
  strncpy(p_src, "32.02139483", n_src);
  trim_str_num(p_src, 5);

  ck_assert_str_eq(p_src, "32.02139");
  free_str(p_src);

  /* *****  ***** */

  p_src = create_str(n_src);
  strncpy(p_src, "32.02139483", n_src);
  trim_str_num(p_src, 6);

  ck_assert_str_eq(p_src, "32.021394");
  free_str(p_src);

  /* *****  ***** */

  p_src = create_str(n_src);
  strncpy(p_src, "32.02139483", n_src);
  trim_str_num(p_src, 7);

  ck_assert_str_eq(p_src, "32.0213948");
  free_str(p_src);

  /* *****  ***** */

  p_src = create_str(n_src);
  strncpy(p_src, "32.02139483", n_src);
  trim_str_num(p_src, 8);

  ck_assert_str_eq(p_src, "32.02139483");
  free_str(p_src);

  /* *****  ***** */

  p_src = create_str(n_src);
  strncpy(p_src, "32.02139483", n_src);
  trim_str_num(p_src, 9);

  ck_assert_str_eq(p_src, "32.02139483");
  free_str(p_src);

  /* *****  ***** */

  p_src = create_str(n_src);
  strncpy(p_src, "32.02139483", n_src);
  trim_str_num(p_src, 9);

  ck_assert_str_eq(p_src, "32.02139483");
  free_str(p_src);

  /* *****  ***** */

  p_src = NULL;
  trim_str_num(p_src, 9);

  ck_assert_ptr_eq(p_src, NULL);
  free_str(p_src);

  /* *****  ***** */
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_calculate_notation_test) {
  char const *src = "32 ~";

  char *res = calculate_notation(src);
  ck_assert_str_eq(res, "-32");
#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  free_str(res);

  /* *****  ***** */

  src = "8 2 5 * + 1 3 2 * + 4 - /";

  res = calculate_notation(src);
#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_str_eq(res, "6");
  free_str(res);

  /* *****  ***** */
  res = calculate_notation("3 ~ 6 + -2 *");
#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_str_eq(res, "-6");
  free_str(res);

  /* *****  ***** */

  res = calculate_notation("9 ~");
#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_str_eq(res, "-9");
  free_str(res);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_remove_zeroes_test) {
  char n_src = 20;
  char *p_src = create_str(n_src);
  int is_error = 0;

  strncpy(p_src, "30.0000", n_src);

  remove_zeros(p_src, n_src, &is_error);

  ck_assert_str_eq(p_src, "30");
  ck_assert_int_eq(is_error, 0);
  free_str(p_src);

  /* *****  ***** */

  p_src = create_str(n_src);
  is_error = 0;

  strncpy(p_src, "30.3000", n_src);

  remove_zeros(p_src, n_src, &is_error);

  ck_assert_str_eq(p_src, "30.3");
  ck_assert_int_eq(is_error, 0);
  free_str(p_src);

  /* *****  ***** */

  p_src = create_str(n_src);
  is_error = 0;

  strncpy(p_src, "30.3300", n_src);

  remove_zeros(p_src, n_src, &is_error);

  ck_assert_str_eq(p_src, "30.33");
  ck_assert_int_eq(is_error, 0);
  free_str(p_src);

  /* *****  ***** */

  p_src = create_str(n_src);
  is_error = 0;

  strncpy(p_src, "30.3390", n_src);

  remove_zeros(p_src, n_src, &is_error);

  ck_assert_str_eq(p_src, "30.339");
  ck_assert_int_eq(is_error, 0);
  free_str(p_src);

  /* *****  ***** */

  p_src = create_str(n_src);
  is_error = 0;

  strncpy(p_src, "30.3391", n_src);

  remove_zeros(p_src, n_src, &is_error);

  ck_assert_str_eq(p_src, "30.3391");
  ck_assert_int_eq(is_error, 0);
  free_str(p_src);

  /* *****  ***** */

  p_src = create_str(n_src);
  is_error = 0;

  strncpy(p_src, "0", n_src);

  remove_zeros(p_src, n_src, &is_error);

  ck_assert_str_eq(p_src, "0");
  ck_assert_int_eq(is_error, 0);
  free_str(p_src);

  /* *****  ***** */

  p_src = create_str(n_src);
  is_error = 0;

  strncpy(p_src, "x", n_src);

  remove_zeros(p_src, n_src, &is_error);

  ck_assert_str_eq(p_src, "x");
  ck_assert_int_eq(is_error, 0);
  free_str(p_src);

  /* *****  ***** */

  p_src = create_str(n_src);
  is_error = 0;

  strncpy(p_src, "0.0", n_src);

  remove_zeros(p_src, n_src, &is_error);

  ck_assert_str_eq(p_src, "0");
  ck_assert_int_eq(is_error, 0);
  free_str(p_src);

  /* *****  ***** */

  p_src = create_str(n_src);
  is_error = 0;

  strncpy(p_src, "0.03", n_src);

  remove_zeros(p_src, n_src, &is_error);

  ck_assert_str_eq(p_src, "0.03");
  ck_assert_int_eq(is_error, 0);
  free_str(p_src);

  /* *****  ***** */

  p_src = NULL;
  is_error = 0;

  remove_zeros(p_src, n_src, &is_error);

  ck_assert_ptr_eq(p_src, NULL);
  ck_assert_int_eq(is_error, 0);
  free_str(p_src);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_check_valid_postfix_test) {
  char *src = "122.33 33 +";
  int res = is_check_valid_postfix(src);

  ck_assert_int_eq(res, 1);

  /* *****  ***** */

  src = "122.33 33 + ~";
  res = is_check_valid_postfix(src);
  ck_assert_int_eq(res, 1);

  /* *****  ***** */

  src = "122.33 33 + * ~";
  res = is_check_valid_postfix(src);
  ck_assert_int_eq(res, 0);

  /* *****  ***** */

  src = "3 4 2 * 1 5 - 2 ^ / +";
  res = is_check_valid_postfix(src);
  ck_assert_int_eq(res, 1);

  /* *****  ***** */

  src = "3 4 2 * 1 5 - 2 ^ / / +";
  res = is_check_valid_postfix(src);
  ck_assert_int_eq(res, 0);

  /* *****  ***** */

  src = "3 4 2 * 1 5 - - 2 ^ / +";
  res = is_check_valid_postfix(src);
  ck_assert_int_eq(res, 0);

  /* *****  ***** */

  src = "3 4 2 * 1 5 - 2 ^ / + ~";
  res = is_check_valid_postfix(src);
  ck_assert_int_eq(res, 1);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_add_math_function_test) {
  s_stack *dest = NULL;
  char *src = "There srcsis nolnmod spooon. cosalog";
  unsigned n_src = strlen(src);

  for (unsigned i = 0; i < n_src; ++i) {
    add_math_function(src, &i, &dest);
  }

  char *tmp = pop_stack(&dest);
  ck_assert_str_eq(tmp, "log");
  free_str(tmp);

  tmp = pop_stack(&dest);
  ck_assert_str_eq(tmp, "cos");
  free_str(tmp);

  tmp = pop_stack(&dest);
  ck_assert_str_eq(tmp, "mod");
  free_str(tmp);

  tmp = pop_stack(&dest);
  ck_assert_str_eq(tmp, "ln");
  free_str(tmp);

  tmp = pop_stack(&dest);
  ck_assert_ptr_eq(tmp, NULL);
  tmp = free_str(tmp);

  free(dest);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_str_to_postfix_test) {
  char *res = str_to_postfix("3 + 4 * 2 / (1 - 5) ^ 2");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 4 2 * 1 5 - 2 ^ / +");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("398 + 4487 * 224 / (128 - 548) ^ 20");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "398 4487 224 * 128 548 - 20 ^ / +");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("3.98 + 4 * 2.0 / (1.5 - 5) ^ 2");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3.98 4 2.0 * 1.5 5 - 2 ^ / +");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(3 + 4) * (2 / (1 - 5) ^ 2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 4 + 2 1 5 - 2 ^ / *");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(3 + 4) * ((2) / (1 - 5) ^ 2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 4 + 2 1 5 - 2 ^ / *");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(3 + 4) * ((2.8) / (1 - 5) ^ 2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 4 + 2.8 1 5 - 2 ^ / *");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(-3 + 4) * ((2.8) / (1 - 5) ^ 2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 ~ 4 + 2.8 1 5 - 2 ^ / *");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(-3 + 4) * ((-2.8) / (1 - 5) ^ 2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 ~ 4 + 2.8 ~ 1 5 - 2 ^ / *");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(-3 + 4) * ((-2.8) / (-1 - 5) ^ +2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 ~ 4 + 2.8 ~ 1 ~ 5 - ^ / 2 + *");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(-3 + 4) * ((-2.8) / (-1 - 5) ^ +(2))");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 ~ 4 + 2.8 ~ 1 ~ 5 - ^ / 2 + *");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(-3 + 4) * ((-2.8) / (-1 - 5) ^ +(2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_ptr_eq(res, NULL);

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(-3 + 4) * ((-2.8) / (1 - 5) ^ 2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 ~ 4 + 2.8 ~ 1 5 - 2 ^ / *");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("-(122.33 + 33)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "122.33 33 + ~");

  free(res);

  /* *****  ***** */

  res = str_to_postfix("-(122 + 33) + 28 - ((22 - 3) + (33 - 2))");
#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "122 33 + ~ 28 + 22 3 - 33 2 - + -");
  free(res);

  /* *****  ***** */

  res = str_to_postfix("-(-42)+1");
#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "42 ~ ~ 1 +");
  free(res);

  /* *****  ***** */

  res = str_to_postfix("2 / (3 - (4 + (5 * 6))) ");
#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "2 3 4 5 6 * + - /");
  free(res);

  /* *****  ***** */

  res = str_to_postfix("-( -(129.0000000) * 6 )");
#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "129.0000000 ~ 6 * ~");
  free(res);

  /* *****  ***** */

  res = str_to_postfix("(atn(8)*sqrt(4))+((ln(88.2)*ln(8.3))-3)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "8 atn 4 sqrt * 88.2 ln 8.3 ln * 3 - +");
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(aton(8)*sqrt(4))+((ln(88.2)*ln(8.3))-3)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_ptr_eq(res, NULL);
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(atn(8)*sqrt(4))+((ln(88.2)*ln(8.3)) - 3)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "8 atn 4 sqrt * 88.2 ln 8.3 ln * 3 - +");
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(-3 + 6) * -2");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 ~ 6 + 2 ~ *");
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(84 + x * (x - 473.938 * x - (x / x)))");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "84 x x 473.938 x * - x x / - * +");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix(
      "(84 + x * (x - 473.938 * x - (x / x * atn(x)))) + cos(x) * mod(87.44)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(
      res, "84 x x 473.938 x * - x x / x atn * - * + x cos 87.44 mod * +");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(84+x*(x-473.938*x-(x/x*atn(x))))+cos(x)*mod(87.44)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(
      res, "84 x x 473.938 x * - x x / x atn * - * + x cos 87.44 mod * +");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("((x * x / x + 0.1)) + (x * x * x * x * x)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "x x * x / 0.1 + x x * x * x * x * +");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("alg(1) * atn(2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "1 alg 2 atn *");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("3--3");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_ptr_eq(res, NULL);

  free_str(res);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_add_str_to_str_test) {
  unsigned size_tmp = 2;
  char *tmp = create_str(size_tmp);
  unsigned i = 0;

  add_str_to_str(&tmp, "There ", &i, &size_tmp);
  add_str_to_str(&tmp, "is ", &i, &size_tmp);
  add_str_to_str(&tmp, "", &i, &size_tmp);
  add_str_to_str(&tmp, "no ", &i, &size_tmp);
  add_str_to_str(&tmp, "spoon", &i, &size_tmp);
  add_str_to_str(&tmp, ".", &i, &size_tmp);

  ck_assert_str_eq(tmp, "There is no spoon.");

  free_str(tmp);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_push_to_stack_tmp_test) {
  unsigned size_tmp = 2;
  char *tmp = create_str(size_tmp);
  unsigned i = 0;
  s_stack *stack = NULL;

  add_char_to_str(&tmp, 'a', i++, &size_tmp);
  add_char_to_str(&tmp, 'b', i++, &size_tmp);
  push_to_stack_tmp(tmp, &stack, &i, size_tmp);

  add_char_to_str(&tmp, 'c', i++, &size_tmp);
  add_char_to_str(&tmp, 'd', i++, &size_tmp);
  push_to_stack_tmp(tmp, &stack, &i, size_tmp);

  add_char_to_str(&tmp, 'e', i++, &size_tmp);
  add_char_to_str(&tmp, 'f', i++, &size_tmp);
  push_to_stack_tmp(tmp, &stack, &i, size_tmp);

  tmp = free_str(tmp);
  tmp = pop_stack(&stack);
  ck_assert_str_eq(tmp, "ef");

  /* *****  ***** */

  tmp = free_str(tmp);
  tmp = pop_stack(&stack);
  ck_assert_str_eq(tmp, "cd");

  /* *****  ***** */

  tmp = free_str(tmp);
  tmp = pop_stack(&stack);
  ck_assert_str_eq(tmp, "ab");

  /* *****  ***** */

  free_stack(&stack);
  free_str(tmp);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_add_char_to_str_test) {
  unsigned size_tmp = 2;
  char *tmp = create_str(size_tmp);

  for (unsigned i = 0; i <= 9; ++i) {
    add_char_to_str(&tmp, i + 48, i, &size_tmp);
  }

  ck_assert_str_eq(tmp, "0123456789");
  free_str(tmp);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_check_and_resize_str_test) {
  unsigned size_str = 2;
  char *str = create_str(size_str);

  for (unsigned i = 0; i < 9; ++i) {
    check_end_resisze_str(&str, i, &size_str);
    str[i] = i + 48;
  }

  ck_assert_str_eq(str, "012345678");
  free_str(str);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_is_digit_test) {
  int res = is_digit('k');
  ck_assert_int_eq(res, 0);

  /* *****  ***** */

  res = is_digit('l');
  ck_assert_int_eq(res, 0);

  /* *****  ***** */

  res = is_digit('1');
  ck_assert_int_eq(res, 1);

  /* *****  ***** */

  for (int i = 0; i <= 9; ++i)
    ck_assert_int_eq(res, 1);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_is_math_function_test) {
  char *str = "cos";

  int is_success = is_math_function(str);
  ck_assert_int_eq(is_success, 1);

  /* *****  ***** */

  str = "sin";
  is_success = is_math_function(str);
  ck_assert_int_eq(is_success, 1);

  /* *****  ***** */

  str = "tan";
  is_success = is_math_function(str);
  ck_assert_int_eq(is_success, 1);

  /* *****  ***** */

  str = "acs";
  is_success = is_math_function(str);
  ck_assert_int_eq(is_success, 1);

  /* *****  ***** */

  str = "asn";
  is_success = is_math_function(str);
  ck_assert_int_eq(is_success, 1);

  /* *****  ***** */

  str = "atn";
  is_success = is_math_function(str);
  ck_assert_int_eq(is_success, 1);

  /* *****  ***** */

  str = "sqrt";
  is_success = is_math_function(str);
  ck_assert_int_eq(is_success, 1);

  /* *****  ***** */

  str = "ln";
  is_success = is_math_function(str);
  ck_assert_int_eq(is_success, 1);

  /* *****  ***** */

  str = "log";
  is_success = is_math_function(str);
  ck_assert_int_eq(is_success, 1);

  /* *****  ***** */

  str = "alog";
  is_success = is_math_function(str);
  ck_assert_int_eq(is_success, 0);

  /* *****  ***** */

  str = "piter log";
  is_success = is_math_function(str);
  ck_assert_int_eq(is_success, 0);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_calculate_numbers_test) {
  int is_error = 0;
  double res = calculate_numbers_mul(33, "*", 2, &is_error);
  ck_assert_double_eq(res, 66.0);
  ck_assert_int_eq(is_error, 0);

  /* *****  ***** */

  res = calculate_numbers_mul(33.5, "+", 2, &is_error);
  ck_assert_double_eq(res, 35.5);
  ck_assert_int_eq(is_error, 0);

  /* *****  ***** */

  res = calculate_numbers_mul(33.5, "-", 2, &is_error);
  ck_assert_double_eq(res, 31.5);
  ck_assert_int_eq(is_error, 0);

  /* *****  ***** */

  res = calculate_numbers_mul(33.5, "/", 2, &is_error);
  ck_assert_int_eq(1, equal_double(res, 16.75));
  ck_assert_int_eq(is_error, 0);

  /* *****  ***** */

  res = calculate_numbers_mul(1.6, "%", 1.2, &is_error);
  ck_assert_int_eq(1, equal_double(res, 0.4));
  ck_assert_int_eq(is_error, 0);

  /* *****  ***** */

  res = calculate_numbers_mul(1.6, NULL, 1.2, &is_error);
  ck_assert_int_eq(1, equal_double(res, 0));
  ck_assert_int_eq(is_error, 1);

  /* *****  ***** */

  res = calculate_numbers_mul(1.6, "kdgh", 1.2, &is_error);
  ck_assert_int_eq(1, equal_double(res, 0));
  ck_assert_int_eq(is_error, 1);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_calculate_polska_notation1_test) {
  char *res = calculate_notation("3 ~ 6 + 2 ~ *");
#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_str_eq(res, "-6");
  free_str(res);

  /* *****  ***** */

  res = calculate_notation(NULL);
#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_str_eq(res, "error");
  free_str(res);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_double_to_string_test) {
  char *res = double_to_string(33.8);

  ck_assert_str_eq(res, "33.80000000000");
  free(res);

  /* *****  ***** */

  res = double_to_string(12345.12345);
  ck_assert_str_eq(res, "12345.12344999999");
  free(res);

  /* *****  ***** */

  res = double_to_string(1.94);
  ck_assert_str_eq(res, "1.94000000000");
  free(res);

  /* *****  ***** */
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_find_brackets_test) {
  s_stack *s = NULL;

  push_stack(&s, "there");
  push_stack(&s, "is");
  push_stack(&s, "no");
  push_stack(&s, "spoon");

  int res = is_find_in_stack_brackets(s);

  ck_assert_int_eq(res, 0);

  /* *****  ***** */
  push_stack(&s, "(");

  res = is_find_in_stack_brackets(s);

  ck_assert_int_eq(res, 1);

  /* *****  ***** */

  pop_free_stack(&s);
  res = is_find_in_stack_brackets(s);
  ck_assert_int_eq(res, 0);

  /* *****  ***** */

  push_stack(&s, ")");
  res = is_find_in_stack_brackets(s);
  ck_assert_int_eq(res, 1);
  free_stack(&s);

  /* *****  ***** */

  push_stack(&s, ")");
  push_stack(&s, "there");
  res = is_find_in_stack_brackets(s);
  ck_assert_int_eq(res, 1);
  free_stack(&s);

  /* *****  ***** */

  push_stack(&s, "(");
  push_stack(&s, "there");
  res = is_find_in_stack_brackets(s);
  ck_assert_int_eq(res, 1);
  free_stack(&s);

  /* *****  ***** */

  res = is_find_in_stack_brackets(s);
  ck_assert_int_eq(res, 0);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_is_letter_test) {
  char ch = 'a';

  ch = is_letter(ch);
  ck_assert_int_eq(ch, 1);

  /* *****  ***** */

  ch = 'z';
  ch = is_letter(ch);
  ck_assert_int_eq(ch, 1);

  /* *****  ***** */

  ch = '8';
  ch = is_letter(ch);
  ck_assert_int_eq(ch, 0);

  /* *****  ***** */

  ch = 'b';
  ch = is_letter(ch);
  ck_assert_int_eq(ch, 1);

  /* *****  ***** */

  ch = 'A';
  ch = is_letter(ch);
  ck_assert_int_eq(ch, 1);

  /* *****  ***** */

  ch = '?';
  ch = is_letter(ch);
  ck_assert_int_eq(ch, 0);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_string_to_double_test) {
  char *b = "88.43";
  double d = 0;

  d = string_to_double(b);
  ck_assert_int_eq(equal_double(d, 88.43), 1);

  b = "39948.3283";

  d = string_to_double(b);
  ck_assert_int_eq(equal_double(d, 39948.3283), 1);

  b = "-1";

  d = string_to_double(b);
  ck_assert_int_eq(equal_double(d, -1), 1);

  b = "+1";

  d = string_to_double(b);
  ck_assert_int_eq(equal_double(d, 1), 1);

  b = "984938.9392039948";

  d = string_to_double(b);

  ck_assert_int_eq(equal_double(d, 984938.9392039948), 1);
  ck_assert_int_eq(equal_double(d, 984938.939203994), 1);
  ck_assert_int_eq(equal_double(d, 984938.93920399), 1);
  ck_assert_int_eq(equal_double(d, 984938.9392039), 1);
  ck_assert_int_eq(equal_double(d, 984938.9392038), 0);

  b = "123456789123";

  d = string_to_double(b);
  ck_assert_int_eq(equal_double(d, 123456789123), 1);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_char_to_str_test) {
  char str[BUFF_STR_CHAR] = {"\0"};

  char_to_str('a', str);

  ck_assert_str_ne(str, "b");
  ck_assert_str_eq(str, "a");
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_find_str_test) {
  const char *str = "there is no spoon.";
  const char *needle = "the";
  int i = 0;
  int n = find_str(str, needle, i);

  ck_assert_int_eq(n, 2);

  /* *****  ***** */

  str = "there is no spoon.";
  needle = "there";
  i = 0;

  n = find_str(str, needle, i);
  ck_assert_int_eq(n, 4);

  /* *****  ***** */

  str = "there is no spoon.";
  needle = "ehere";
  i = 0;

  n = find_str(str, needle, i);
  ck_assert_int_eq(n, -1);

  /* *****  ***** */

  str = "there is no spoon.";
  needle = "t";
  i = 0;

  n = find_str(str, needle, i);
  ck_assert_int_eq(n, 0);

  /* *****  ***** */
  str = "cos(2 * x)";
  needle = "cos";
  i = 0;

  n = find_str(str, needle, i);
  ck_assert_int_eq(n, 2);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_full_calculation_smart_test) {
  char *res = str_to_postfix("(8 + 2 * 5) / (1 + 3 * 2 - 4)");
  char *pols = NULL;

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_str_eq(res, "8 2 5 * + 1 3 2 * + 4 - /");

  pols = calculate_notation(res);

  ck_assert_str_eq(pols, "6");
  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("35 * (54 - 9)");
  pols = NULL;

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_str_eq(res, "35 54 9 - *");

  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "1575");
  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("4 ^ 2");
  pols = NULL;

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_str_eq(res, "4 2 ^");

  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "16");
  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("4 ^ 2 + (2* 3.8) - 3");
  pols = NULL;

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "20.6");
  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("(76.3 - 7.8 * 44.002) - ((87 / 3.8) + 9.9 - 4)");
  pols = NULL;

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_str_eq(res, "76.3 7.8 44.002 * - 87 3.8 / 9.9 + 4 - -");

  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "-295.7103368");
  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("((84.998  * 3.94 * 2.2) - (778.9) ^ 2)");
  pols = NULL;

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_str_eq(res, "84.998 3.94 * 2.2 * 778.9 2 ^ -");

  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "-605948.4473359");
  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res =
      str_to_postfix("849.938 * sin(44) + 74.9 * ((40.9 * cos(20.8)) - 57.8)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_str_eq(res, "849.938 44 sin * 74.9 40.9 20.8 cos * 57.8 - * +");
  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "-5449.4537614");
  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("(-3 + 6) * -2");
  pols = NULL;

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 ~ 6 + 2 ~ *");

  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "-6");
  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("(-3 + 4) * ((2.8) / (1 - 5) ^ 2)");
#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_str_eq(res, "3 ~ 4 + 2.8 1 5 - 2 ^ / *");
  pols = calculate_notation(res);
#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "0.175");
  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("(-3 + (4.9483 / 3.9)) * ((sin(2.8)) / (1 - 5) ^ 2)");
#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  pols = calculate_notation(res);
#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "-0.0362458");
  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("atn(sin(49.99)) * 30.8");
#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  pols = calculate_notation(res);
#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "-8.1800322");
  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("atn(log(9.39)) * 30.8 * sin(9)");
#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  pols = calculate_notation(res);
#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "9.7933808");
  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("acs(1) + ln(44.2) * asn(1)");
#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  pols = calculate_notation(res);
#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "5.9513149");
  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("tan(3.94) * 392.2 / (2.8 + 4.93992) * 2");
#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  pols = calculate_notation(res);
#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "104.0164484");
  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("atn(sin(49.99)) * 30.8");
#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  pols = calculate_notation(res);
#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "-8.1800322");
  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("sqrt(49.29) * ((((34.2 - 2) - 44.9) * 2.843) / 4.83)");
#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  pols = calculate_notation(res);
#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "-52.4822999");
  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("cos(1)");
#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  pols = calculate_notation(res);
#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "0.5403023");
  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("(-3 + 4) * ((-2.8) / (1 - 5) ^ 2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 ~ 4 + 2.8 ~ 1 5 - 2 ^ / *");

  pols = calculate_notation(res);
#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "-0.175");

  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("(-3+ 4)* ((-2.8)/(1-5) ^ 2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 ~ 4 + 2.8 ~ 1 5 - 2 ^ / *");

  pols = calculate_notation(res);
#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "-0.175");

  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("sin(2)*cos(2)*3+4*(25-5)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  pols = calculate_notation(res);
#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(res, "2 sin 2 cos * 3 * 4 25 5 - * +");

  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("sin(2)*cos(2)*");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  pols = calculate_notation(res);
#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "error");

  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("sin(2)*cos(2)*");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "error");

  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("32 * / 90- 1");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "error");

  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("32 % 3");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "2");

  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("32.939 % 3.329");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "2.978");

  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("3/+");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  pols = calculate_notation(res);
  ck_assert_str_eq(pols, "error");

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("cos(3) /cos(8)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  pols = calculate_notation(res);
  ck_assert_str_eq(pols, "6.8040705");

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("asn(0.3) /asn(0.8)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "0.3285821");

  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("sin(8.3) / sin(0.1)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "9.0367720");

  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("(tan(8.3)*atn(0.1))");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "-0.2084447");

  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("(acs(0.5)*ln(8.8))");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "2.2773946");

  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("(acs(0.5)^ln(8.8))");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "1.1054962");

  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("atn(0.3) + (-10) * sin(-10)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "-5.1487543");

  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("*2");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  pols = calculate_notation(res);
#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_str_eq(pols, "error");

  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("-(-42)+1");

  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif
  ck_assert_str_eq(pols, "43");

  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("kk");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif
  ck_assert_str_eq(pols, "error");

  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res = str_to_postfix("2 + asn");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  // ck_assert_ptr_eq(res, NULL);
  pols = calculate_notation(res);
  ck_assert_str_eq(pols, "error");

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  free_str(res);
  free_str(pols);

  /* *****  ***** */
  res = str_to_postfix("kk");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif
  ck_assert_str_eq(pols, "error");

  free_str(res);
  free_str(pols);

  /* *****  ***** */

  res =
      str_to_postfix("849.938 * sin(44) + 74.9 * ((40.9 * cos(20.8)) - 57.8)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_str_eq(res, "849.938 44 sin * 74.9 40.9 20.8 cos * 57.8 - * +");
  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "-5449.4537614");

  free(res);
  free(pols);

  /* *****  ***** */

  res = str_to_postfix("((2 + 3) * (asn(0.3) + 3))");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_str_eq(res, "2 3 + 0.3 asn 3 + *");
  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "16.5234632");

  free(res);
  free(pols);

  /* *****  ***** */

  res = str_to_postfix("-(-(12 / 9 * 3) * 6)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  pols = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pols, __LINE__);
#endif

  ck_assert_str_eq(pols, "23.9999999");

  free(res);
  free(pols);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_arifmetic_operations2_test) {
  char *res = str_to_postfix("(-3 + 4) * ((2.8) / (1 - 5) ^ 2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 ~ 4 + 2.8 1 5 - 2 ^ / *");

  char *pol = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pol, __LINE__);
#endif

  free_str(res);
  free_str(pol);

  res = str_to_postfix("tan(-10)");
  pol = NULL;

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_str_eq(res, "10 ~ tan");

  pol = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pol, __LINE__);
#endif

  ck_assert_str_eq(pol, "-0.6483608");
  free_str(res);
  free_str(pol);

  /* *****  ***** */

  res = str_to_postfix("tan(-9)");
  pol = NULL;

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_str_eq(res, "9 ~ tan");

  pol = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pol, __LINE__);
#endif

  ck_assert_str_eq(pol, "0.4523156");
  free_str(res);
  free_str(pol);

  /* *****  ***** */

  res = str_to_postfix("tan(-8)");
  pol = NULL;

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_str_eq(res, "8 ~ tan");

  pol = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pol, __LINE__);
#endif

  ck_assert_str_eq(pol, "6.7997114");
  free_str(res);
  free_str(pol);

  /* *****  ***** */

  res = str_to_postfix("tan(-7)");
  pol = NULL;

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_str_eq(res, "7 ~ tan");

  pol = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(pol, __LINE__);
#endif

  ck_assert_str_eq(pol, "-0.8714479");
  free_str(res);
  free_str(pol);

  /* *****  ***** */

  res = str_to_postfix("*2");
  pol = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_str_eq(pol, "error");
  free_str(res);
  free_str(pol);

  /* *****  ***** */

  res = str_to_postfix("**2");
  pol = calculate_notation(res);

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_str_eq(pol, "error");
  free_str(res);
  free_str(pol);

  /* *****  ***** */

  res = str_to_postfix("2*");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  pol = calculate_notation(res);
#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(pol, "error");
  free_str(res);
  free_str(pol);

  /* *****  ***** */
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_arifmetic_operations_test) {
  char *res = str_to_postfix("sin(2) * cos(2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "2 sin 2 cos *");
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("-(-42) + -(44)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "42 ~ ~ 44 ~ +");
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("-(-42) + -((44))");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "42 ~ ~ 44 ~ +");
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("--42");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_ptr_eq(res, NULL);
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("-(-42)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "42 ~ ~");
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("cos(2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "2 cos");
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("cos(2) * 2.48 * (2 + 2 - (log(4))) ");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "2 cos 2.48 * 2 2 + 4 log - *");
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(atn(8) * sqrt(4)) + ((ln(88.2) * ln(8.3)) - 3)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "8 atn 4 sqrt * 88.2 ln 8.3 ln * 3 - +");
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(atn(8)*sqrt(4))+((ln(88.2)*ln(8.3)) -3)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "8 atn 4 sqrt * 88.2 ln 8.3 ln * 3 - +");
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(atn(8)*sqrt(4))+((ln(88.2)*ln(8.3)) - 3)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "8 atn 4 sqrt * 88.2 ln 8.3 ln * 3 - +");
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(atn(8)*sqrt(4))+((ln(88.2)*ln(8.3))-3)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "8 atn 4 sqrt * 88.2 ln 8.3 ln * 3 - +");
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(-3+ 4)* ((-2.8)/(1-5) ^ 2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 ~ 4 + 2.8 ~ 1 5 - 2 ^ / *");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("ln(8.3) ^ log(8.8) / ((sin(5) - (atn(9))))");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "8.3 ln 8.8 log ^ 5 sin 9 atn - /");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("32 - -3");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif
  ck_assert_ptr_eq(res, NULL);

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("32--3");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_ptr_eq(res, NULL);

  free_str(res);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_str_to_polska_test) {
  char *res = str_to_postfix("3 + 4 * 2 / (1 - 5) ^ 2");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 4 2 * 1 5 - 2 ^ / +");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("398 + 4487 * 224 / (128 - 548) ^ 20");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "398 4487 224 * 128 548 - 20 ^ / +");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("3.98 + 4 * 2.0 / (1.5 - 5) ^ 2");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3.98 4 2.0 * 1.5 5 - 2 ^ / +");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(3 + 4) * (2 / (1 - 5) ^ 2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 4 + 2 1 5 - 2 ^ / *");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(3 + 4) * ((2) / (1 - 5) ^ 2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 4 + 2 1 5 - 2 ^ / *");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(3 + 4) * ((2.8) / (1 - 5) ^ 2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 4 + 2.8 1 5 - 2 ^ / *");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(-3 + 4) * ((2.8) / (1 - 5) ^ 2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 ~ 4 + 2.8 1 5 - 2 ^ / *");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(-3 + 4) * ((-2.8) / (1 - 5) ^ 2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 ~ 4 + 2.8 ~ 1 5 - 2 ^ / *");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(-3 + 4) * ((-2.8) / (-1 - 5) ^ +2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 ~ 4 + 2.8 ~ 1 ~ 5 - ^ / 2 + *");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(-3 + 4) * ((-2.8) / (-1 - 5) ^ +(2))");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 ~ 4 + 2.8 ~ 1 ~ 5 - ^ / 2 + *");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(-3 + 4) * ((-2.8) / (-1 - 5) ^ +(2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_ptr_eq(res, NULL);

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(-3 + 4) * ((-2.8) / (1 - 5) ^ 2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 ~ 4 + 2.8 ~ 1 5 - 2 ^ / *");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(atn(8)*sqrt(4))+((ln(88.2)*ln(8.3))-3)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "8 atn 4 sqrt * 88.2 ln 8.3 ln * 3 - +");
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(atn(8)*sqrt(4))+((ln(88.2)*ln(8.3)) - 3)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "8 atn 4 sqrt * 88.2 ln 8.3 ln * 3 - +");
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(-3 + 6) * -2");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "3 ~ 6 + 2 ~ *");
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(84 + x * (x - 473.938 * x - (x / x)))");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "84 x x 473.938 x * - x x / - * +");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix(
      "(84 + x * (x - 473.938 * x - (x / x * atn(x)))) + cos(x) * mod(87.44)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(
      res, "84 x x 473.938 x * - x x / x atn * - * + x cos 87.44 mod * +");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("(84+x*(x-473.938*x-(x/x*atn(x))))+cos(x)*mod(87.44)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(
      res, "84 x x 473.938 x * - x x / x atn * - * + x cos 87.44 mod * +");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("((x * x / x + 0.1)) + (x * x * x * x * x)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "x x * x / 0.1 + x x * x * x * x * +");

  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("alg(1) * atn(2)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_str_eq(res, "1 alg 2 atn *");

  free_str(res);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_error_test) {
  char *res = str_to_postfix("sin(2) * cos(2) * x + x (25 - x");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_ptr_eq(res, NULL);
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("sin(2) * cos(2 * x + x (25 - x)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_ptr_eq(res, NULL);
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("sin(2 * cos(2 * x + x (25 - x)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_ptr_eq(res, NULL);
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("sin 2) * cos(2 * x + x (25 - x)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_ptr_eq(res, NULL);
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("sin(2) * cos(2) * x + x (25 - x)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_ptr_ne(res, NULL);
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("sin() * cos(2) * x + x (25 - x)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_ptr_eq(res, NULL);
  free_str(res);

  /* *****  ***** */

  res = str_to_postfix("sin * cos(2) * x + x (25 - x)");

#if IS_TEST_TURN_ON
  print_debug_str(res, __LINE__);
#endif

  ck_assert_ptr_eq(res, NULL);
  free_str(res);
}
END_TEST

// -------------------------------------------------------

void help_functions_test(TCase *tc1_1) {
  tcase_add_test(tc1_1, s21_char_to_str_test);
  tcase_add_test(tc1_1, s21_string_to_double_test);
  tcase_add_test(tc1_1, s21_double_to_string_test);
  tcase_add_test(tc1_1, s21_is_letter_test);
  tcase_add_test(tc1_1, s21_find_brackets_test);
  tcase_add_test(tc1_1, s21_is_math_function_test);
  tcase_add_test(tc1_1, s21_is_digit_test);
  tcase_add_test(tc1_1, s21_check_and_resize_str_test);
  tcase_add_test(tc1_1, s21_add_char_to_str_test);
  tcase_add_test(tc1_1, s21_push_to_stack_tmp_test);
  tcase_add_test(tc1_1, s21_add_str_to_str_test);
}

void help_functions2_test(TCase *tc1_1) {
  tcase_add_test(tc1_1, s21_find_str_test);
  tcase_add_test(tc1_1, s21_add_math_function_test);
  tcase_add_test(tc1_1, s21_trim_str_num_test);
}

void polska_notacia_test(TCase *tc1_1) {
  tcase_add_test(tc1_1, s21_str_to_polska_test);
  tcase_add_test(tc1_1, s21_arifmetic_operations2_test);
}

void arifmetic_operations_test(TCase *tc1_1) {
  tcase_add_test(tc1_1, s21_arifmetic_operations_test);
}

void error_operations_test(TCase *tc1_1) {
  tcase_add_test(tc1_1, s21_error_test);
}

void calculate_polska_notation_test(TCase *tc1_1) {
  tcase_add_test(tc1_1, s21_calculate_numbers_test);
  tcase_add_test(tc1_1, s21_calculate_polska_notation1_test);
  tcase_add_test(tc1_1, s21_calculate_notation_test);
}

void full_smart_calculation_test(TCase *tc1_1) {
  tcase_add_test(tc1_1, s21_full_calculation_smart_test);
  tcase_add_test(tc1_1, s21_check_valid_postfix_test);
  tcase_add_test(tc1_1, s21_str_to_postfix_test);
  tcase_add_test(tc1_1, s21_remove_zeroes_test);
  tcase_add_test(tc1_1, s21_full_calculation_smart_test);
}

// -------------------------------------------------------

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc1_1);

  calculator_credit_test(tc1_1);
  stack_functions_test(tc1_1);
  help_functions_test(tc1_1);
  help_functions2_test(tc1_1);
  polska_notacia_test(tc1_1);
  arifmetic_operations_test(tc1_1);

  error_operations_test(tc1_1);
  calculate_polska_notation_test(tc1_1);

  full_smart_calculation_test(tc1_1);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
