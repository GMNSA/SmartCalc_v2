#include "s21_smart_calc.h"
#include <math.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>

#define SIZE_ERROR_STR 6
#define LIMIT_SIZE_STR_ERROR 3000

#define ft_unuased(num) (void)(num)

#define IS_TEST_TURN_ON 0

// #if IS_TEST_TURN_ON
// void print_reverse_stack(s_stack *stack_);
// void print_debug_stack_step(s_stack *s_, s_stack *v_) {
//   printf("s = ");
//   print_reverse_stack(s_);
//   printf("v = ");
//   print_reverse_stack(v_);
//   printf("\n");
// }
//
// void print_debug_stack_single(s_stack *s_) {
//   printf("s = ");
//   print_reverse_stack(s_);
//   printf("\n");
// }
//
// void print_debug_s(char *str_) {
//   if (str_)
//     printf("res => %s\n", str_);
// }
// #endif

unsigned custom_strlen(char const *p_str_, unsigned limit_, int *is_error_);
int is_sign(char ch_);
int is_math_function(char *str_);
int is_digit(char ch_);
int is_number_str(char *str_);
void pol_is_num(char tmp_[], char const num_, unsigned *i_tmp_);
int find_str(char const *str_, char const *needle_, int i_);
void clear_str(char *str_, int size_);
int priority(char ch_);
void print_stack(s_stack *stack_);
char *string_number(char const *p_str_, unsigned *pi_str_, int *p_is_error_);
void add_space_to_str(char **p_str_, unsigned *pi_res_, unsigned *p_size_res_);
int add_math_function(char const *p_src_, unsigned *pi_src_, s_stack **p_s_);

void remove_zeros(char *p_str_, unsigned limit_str_, int *p_is_error_);

/* *****  tmp  ***** */

void push_to_stack_tmp(char *p_tmp_, s_stack **stack_, unsigned *pi_str_,
                       unsigned const size_tmp_);
void add_char_to_str(char **p_str_, char const ch_, unsigned i_str_,
                     unsigned *p_size_str_);
void add_str_to_str(char **p_dest_, char const *p_src_, unsigned *pi_dest_,
                    unsigned *p_size_dest_);

/* *****  ***** */

void remove_zeros(char *p_str_, unsigned limit_str_, int *p_is_error_) {
  if (p_str_) {
    unsigned n_str = custom_strlen(p_str_, limit_str_, p_is_error_) - 1;

    for (unsigned i = n_str; i > 0 && (p_str_[i] == '0' || p_str_[i] == '.');
         --i) {
      if (p_str_[i] == '0' && i > 1) {
        p_str_[i] = '\0';
      } else if (p_str_[i] == '.') {
        p_str_[i] = '\0';
        i = 1;
      }
    }
  }
}

// -------------------------------------------------------

int is_check_valid_postfix(char *p_str_, int *p_is_error_) {
  int n_sign = 0;
  int n_num = 0;

  if (p_str_) {
    unsigned n_str = custom_strlen(p_str_, LIMIT_SIZE_STR_ERROR, p_is_error_);
    int is_find = 0;

    for (unsigned i = 0; i < n_str; ++i) {
      if ((is_digit(p_str_[i]) || p_str_[i] == 'x') && !is_find) {
        is_find = 1;
        ++n_num;
      } else if (is_sign(p_str_[i]) && !is_find) {
        is_find = 1;
        ++n_sign;
      } else if (p_str_[i] == ' ') {
        is_find = 0;
      }
    }
  }

  return (n_num > n_sign);
}

/* *****  ***** */

unsigned custom_strlen(char const *p_str_, unsigned limit_, int *p_is_error_) {
  unsigned i;
  unsigned n_str = 0;

  for (i = 0; p_str_ && p_str_[i] && i < limit_; ++i) {
    ++n_str;
  }

  if (i >= limit_ || !p_str_)
    *p_is_error_ = 1;

  return (n_str);
}

