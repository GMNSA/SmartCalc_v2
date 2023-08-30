#include "../s21_stack.h"
#include <check.h>
#include <stdlib.h>

#define IS_TEST_TURN_ON 0

// -------------------------------------------------------

void print_stack(s_stack *stack_) {
  if (stack_) {
    printf("size: %ld - ", stack_->size);

    s_stack *node = stack_;
    while (node) {
      printf(" %s ", (char *)node->p_value);
      node = node->p_prev;
    }
  } else {
    printf("null\n");
  }

  printf("\n");
}

/* *****  ***** */

void print_reverse_stack(s_stack *stack_) {
  if (stack_) {
    printf("size: %ld ==> ", stack_->size);

    s_stack *node = stack_;
    while (node->p_prev) {
      node = node->p_prev;
    }
    while (node) {
      printf(" %s ", (char *)node->p_value);
      node = node->p_next;
    }
  } else {
    printf("null\n");
  }

  printf("\n");
}

// -------------------------------------------------------

START_TEST(s21_string_to_stack_test) {
  char *str = "21 22 23 24";
  char *res = NULL;
  s_stack *stack = NULL;

  stack = string_to_stack(str);

#if IS_TEST_TURN_ON
  print_stack(stack);
#endif

  ck_assert_int_eq(is_empty_stack(stack), 0);
  ck_assert_int_eq(stack->size, 4);

  res = pop_stack(&stack);
  ck_assert_str_eq(res, "24");
  res = free_str(res);

  free_stack(&stack);

  /* *****  ***** */

  str = "21 22 23 24  ";
  stack = string_to_stack(str);

  ck_assert_int_eq(is_empty_stack(stack), 0);
  ck_assert_int_eq(stack->size, 4);

#if IS_TEST_TURN_ON
  print_stack(stack);
#endif
  res = pop_stack(&stack);
  ck_assert_str_eq(res, "24");
  res = free_str(res);

  free_stack(&stack);

  /* *****  ***** */

  str = "21 22 23 24        ";
  stack = string_to_stack(str);

  ck_assert_int_eq(is_empty_stack(stack), 0);
  ck_assert_int_eq(stack->size, 4);

#if IS_TEST_TURN_ON
  print_stack(stack);
#endif
  res = pop_stack(&stack);
  ck_assert_str_eq(res, "24");
  res = free_str(res);
  res = pop_stack(&stack);
  ck_assert_str_eq(res, "23");
  res = free_str(res);

  free_stack(&stack);

  /* *****  ***** */

  str = "       21 22 23 24        ";
  stack = string_to_stack(str);

  ck_assert_int_eq(is_empty_stack(stack), 0);
  ck_assert_int_eq(stack->size, 4);

#if IS_TEST_TURN_ON
  print_stack(stack);
#endif
  res = pop_stack(&stack);
  ck_assert_str_eq(res, "24");
  res = free_str(res);
  res = pop_stack(&stack);
  ck_assert_str_eq(res, "23");
  res = free_str(res);

  free_stack(&stack);

  /* *****  ***** */

  str = "1 ";
  stack = string_to_stack(str);

  ck_assert_int_eq(is_empty_stack(stack), 0);
  ck_assert_int_eq(stack->size, 1);

#if IS_TEST_TURN_ON
  print_stack(stack);
#endif
  res = pop_stack(&stack);
  ck_assert_str_eq(res, "1");
  res = free_str(res);
  res = pop_stack(&stack);
  ck_assert_ptr_eq(res, NULL);
  res = free_str(res);

  free_stack(&stack);

  /* *****  ***** */

  str = "  ";
  stack = string_to_stack(str);

  ck_assert_int_eq(is_empty_stack(stack), 1);

#if IS_TEST_TURN_ON
  print_stack(stack);
#endif
  res = pop_stack(&stack);
  ck_assert_ptr_eq(res, NULL);
  res = free_str(res);

  free_stack(&stack);

  /* *****  ***** */

  str = " ";
  stack = string_to_stack(str);

  ck_assert_int_eq(is_empty_stack(stack), 1);

#if IS_TEST_TURN_ON
  print_stack(stack);
#endif
  res = pop_stack(&stack);
  ck_assert_ptr_eq(res, NULL);
  res = free_str(res);

  free_stack(&stack);

  /* *****  ***** */

  str = "";
  stack = string_to_stack(str);

  ck_assert_int_eq(is_empty_stack(stack), 1);

#if IS_TEST_TURN_ON
  print_stack(stack);
#endif
  res = pop_stack(&stack);
  ck_assert_ptr_eq(res, NULL);
  res = free_str(res);

  free_stack(&stack);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_push_stack_char_test) {
  s_stack *stack = NULL;

  ck_assert_int_eq(is_empty_stack(stack), 1);

  push_stack_char(&stack, '1');
  push_stack_char(&stack, '2');
  push_stack_char(&stack, '3');
  push_stack_char(&stack, '4');
  push_stack_char(&stack, '5');

  // print_stack(stack);
  char res = prev_char_stack(stack);
  ck_assert_int_eq(res, '4');

  char *tmp = pop_stack(&stack);
  free(tmp);
  tmp = NULL;

  res = prev_char_stack(stack);
  ck_assert_int_eq(res, '3');

  /* *****  ***** */

  tmp = pop_stack(&stack);
  free(tmp);

  res = prev_char_stack(stack);
  ck_assert_int_eq(res, '2');

  /* *****  ***** */

  tmp = pop_stack(&stack);
  free(tmp);

  res = prev_char_stack(stack);
  ck_assert_int_eq(res, '1');

  /* *****  ***** */

  tmp = pop_stack(&stack);
  free(tmp);

  res = prev_char_stack(stack);
  ck_assert_int_eq(res, '\0');

  free_stack(&stack);

  /* *****  ***** */
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_stack_prev_char_test) {
  s_stack *stack = NULL;

  ck_assert_int_eq(is_empty_stack(stack), 1);

  push_stack(&stack, "1");
  push_stack(&stack, "2");
  push_stack(&stack, "3");
  push_stack(&stack, "4");
  push_stack(&stack, "5");

  char res = prev_char_stack(stack);
  ck_assert_int_eq(res, '4');

  char *tmp = pop_stack(&stack);
  free(tmp);
  tmp = NULL;

  res = prev_char_stack(stack);
  ck_assert_int_eq(res, '3');

  /* *****  ***** */

  tmp = pop_stack(&stack);
  free(tmp);

  res = prev_char_stack(stack);
  ck_assert_int_eq(res, '2');

  /* *****  ***** */

  tmp = pop_stack(&stack);
  free(tmp);

  res = prev_char_stack(stack);
  ck_assert_int_eq(res, '1');

  /* *****  ***** */

  tmp = pop_stack(&stack);
  free(tmp);

  res = prev_char_stack(stack);
  ck_assert_int_eq(res, '\0');

  free_stack(&stack);

  /* *****  ***** */
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_stack_data_to_string_test) {
  s_stack *stack = NULL;

  ck_assert_int_eq(is_empty_stack(stack), 1);

  push_stack(&stack, "1");
  push_stack(&stack, "2");
  push_stack(&stack, "3");
  push_stack(&stack, "4");
  push_stack(&stack, "5");

  // print_stack(stack);
  char *res = data_to_string_stack(stack);

  ck_assert_ptr_ne(res, NULL);
  // printf("result = %s\n", res);
  res = free_str(res);
  free_stack(&stack);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_str_deep2_test) {
  char **str = NULL;

  ck_assert_ptr_eq(str, NULL);
  str = create_str_deep_2(10, 10);
  ck_assert_ptr_ne(str, NULL);
  str = free_str_deep_2(str, 10);
  ck_assert_ptr_eq(str, NULL);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_stack_is_empty) {
  s_stack *stack = NULL;

  ck_assert_int_eq(is_empty_stack(stack), 1);

  push_stack(&stack, "1");
  push_stack(&stack, "2");
  push_stack(&stack, "3");

  ck_assert_int_eq(is_empty_stack(stack), 0);

  free(pop_stack(&stack));
  ck_assert_int_eq(is_empty_stack(stack), 0);

  free(pop_stack(&stack));
  ck_assert_int_eq(is_empty_stack(stack), 0);

  free(pop_stack(&stack));
  ck_assert_int_eq(is_empty_stack(stack), 1);

  free_stack(&stack);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_free_str_test) {
  char *str = NULL;

  if (!(str = (char *)calloc(5, sizeof(char)))) {
    exit(-1);
  }

  str[0] = 'a';
  str[1] = 'b';
  str[2] = '\0';
  str[3] = '\0';
  str[4] = '\0';

  str = free_str(str);
  str = free_str(str);
  str = free_str(str);

  ck_assert_ptr_eq(str, NULL);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_stack_push_test) {
  s_stack *stack = NULL;
  init_stack(&stack);
  push_stack(&stack, "there");
  free_stack(&stack);

  /* *****  ***** */

  stack = NULL;
  init_stack(&stack);
  free_stack(&stack);

  /* *****  ***** */

  stack = NULL;
  init_stack(&stack);
  push_stack(&stack, "there");
  push_stack(&stack, "is");
  push_stack(&stack, "no");
  push_stack(&stack, "spoon");
  push_stack(&stack, ".");
  free_stack(&stack);

  /* *****  ***** */

  stack = NULL;
  init_stack(&stack);
  push_stack(&stack, "there");
  push_stack(&stack, "is");
  push_stack(&stack, "no");
  push_stack(&stack, "spoon");
  push_stack(&stack, ".");

  char *str = NULL;
  str = pop_stack(&stack);
  ck_assert_str_eq(str, ".");
  free(str);
  str = NULL;

  str = pop_stack(&stack);
  ck_assert_str_eq(str, "spoon");
  free(str);

  str = pop_stack(&stack);
  ck_assert_str_eq(str, "no");
  free(str);

  str = pop_stack(&stack);
  ck_assert_str_eq(str, "is");
  free(str);

  str = pop_stack(&stack);
  ck_assert_str_eq(str, "there");
  free(str);

  str = pop_stack(&stack);
  ck_assert_ptr_eq(str, NULL);
  free(str);

  str = pop_stack(&stack);
  ck_assert_ptr_eq(str, NULL);
  free(str);

  /* *****  ***** */

  push_stack(&stack, "since");
  str = pop_stack(&stack);
  ck_assert_str_eq(str, "since");
  free_str(str);
  free_stack(&stack);

  /* *****  ***** */

  int res = push_stack(&stack, NULL);
  ck_assert_int_eq(res, 1);
  str = pop_stack(&stack);
  if (!res)
    ck_assert_str_eq(str, "since");
  free_str(str);
  free_stack(&stack);
}
END_TEST

