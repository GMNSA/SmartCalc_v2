#include "../../includes/Model/modelcredit.hpp"

namespace s21 {

ModelCredit::ModelCredit()
    : sum_credit_(0),
      time_credit_(0),
      procents_credit_(0.0),
      is_mount_(false),
      is_different_(false),
      mount_(0.0),
      mount_last_(0.0),
      procents_(0.0),
      total_(0.0) {}

// ----------------------------------------------------------------------------

ModelCredit::~ModelCredit() {}

// ----------------------------------------------------------------------------

void ModelCredit::Calculate() {
  ResetData();

  if (time_credit_ != 0 && procents_credit_ != 0) {
    if (is_different_)
      CalculatorDifferent();
    else
      CalculatorAnnuit();
  }
};

// ----------------------------------------------------------------------------

void ModelCredit::set_sum(QString count) { sum_credit_ = count.toLongLong(); };

// ----------------------------------------------------------------------------

void ModelCredit::set_time(QString count) { time_credit_ = count.toInt(); };

// ----------------------------------------------------------------------------

void ModelCredit::set_procent(QString count) {
  procents_credit_ = count.toDouble();
};

// ----------------------------------------------------------------------------

void ModelCredit::set_is_mount(bool is_mount) { is_mount_ = is_mount; };

// ----------------------------------------------------------------------------

void ModelCredit::set_different(bool is_diff) { is_different_ = is_diff; };

// ----------------------------------------------------------------------------

QString ModelCredit::MonthlyPayment() const {
  QString str;

  if (is_different_) {
    str = QString("%L1").arg(mount_, 0, 'f', 2) + " ... " +
          QString("%L1").arg(mount_last_, 0, 'f', 2);
  } else {
    str = QString("%L1").arg(mount_, 0, 'f', 2);
  }
  str = str.replace(",", " ");

  return (str);
};

// ----------------------------------------------------------------------------

QString ModelCredit::AccruedInterest() const {
  QString str;

  str = QString("%L1").arg(procents_, 0, 'f', 2);
  str = str.replace(",", " ");
  return (str);
};

// ----------------------------------------------------------------------------

QString ModelCredit::DebgAndInterest() const {
  QString str;

  str = QString("%L1").arg(total_, 0, 'f', 2);
  str = str.replace(",", " ");

  return (str);
};

// ----------------------------------------------------------------------------
void ModelCredit::ResetData() {
  mount_ = 0.0;
  mount_last_ = 0.0;
  procents_ = 0.0;
  total_ = 0.0;
}

// ----------------------------------------------------------------------------

void ModelCredit::MyRound(long double *num) {
  if (num) {
    long double a = (unsigned)*num;
    double tmp = modf(round(*num * 100) / 100, &tmp);
    *num = a + tmp;
  }
}

// ********************************************************

void ModelCredit::CalculatorAnnuit() {
  ResetData();
  double ps = procents_credit_ / 1200.0;
  double pp = is_mount_ == 0 ? time_credit_ : time_credit_ * 12;
  double o = sum_credit_;
  double a = 1 - pow(1 + ps, -pp);
  double b = ps / a;
  long double p = o * b;

  MyRound(&p);

  mount_ = p;
  mount_last_ = p;
  procents_ = p * pp - sum_credit_;
  total_ = sum_credit_ + procents_;
}

// ----------------------------------------------------------------------------

void ModelCredit::CalculatorDifferent() {
  ResetData();
  double p = procents_credit_ / 1200.0;
  double s = sum_credit_;
  double n = is_mount_ == 0 ? time_credit_ : time_credit_ * 12;
  double b = s / n;
  double mount_first = b + (sum_credit_ - b * 0) * p;
  double mount_last = b + (sum_credit_ - b * round(n - 1)) * p;
  long double aa = mount_first;
  long double bb = mount_last;
  long double dd = (mount_first + mount_last) * (n / 2.0);
  long double cc = (dd - s);

  MyRound(&aa);
  MyRound(&bb);
  MyRound(&cc);
  MyRound(&dd);

  mount_ = aa;
  mount_last_ = bb;
  procents_ = cc;
  total_ = dd;
}

}  // namespace s21