char *string_number(char const *p_str_, unsigned *pi_str_, int *p_is_error_) {
  unsigned size_str = 20;
  char *res = NULL;

  if (p_str_ && pi_str_) {
    unsigned n_str = custom_strlen(p_str_, LIMIT_SIZE_STR_ERROR, p_is_error_);
    res = create_str(size_str);
    unsigned i_res = 0;

    for (; *pi_str_ < n_str &&
           (is_digit(p_str_[*pi_str_]) || p_str_[*pi_str_] == '.');
         ++(*pi_str_)) {
      add_char_to_str(&res, p_str_[*pi_str_], i_res++, &size_str);
    }
  }

  return (res);
}

// -------------------------------------------------------

void add_space_to_str(char **p_str_, unsigned *pi_res_, unsigned *p_size_res_) {
  if (p_str_ && *p_str_ && *pi_res_ > 0 && (*p_str_)[*pi_res_] != ' ') {
    add_char_to_str(p_str_, ' ', (*pi_res_)++, p_size_res_);
  }
}

// -------------------------------------------------------

void check_end_resisze_str(char **p_str_, unsigned pi_str_, unsigned *pn_str_) {
  char *tmp = NULL;
  unsigned const ADD_SIZE = 20;

  if (pn_str_ && (pi_str_ + 1 >= *pn_str_)) {
    if (*p_str_) {
      unsigned newallocated = pi_str_ + *pn_str_ + ADD_SIZE;
      if (!((tmp) = (char *)realloc((*p_str_),
                                    (newallocated + 1) * sizeof(char)))) {
        exit(-1);
      } else {
        memset(tmp + ((*pn_str_) * sizeof(char)), 0,
               (newallocated - (*pn_str_)) * sizeof(char));
        *pn_str_ = newallocated;
        (*p_str_) = tmp;
        tmp = NULL;
      }
    }
  }
}

// -------------------------------------------------------

int is_number_str(char *str_) {
  int res = 1;

  if (str_) {
    unsigned n_str = strlen(str_);
    for (unsigned i = 0; i < n_str; ++i) {
      if (!is_digit(str_[i]) && str_[i] != '.' && str_[i] != '-') {
        i = n_str;
        res = 0;
      }
    }
  }

  return (res);
}

// -------------------------------------------------------

void trim_str_num(char *p_res_, unsigned n_limit_) {
  int is_start = 0;
  n_limit_++;

  if (p_res_) {
    for (int i = 0; p_res_ && p_res_[i] != '\0'; ++i) {
      if (is_start) {
        --n_limit_;
      }

      if (p_res_[i] == '.') {
        if (n_limit_ == 1)
          n_limit_ = 0;
        is_start = 1;
      }

      if (n_limit_ == 0) {
        p_res_[i--] = '\0';
      }
    }
  }
}

// -------------------------------------------------------

int add_math_function(char const *p_src_, unsigned *pi_src_, s_stack **p_s_) {
  int res = -1;

  if (p_src_ && pi_src_) {
    if ((res = find_str(p_src_, "cos", *pi_src_)) != -1) {
      push_stack(p_s_, "cos");
    } else if ((res = find_str(p_src_, "sin", *pi_src_)) != -1) {
      push_stack(p_s_, "sin");
    } else if ((res = find_str(p_src_, "alg", *pi_src_)) != -1) {
      push_stack(p_s_, "alg");
    } else if ((res = find_str(p_src_, "tan", *pi_src_)) != -1) {
      push_stack(p_s_, "tan");
    } else if ((res = find_str(p_src_, "acs", *pi_src_)) != -1) {
      push_stack(p_s_, "acs");
    } else if ((res = find_str(p_src_, "asn", *pi_src_)) != -1) {
      push_stack(p_s_, "asn");
    } else if ((res = find_str(p_src_, "atn", *pi_src_)) != -1) {
      push_stack(p_s_, "atn");
    } else if ((res = find_str(p_src_, "sqrt", *pi_src_)) != -1) {
      push_stack(p_s_, "sqrt");
    } else if ((res = find_str(p_src_, "ln", *pi_src_)) != -1) {
      push_stack(p_s_, "ln");
    } else if ((res = find_str(p_src_, "log", *pi_src_)) != -1) {
      push_stack(p_s_, "log");
    } else if ((res = find_str(p_src_, "mod", *pi_src_)) != -1) {
      push_stack(p_s_, "mod");
    }

    *pi_src_ = res != -1 ? (unsigned)res : *pi_src_;
  }

  return (res);
}

