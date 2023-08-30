#ifndef CALCULATIONSMARTCALC_HPP
#define CALCULATIONSMARTCALC_HPP

extern "C" {
#include "s21_smart_calc.h"
}

#include <QString>

class CalculationSmartCalc {
 public:
  CalculationSmartCalc();
  virtual ~CalculationSmartCalc();

  QString calculate(QString str_);

 private:
  QString m_str;
};

#endif  // CALCULATIONSMARTCALC_HPP
