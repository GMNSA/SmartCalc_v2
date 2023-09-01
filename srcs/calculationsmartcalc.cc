#include "../includes/calculationsmartcalc.hpp"

#include <QtDebug>

CalculationSmartCalc::CalculationSmartCalc() : m_str("0") {}

CalculationSmartCalc::~CalculationSmartCalc() {}

QString CalculationSmartCalc::calculate(QString str_) {
  char *p_str = nullptr;
  char *p_polska = nullptr;
  char *p_res = nullptr;

  QByteArray ba = str_.toLocal8Bit();
  p_str = ba.data();

  p_polska = str_to_postfix(p_str);
  p_res = calculate_notation(p_polska);
  m_str = p_res;

  if (p_polska) free(p_polska);

  if (p_res) free(p_res);

  return (m_str);
}