int is_math_function(char *str_) {
  int res = 0;

  if (str_) {
    if (strcmp(str_, "cos") == 0)
      res = 1;
    if (strcmp(str_, "sin") == 0)
      res = 1;
    if (strcmp(str_, "tan") == 0)
      res = 1;
    if (strcmp(str_, "acs") == 0)
      res = 1;
    if (strcmp(str_, "asn") == 0)
      res = 1;
    if (strcmp(str_, "atn") == 0)
      res = 1;
    if (strcmp(str_, "sqrt") == 0)
      res = 1;
    if (strcmp(str_, "ln") == 0)
      res = 1;
    if (strcmp(str_, "log") == 0)
      res = 1;
  }

  return (res);
}

// -------------------------------------------------------

int find_str(char const *str_, char const *needle_, int i_) {
  int res = -1;
  if (str_ && needle_) {
    unsigned n_str = strlen(str_);
    unsigned n_needle = strlen(needle_);

    if (n_str >= n_needle) {
      unsigned i_str = i_;
      int i_needle = 0;
      for (; str_[i_str]; ++i_str, ++i_needle) {
        if (needle_[i_needle] == '\0' || (str_[i_str] != needle_[i_needle])) {
          break;
        }
      }
      if ((unsigned)i_needle == n_needle) {
        res = i_ + i_needle - 1;
      }
    }
  }
  return (res);
}

// -------------------------------------------------------

int is_find_in_stack_brackets(s_stack *s_) {
  int is_find_brackets = 0;

  while (s_ && !is_empty_stack(s_)) {
    if (strspn(s_->p_value, "(") || strspn(s_->p_value, ")")) {
      is_find_brackets = 1;
      break;
    }
    s_ = s_->p_prev;
  }

  return (is_find_brackets);
}

// -------------------------------------------------------

int is_digit(char ch_) {
  int res = 0;

  if (ch_ >= '0' && ch_ <= '9')
    res = 1;
  return (res);
}

// -------------------------------------------------------

int is_letter(char ch_) {
  int res = 0;

  if (ch_ >= 97 && ch_ <= 122)
    res = 1;
  else if (ch_ >= 65 && ch_ <= 90)
    res = 1;
  else
    res = 0;

  return (res);
}

// -------------------------------------------------------

void push_to_stack_tmp(char *p_tmp_, s_stack **stack_, unsigned *pi_str_,
                       unsigned const size_tmp_) {
  if (p_tmp_ && p_tmp_[0] != '\0') {
    push_stack(stack_, p_tmp_);
    *pi_str_ = 0;
    clear_str(p_tmp_, size_tmp_);
  }
}

// -------------------------------------------------------

void add_char_to_str(char **p_tmp_, char ch_, unsigned i_str_,
                     unsigned *p_size_tmp_) {
  if (p_tmp_) {
    check_end_resisze_str(p_tmp_, i_str_, p_size_tmp_);
    (*p_tmp_)[i_str_] = ch_;
  }
}

// -------------------------------------------------------

void add_str_to_str(char **p_dest_, char const *p_src_, unsigned *pi_dest_,
                    unsigned *p_size_dest_) {
  if (p_dest_ && *p_dest_ && p_src_) {
    unsigned n_src = strlen(p_src_);
    *pi_dest_ += n_src;
    check_end_resisze_str(p_dest_, *pi_dest_, p_size_dest_);
    strncat(*p_dest_, p_src_, n_src);
  }
}

// -------------------------------------------------------

char *double_to_string(double num_) {
  char *res = create_str(LIMIT_SIZE_STR_ERROR);
  int n_num = 0;

  snprintf(res, LIMIT_SIZE_STR_ERROR, "%.12f", num_);

  n_num = strlen(res);
  res[n_num - 1] = '\0';

  return (res);
}

