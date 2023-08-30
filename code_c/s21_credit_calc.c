#include "s21_credit_calc.h"

#include <stdio.h>

#define ft_unuased(num) (void)(num)

void clear_str(char *str_, int size_);
void my_round(long double *num_) {
  long double a = (unsigned)*num_;
  double tmp = modf(round(*num_ * 100) / 100, &tmp);
  *num_ = a + tmp;
}

// ********************************************************

s_credit_data calculator_annuit(double sum_, double period_, int is_age_,
                                double n_procent_) {
  s_credit_data res = {0, 0, 0, 0};
  double ps = n_procent_ / 1200.0;
  double pp = is_age_ == 0 ? period_ : period_ * 12;
  double o = sum_;
  double a = 1 - pow(1 + ps, -pp);
  double b = ps / a;
  long double p = o * b;

  my_round(&p);

  res.mount = p;
  res.mount_last = p;
  res.procents = p * pp - sum_;
  res.total = sum_ + res.procents;

  return (res);
}

s_credit_data calculator_different(double sum_, double period_, int is_age_,
                                   double n_procent_) {
  s_credit_data res = {0, 0, 0, 0};
  double p = n_procent_ / 1200.0;
  double s = sum_;
  double n = is_age_ == 0 ? period_ : period_ * 12;
  double b = s / n;
  double mount_first = b + (sum_ - b * 0) * p;
  double mount_last = b + (sum_ - b * round(n - 1)) * p;
  long double aa = mount_first;
  long double bb = mount_last;
  long double dd = (mount_first + mount_last) * (n / 2.0);
  long double cc = (dd - s);

  my_round(&aa);
  my_round(&bb);
  my_round(&cc);
  my_round(&dd);

  res.mount = aa;
  res.mount_last = bb;
  res.procents = cc;
  res.total = dd;

  return (res);
}
