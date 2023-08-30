#ifndef CREDITCALCULATOR_HPP
#define CREDITCALCULATOR_HPP

#include <QObject>

extern "C" {
#include "s21_credit_calc.h"
}

class CreditCalculator {
public:
  CreditCalculator();
  virtual ~CreditCalculator();

  void calculate();
  void setStr(QString count_);
  void setSum(QString count_);
  void setTime(QString count_);
  void setProcent(QString count_);
  void setIsMount(bool isMount_);
  void setDifferent(bool isDiff_);

  QString infoMonthlyPayment() const;
  QString infoAccruedInterest() const;
  QString infoDebgAndInterest() const;

private:
  QString m_strCredit;
  unsigned long long m_sumCredit;
  unsigned m_timeCredit;
  double m_n_procentCredit;

  bool m_isMount;
  bool m_isDifferent;

  s_credit_data m_s_data;

private:
  void resetData();
};

#endif // CREDITCALCULATOR_HPP