// -------------------------------------------------------

double string_to_double(char const *str_) {
  char *tmp = NULL;
  double res = 0;

  res = strtod(str_, &tmp);
  return (res);
}

// -------------------------------------------------------

int priority(char ch_) {
  int res = 0;

  if (ch_ == '(' || ch_ == ')')
    res = 6;
  else if (ch_ == 'c' || ch_ == 's' || ch_ == 't' || ch_ == 'l' || ch_ == 'a')
    res = 5;
  else if (ch_ == '~')
    res = 4;
  else if (ch_ == '^' || ch_ == '%')
    res = 3;
  else if (ch_ == '*' || ch_ == '/')
    res = 2;
  else if (ch_ == '+' || ch_ == '-')
    res = 1;
  else
    res = 0;

  return (res);
}

// -------------------------------------------------------

int is_sign(char ch_) {
  int is_res = 0;

  if (ch_ == '^')
    is_res = 1;
  else if (ch_ == '*')
    is_res = 1;
  else if (ch_ == '/')
    is_res = 1;
  else if (ch_ == '+')
    is_res = 1;
  else if (ch_ == '-')
    is_res = 1;
  else if (ch_ == '%')
    is_res = 1;
  else
    is_res = 0;

  return (is_res);
}

void clear_str(char *str_, int size_) {
  for (int i = 0; i < size_; ++i) {
    str_[i] = '\0';
  }
}

// -------------------------------------------------------

char *str_to_postfix(char *str_) {
  ft_unuased(str_);
  s_stack *s = NULL;
  unsigned size_res = 20;
  char *res = create_str(size_res);
  int is_error = 0;
  char *tmp = NULL;
  unsigned i_res = 0;

  if (str_ == NULL)
    is_error = 1;

  if (!is_error) {
    unsigned n_str = custom_strlen(str_, LIMIT_SIZE_STR_ERROR, &is_error);
    char prev_ch = '\0';
    char c = '\0';
    char op = '\0';

    for (unsigned i = 0; i < n_str; ++i) {
      c = str_[i];
      if (is_digit(c) || c == 'x') {
        if (c == 'x') {
          add_space_to_str(&res, &i_res, &size_res);
          add_char_to_str(&res, c, i_res++, &size_res);
        } else {
          tmp = string_number(str_, &i, &is_error);
          --i;
          add_space_to_str(&res, &i_res, &size_res);
          add_str_to_str(&res, tmp, &i_res, &size_res);
          tmp = free_str(tmp);
        }
      } else if (is_letter(c)) {
        if (add_math_function(str_, &i, &s) == -1)
          is_error = 1;
      } else if (c == '(') {
        push_stack_char(&s, '(');
      } else if (c == ')') {
        if (c == ')' && prev_ch == '(')
          is_error = 1;
        while (!is_empty_stack(s) && s->p_value && s->p_value[0] != '(' &&
               !is_error) {
          tmp = pop_stack(&s);
          add_space_to_str(&res, &i_res, &size_res);
          add_str_to_str(&res, tmp, &i_res, &size_res);
          tmp = free_str(tmp);
        }
        if (is_empty_stack(s) || (s->p_value && s->p_value[0] != '(')) {
          is_error = 1;
        }
        pop_free_stack(&s);
      } else if (is_sign(c) && priority(c)) {
        op = c;

        if (op == '-' &&
            (i == 0 || (i >= 1 && (is_sign(prev_ch) || prev_ch == '(')))) {
          op = '~';
        }

        while (s && !is_empty_stack(s) && s->p_value &&
               (priority(s->p_value[0]) >= priority(op)) &&
               priority(s->p_value[0]) <= 5) {
          tmp = pop_stack(&s);
          add_space_to_str(&res, &i_res, &size_res);
          add_str_to_str(&res, tmp, &i_res, &size_res);
          tmp = free_str(tmp);
        }
        push_stack_char(&s, op);
      }

      if ((c == '-' && prev_ch == '-') ||
          ((is_letter(prev_ch) && prev_ch != 'x') && c != '('))
        is_error = 1;

      if (c != ' ')
        prev_ch = c;

      if (is_error)
        break;
    }

    is_error = is_error ? is_error : is_find_in_stack_brackets(s);

    if (!is_error) {
      while (!is_empty_stack(s)) {
        tmp = pop_stack(&s);
        add_char_to_str(&res, ' ', i_res++, &size_res);
        add_str_to_str(&res, tmp, &i_res, &size_res);
        tmp = free_str(tmp);
      }
    } else {
      res = free_str(res);
    }
    free_stack(&s);
  }

  return (res);
}

