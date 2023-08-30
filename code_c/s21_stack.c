#include "s21_stack.h"
#include <stdlib.h>
#include <string.h>

void clear_str(char *str_, int size_);
void add_char_to_str(char **p_str_, char const ch_, unsigned i_str_,
                     unsigned *p_size_str_);
void add_str_to_str(char **p_dest_, char const *p_src_, unsigned *pi_dest_,
                    unsigned *p_size_dest_);

// -------------------------------------------------------

void reverse_str_deep2(char ***str_, int n_row_) {
  char **tmp = *str_;
  int end_str = n_row_ - 1;

  char *t = NULL;
  for (int i = 0; i < end_str; ++i, --end_str) {
    t = tmp[i];
    tmp[i] = tmp[end_str];
    tmp[end_str] = t;
    t = NULL;
  }
}

// -------------------------------------------------------

char *free_str(char *str_) {
  if (str_) {
    free(str_);
  }
  return (NULL);
}

// -------------------------------------------------------

char *create_str(unsigned size_) {
  char *str = NULL;

  if (!(str = (char *)calloc(size_ + 1, sizeof(char)))) {
    exit(-1);
  }

  return (str);
}

// -------------------------------------------------------

char **create_str_deep_2(unsigned row_, unsigned col_) {
  char **str = NULL;

  if (!(str = (char **)calloc(row_, sizeof(char *)))) {
    exit(-1);
  }

  for (unsigned i = 0; i < row_; ++i) {
    if (!(str[i] = (char *)calloc(col_ + 1, sizeof(char)))) {
      exit(-1);
    }
  }

  return (str);
}

// -------------------------------------------------------

char **free_str_deep_2(char **str_, int row_) {
  if (str_) {
    for (int i = 0; i < row_; ++i) {
      if (str_[i]) {
        free(str_[i]);
        str_[i] = NULL;
      }
    }
    free(str_);
    str_ = NULL;
  }

  return (str_);
}

// -------------------------------------------------------

int init_stack(s_stack **p_stack_) {
  int error = 0;

  if ((*p_stack_) == NULL) {
    if (!((*p_stack_) = (s_stack *)calloc(1, sizeof(s_stack)))) {
      exit(-1);
    }

    (*p_stack_)->p_next = NULL;
    (*p_stack_)->p_prev = NULL;
    (*p_stack_)->size = 0;
  } else {
    error = 1;
  }

  return (error);
}

// -------------------------------------------------------

int free_stack(s_stack **p_stack_) {
  int error = 0;

  if (p_stack_ && *p_stack_) {
    s_stack *node = (*p_stack_);
    s_stack *tmp = NULL;

    while (node->p_next)
      node = node->p_next;

    while (node) {
      tmp = node;
      node = node->p_prev;
      if (tmp->p_value) {
        tmp->p_value = free_str(tmp->p_value);
      }
      free(tmp);
      tmp = NULL;
    }
    (*p_stack_) = NULL;
  } else {
    error = 1;
  }

  return (error);
}

// -------------------------------------------------------
int push_stack_char(s_stack **p_stack_, char const ch_) {
  int error = 0;
  int const n_str = 2;

  if (p_stack_ && *p_stack_) {
    s_stack *tmp = NULL;

    if ((*p_stack_)->size == 0) {
      (*p_stack_)->p_value = create_str(n_str);
      (*p_stack_)->p_value[0] = ch_;
      ++(*p_stack_)->size;
    } else {
      if (!(tmp = (s_stack *)calloc(1, sizeof(s_stack)))) {
        exit(-1);
      }
      tmp->p_value = create_str(n_str);
      tmp->p_value[0] = ch_;

      (*p_stack_)->p_next = tmp;
      tmp->size = (*p_stack_)->size + 1;
      tmp->p_prev = (*p_stack_);
      tmp->p_next = NULL;
      (*p_stack_) = tmp;
    }
  } else if ((*p_stack_) == NULL) {
    init_stack(p_stack_);
    push_stack_char(p_stack_, ch_);
  } else {
    error = 1;
  }

  return (error);
}

// -------------------------------------------------------

int push_stack(s_stack **p_stack_, char const *str_) {
  int error = 0;

  if (p_stack_ && *p_stack_ && str_) {
    unsigned n_str = strlen(str_);
    s_stack *tmp = NULL;

    if ((*p_stack_)->size == 0) {
      (*p_stack_)->p_value = create_str(n_str);
      strncpy((*p_stack_)->p_value, str_, n_str);
      ++(*p_stack_)->size;
    } else {
      if (!(tmp = (s_stack *)calloc(1, sizeof(s_stack)))) {
        exit(-1);
      }
      tmp->p_value = create_str(n_str);
      strncpy(tmp->p_value, str_, n_str);

      (*p_stack_)->p_next = tmp;
      tmp->size = (*p_stack_)->size + 1;
      tmp->p_prev = (*p_stack_);
      tmp->p_next = NULL;
      (*p_stack_) = tmp;
    }
  } else if ((*p_stack_) == NULL && str_ != NULL) {
    init_stack(p_stack_);
    push_stack(p_stack_, str_);
  } else {
    error = 1;
  }

  return (error);
}

