#ifndef SRC_CODE_C_S21_SMART_CALC_H_
#define SRC_CODE_C_S21_SMART_CALC_H_

#include "s21_stack.h"
#include <stdlib.h>

#define BUFF_STR_CHAR 2

char *char_to_str(char ch_, char res_[]);

/**
 * @brief String to polish notation.
 *
 * @param str_ (char *) string data.
 *
 * @return  -> (char *)  (3 + 4) return (3 4 +) OK
 *             NULL                             ERROR
 */
char *str_to_postfix(char *str_);

// -------------------------------------------------------

/**
 * @brief Calculating polish notation
 *
 * @param str -> (char *) data (polska notation)
 *
 * @return  -> (char *) result (3 9 +) ==> (12)
 *             (error)  ERROR
 */
char *calculate_notation(char const *str_);

#endif // SRC_CODE_C_S21_SMART_CALC_H_