// -------------------------------------------------------

char *char_to_str(char ch_, char res_[]) {
  res_[0] = ch_;
  res_[1] = '\0';

  return (res_);
}

// -------------------------------------------------------

double calculate_str_numbers_single(char *p_num_, char *p_str_,
                                    int *p_is_error_) {
  double res = 0;

  if (p_num_ && (*p_is_error_) == 0) {
    char *p_tmp = NULL;
    if (strcmp(p_str_, "sin") == 0) {
      res = sin(strtod(p_num_, &p_tmp));
    } else if (strcmp(p_str_, "cos") == 0) {
      res = cos(strtod(p_num_, &p_tmp));
    } else if (strcmp(p_str_, "tan") == 0) {
      res = tan(strtod(p_num_, &p_tmp));
    } else if (strcmp(p_str_, "acs") == 0) {
      res = acos(strtod(p_num_, &p_tmp));
    } else if (strcmp(p_str_, "asn") == 0) {
      res = asin(strtod(p_num_, &p_tmp));
    } else if (strcmp(p_str_, "atn") == 0) {
      res = atan(strtod(p_num_, &p_tmp));
    } else if (strcmp(p_str_, "sqrt") == 0) {
      res = sqrt(strtod(p_num_, &p_tmp));
    } else if (strcmp(p_str_, "ln") == 0) {
      res = log(strtod(p_num_, &p_tmp));
    } else if (strcmp(p_str_, "log") == 0) {
      res = log10(strtod(p_num_, &p_tmp));
    } else {
      *p_is_error_ = 1;
    }
  } else {
    *p_is_error_ = 1;
  }

  return (res);
}

double calculate_str_numbers_mul(char *p_num1_, char const *str_, char *p_num2_,
                                 int *error_) {
  double res = 0;

  if (str_ && p_num1_ && p_num2_ && *error_ != 1) {
    char *p_tmp = NULL;
    char *p_tmp2 = NULL;
    if (strcmp(str_, "+") == 0) {
      res = strtod(p_num1_, &p_tmp) + strtod(p_num2_, &p_tmp2);
    } else if (strcmp(str_, "-") == 0) {
      res = strtod(p_num1_, &p_tmp) - strtod(p_num2_, &p_tmp2);
    } else if (strcmp(str_, "/") == 0) {
      res = strtod(p_num1_, &p_tmp) / strtod(p_num2_, &p_tmp2);
    } else if (strcmp(str_, "*") == 0) {
      res = strtod(p_num1_, &p_tmp) * strtod(p_num2_, &p_tmp2);
    } else if (strcmp(str_, "^") == 0) {
      res = pow(strtod(p_num1_, &p_tmp), strtod(p_num2_, &p_tmp2));
    } else if (strcmp(str_, "%") == 0) {
      res = fmod(strtod(p_num1_, &p_tmp), strtod(p_num2_, &p_tmp2));
    } else {
      *error_ = 1;
    }
  } else {
    *error_ = 1;
  }

  return (res);
}

// -------------------------------------------------------

double calculate_numbers_mul(double num1_, char const *str_, double num2_,
                             int *error_) {
  double res = 0;

  if (str_ && *error_ != 1) {
    if (strcmp(str_, "+") == 0) {
      res = num1_ + num2_;
    } else if (strcmp(str_, "-") == 0) {
      res = num1_ - num2_;
    } else if (strcmp(str_, "/") == 0) {
      res = num1_ / num2_;
    } else if (strcmp(str_, "*") == 0) {
      res = num1_ * num2_;
    } else if (strcmp(str_, "^") == 0) {
      res = pow(num1_, num2_);
    } else if (strcmp(str_, "%") == 0) {
      res = fmod(num1_, num2_);
    } else {
      *error_ = 1;
    }
  } else {
    *error_ = 1;
  }

  return (res);
}