// -------------------------------------------------------

START_TEST(s21_pop_free_stack_test) {
  s_stack *stack = NULL;

  /* *****  ***** */

  push_stack(&stack, "there");
  push_stack(&stack, "is");
  push_stack(&stack, "no");
  push_stack(&stack, "spoon");
  push_stack(&stack, ".");

  //  /* *****  ***** */

  pop_free_stack(&stack);
  pop_free_stack(&stack);
  char *str = pop_stack(&stack);

  ck_assert_str_eq(str, "no");

  str = free_str(str);
  pop_free_stack(&stack);
  pop_free_stack(&stack);
  pop_free_stack(&stack);
  pop_free_stack(&stack);

  free_stack(&stack);
}
END_TEST

// -------------------------------------------------------

void stack_functions_test(TCase *tc1_1) {
  tcase_add_test(tc1_1, s21_string_to_stack_test);
  tcase_add_test(tc1_1, s21_stack_push_test);
  tcase_add_test(tc1_1, s21_free_str_test);
  tcase_add_test(tc1_1, s21_str_deep2_test);
  tcase_add_test(tc1_1, s21_stack_is_empty);
  tcase_add_test(tc1_1, s21_stack_data_to_string_test);
  tcase_add_test(tc1_1, s21_stack_prev_char_test);
  tcase_add_test(tc1_1, s21_push_stack_char_test);
  tcase_add_test(tc1_1, s21_pop_free_stack_test);
}