// -------------------------------------------------------

char *pop_stack(s_stack **p_stack_) {
  char *str = NULL;
  if (p_stack_ && *p_stack_) {
    str = (*p_stack_)->p_value;
    s_stack *tmp = NULL;
    tmp = (*p_stack_);

    if ((*p_stack_)) {
      (*p_stack_) = (*p_stack_)->p_prev;
      if (*p_stack_)
        (*p_stack_)->p_next = NULL;
    }

    free(tmp);
  }
  return (str);
}

// -------------------------------------------------------

void pop_free_stack(s_stack **p_stack_) {
  char *str = NULL;
  if (p_stack_ && *p_stack_) {
    str = (*p_stack_)->p_value;
    s_stack *tmp = NULL;
    tmp = (*p_stack_);

    if ((*p_stack_)) {
      (*p_stack_) = (*p_stack_)->p_prev;
      if (*p_stack_)
        (*p_stack_)->p_next = NULL;
    }

    free(tmp);
  }

  free_str(str);
}

// -------------------------------------------------------

int is_empty_stack(s_stack *p_stack_) {
  int res = 0;

  if (!p_stack_) {
    res = 1;
  } else {
    if (p_stack_->size > 0)
      res = 0;
    else
      res = 1;
  }
  return (res);
}

// -------------------------------------------------------

char *data_to_string_stack(s_stack *p_stack_) {
  char *res = NULL;

  if (p_stack_ && p_stack_->size >= 1) {
    int const n_deep2 = 300;
    int const n_deep1 = p_stack_->size;

    char **tmp = create_str_deep_2(n_deep1, n_deep2);

    for (int i = 0; i < n_deep1; ++i) {
      for (int j = 0; j < n_deep2; ++j) {
        tmp[i][j] = '\0';
      }
    }

    char *data = NULL;
    s_stack *p_tmp_stack = p_stack_;
    int n_i = 0;

    while (p_tmp_stack != NULL) {
      data = p_tmp_stack->p_value;
      if (data) {
        strncat(tmp[n_i++], data, strlen(data));
      }
      p_tmp_stack = p_tmp_stack->p_prev;
    }

    reverse_str_deep2(&tmp, n_deep1);

    int n_res = 0;
    for (int i = 0; i < n_deep1; ++i) {
      n_res += strlen(tmp[i]);
    }

    res = create_str(n_res * 2);

    for (int i = 0; i < n_deep1; ++i) {
      strncat(res, tmp[i], strlen(tmp[i]));
      if (i != n_deep1 - 1)
        strncat(res, " ", 2);
    }

    free_str_deep_2(tmp, n_deep1);
  }

  return (res);
}

// -------------------------------------------------------

char prev_char_stack(s_stack *p_stack_) {
  char res = '\0';

  if (p_stack_ && p_stack_->p_prev && p_stack_->p_prev->p_value) {
    res = p_stack_->p_prev->p_value[0];
  }

  return (res);
}

// -------------------------------------------------------

void remove_space_str_end(char *p_str_) {
  if (p_str_) {

    int n_str = strlen(p_str_);

    for (int i = n_str - 1; i >= 0; --i) {
      if (p_str_[i] == ' ' || p_str_[i] == '\t') {
        p_str_[i] = '\0';
      } else {
        i = 0;
      }
    }
  }
}

void reverse_str(char *p_str_) {
  if (p_str_) {
    char tmp_ch = '\0';
    int n_str = strlen(p_str_) - 1;
    for (int i = 0; i <= n_str; ++i, --n_str) {
      tmp_ch = p_str_[i];
      p_str_[i] = p_str_[n_str];
      p_str_[n_str] = tmp_ch;
    }
  }
}

// -------------------------------------------------------

s_stack *string_to_stack(char const *p_str_) {
  s_stack *res = NULL;
  unsigned n_reverse_str = 20;
  unsigned n_tmp = 20;
  char *p_reverse_str = create_str(n_reverse_str);
  char *p_tmp = create_str(n_tmp);
  unsigned i_reverse_str = 0;

  if (p_str_) {
    int n_str = strlen(p_str_);
    int i_tmp = 0;

    add_str_to_str(&p_reverse_str, p_str_, &i_reverse_str, &n_reverse_str);

    remove_space_str_end(p_reverse_str);
    n_str = strlen(p_reverse_str) - 1;

    if (n_str >= 0) {
      reverse_str(p_reverse_str);
      remove_space_str_end(p_reverse_str);
      n_str = strlen(p_reverse_str);
      for (int i = n_str - 1; i >= 0; --i, ++i_tmp) {
        if (p_reverse_str[i] == ' ') {
          push_stack(&res, p_tmp);
          clear_str(p_tmp, n_tmp);
          i_tmp = -1;
        } else {
          add_char_to_str(&p_tmp, p_reverse_str[i], i_tmp, &n_tmp);
        }
      }

      if (p_tmp[0] != '\0') {
        push_stack(&res, p_tmp);
        clear_str(p_tmp, n_tmp);
      }
    }

    free_str(p_tmp);
    free_str(p_reverse_str);
  }

  return (res);
}