// -------------------------------------------------------

char *calculate_notation(char const *p_str_) {
  char *p_result = NULL;
  s_stack *sp_tmp_data = NULL;
  s_stack *sp_str_split = NULL;
  int is_error = 0;
  long double tmp_num = 0;

  if (p_str_ && p_str_[0] != '\0') {
    sp_str_split = string_to_stack(p_str_);
    char *p_tmp = NULL;
    char *p_one_arg = NULL;
    char *p_two_arg = NULL;
    char *p_sign_arg = NULL;

    while (sp_str_split->p_prev) {
      sp_str_split = sp_str_split->p_prev;
    }

    while (sp_str_split && sp_str_split->p_value) {
      p_tmp = sp_str_split->p_value;
      push_stack(&sp_tmp_data, p_tmp);

      if (!is_empty_stack(sp_tmp_data) && p_tmp) {
        if (sp_tmp_data->size >= 2 && p_tmp[0] == '~') {
          pop_free_stack(&sp_tmp_data);
          p_one_arg = pop_stack(&sp_tmp_data);
          tmp_num = strtod(p_one_arg, &p_tmp);

          tmp_num = calculate_numbers_mul(0, "-", tmp_num, &is_error);
          p_tmp = double_to_string(tmp_num);
          push_stack(&sp_tmp_data, p_tmp);

          p_one_arg = free_str(p_one_arg);
          p_tmp = free_str(p_tmp);
        } else if (sp_tmp_data->size >= 2 && is_math_function(p_tmp)) {
          p_sign_arg = pop_stack(&sp_tmp_data);
          p_one_arg = pop_stack(&sp_tmp_data);

          if (!is_number_str(p_one_arg))
            is_error = 1;

          tmp_num =
              calculate_str_numbers_single(p_one_arg, p_sign_arg, &is_error);
          if (isnan(tmp_num))
            is_error = 1;
          p_tmp = double_to_string(tmp_num);
          push_stack(&sp_tmp_data, p_tmp);
          p_sign_arg = free_str(p_sign_arg);
          p_sign_arg = free_str(p_one_arg);
          p_tmp = free_str(p_tmp);

        } else if (sp_tmp_data->size >= 3 && is_sign(p_tmp[0])) {
          p_sign_arg = pop_stack(&sp_tmp_data);
          p_two_arg = pop_stack(&sp_tmp_data);
          p_one_arg = pop_stack(&sp_tmp_data);

          if (!is_number_str(p_two_arg) || !is_number_str(p_one_arg))
            is_error = 1;

          tmp_num = calculate_str_numbers_mul(p_one_arg, p_sign_arg, p_two_arg,
                                              &is_error);
          p_tmp = double_to_string(tmp_num);
          push_stack(&sp_tmp_data, p_tmp);
          p_sign_arg = free_str(p_sign_arg);
          p_sign_arg = free_str(p_two_arg);
          p_sign_arg = free_str(p_one_arg);
          p_tmp = free_str(p_tmp);
        }
      }

      /* *****  ***** */

      if (sp_str_split->p_next == NULL || is_error)
        break;
      sp_str_split = sp_str_split->p_next;
    }
  } else {
    is_error = 1;
  }

  if (sp_tmp_data && sp_tmp_data->size == 1 && !is_error) {
    p_result = pop_stack(&sp_tmp_data);
    remove_zeros(p_result, LIMIT_SIZE_STR_ERROR, &is_error);
  } else {
    p_result = create_str(SIZE_ERROR_STR);
    strncpy(p_result, "error", SIZE_ERROR_STR);
  }

  free_stack(&sp_tmp_data);
  free_stack(&sp_str_split);

  trim_str_num(p_result, 7);

  return (p_result);
}

// -------------------------------------------------------
