#ifndef SRC_CODE_C_S21_STACK_H_
#define SRC_CODE_C_S21_STACK_H_

#include <stdio.h>

#define ft_unuased(num) (void)(num)

// -------------------------------------------------------

typedef struct s_node {
  char *p_value;
  struct s_node *p_next;
  struct s_node *p_prev;
} s_node;

/* *****  ***** */

typedef struct s_stack {
  size_t size;
  char *p_value;
  struct s_stack *p_next;
  struct s_stack *p_prev;
} s_stack;

// -------------------------------------------------------

char *create_str(unsigned size_);
char *free_str(char *str_);
char **create_str_deep_2(unsigned row_, unsigned col_);
char **free_str_deep_2(char **str_, int row_);

// -------------------------------------------------------

/**
 * @brief Initialization stack.
 *
 * @param p_stack_ -> (s_stack **) pointer to the stack.
 *
 * @return ->           OK    - 0
 *                      Error - 1
 */
int init_stack(s_stack **p_stack_);

// -------------------------------------------------------

/**
 * @brief Free stack.
 *
 * @param p_stack_ -> (s_stack **) pointer (deep 2) to the stack.
 *
 * @return ->           OK    - 0
 *                      Error - 1
 */
int free_stack(s_stack **p_stack_);

// -------------------------------------------------------

/**
 * @brief Push to stack.
 *
 * @param p_stack__ -> (s_stack **) pointer (deep 2) to the stack.
 * @param str_ -> (char const *) string.
 *
 * @return ->           OK    - 0
 *                      Error - 1
 */
int push_stack(s_stack **p_stack_, char const *str_);

// -------------------------------------------------------

/**
 * @brief Push to stack char.
 *
 * @param p_stack__ -> (s_stack **) pointer (deep 2) to the stack.
 * @param str_ -> (char char) symbol.
 *
 * @return ->           OK    - 0
 *                      Error - 1
 */
int push_stack_char(s_stack **p_stack_, char const ch_);

// -------------------------------------------------------

/**
 * @brief Pop value from stack.
 *
 * @param p_stack_ -> (s_stack **) pointer (deep 2) to the stack.
 *
 * @return -> (char *) pointer to a value.
 */
char *pop_stack(s_stack **p_stack_);

// -------------------------------------------------------

/**
 * @brief Pop and free value from stack.
 *
 * @param p_stack_ -> (s_stack **) pointer (deep 2) to the stack.
 *
 * @return -> (void)
 */
void pop_free_stack(s_stack **p_stack_);

// -------------------------------------------------------

/**
 * @brief Is the stack empty.
 *
 * @param p_stack_ -> (s_stack *) poinster to the stack.
 *
 * @return ->    1 empty.
 *               0 not empty.
 */
int is_empty_stack(s_stack *p_stack_);

// -------------------------------------------------------

/**
 * @brief Data to string from stack.
 *
 * @param p_stack_ -> (s_stack *) pointer to the stack.
 *
 * @return     -> (If the stack is not empty) (char *)
 *                (If the stack is empty)     (NULL)
 *
 */
char *data_to_string_stack(s_stack *p_stack_);

// -------------------------------------------------------

/**
 * @brief Get char from prev data of stack.
 *
 * @param p_stack_ -> (s_stack *) pointer to the stack.
 *
 * @return  -> (If is not null) (char)
 *             (If is null)     ('\0')
 */
char prev_char_stack(s_stack *p_stack_);

// -------------------------------------------------------

/**
 * @brief Split string to stack. Space separator.
 *
 * @param str_ -> (char *) Line to split.
 *
 * @return  -> (s_stack *) Split string.
 *             (null) error.
 */
s_stack *string_to_stack(char const *str_);

#endif // SRC_CODE_C_S21_STACK_H_
