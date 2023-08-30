#ifndef SRC_CODE_C_S21_CREDIT_CALC_H_
#define SRC_CODE_C_S21_CREDIT_CALC_H_

#include <stdlib.h>
#include <math.h>

typedef struct s_credit_data {
  long double mount;
  long double mount_last;
  long double procents;
  long double total;
} s_credit_data;

s_credit_data calculator_annuit(double sum_, double period_, int is_age_,
                                double n_procent_);
s_credit_data calculator_different(double sum_, double period_, int is_age_,
                                   double n_procent_);

#endif // SRC_CODE_C_S21_CREDIT_CALC_H_
