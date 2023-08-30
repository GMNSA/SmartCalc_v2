#include "creditcalculator.hpp"

#include <QDebug>
#include <QString>

CreditCalculator::CreditCalculator()
    : m_sumCredit(0), m_timeCredit(0), m_n_procentCredit(0), m_isMount(0),
      m_isDifferent(0), m_s_data({0, 0, 0, 0}) {}

/*          ***** ***** ***** *****          */

CreditCalculator::~CreditCalculator() {}

/*          ***** ***** ***** *****          */

void CreditCalculator::calculate() {
  resetData();

  if (m_timeCredit != 0 && m_n_procentCredit != 0) {
    if (m_isDifferent)
      m_s_data = calculator_different((double)m_sumCredit, (double)m_timeCredit,
                                      m_isMount, m_n_procentCredit);
    else
      m_s_data = calculator_annuit((double)m_sumCredit, (double)m_timeCredit,
                                   m_isMount, m_n_procentCredit);
  }
}

/*          ***** ***** ***** *****          */

void CreditCalculator::setStr(QString count_) { m_strCredit = count_; }

/*          ***** ***** ***** *****          */

void CreditCalculator::setSum(QString count_) {
  m_sumCredit = count_.toULongLong();
}

/*          ***** ***** ***** *****          */

void CreditCalculator::setTime(QString count_) {
  m_timeCredit = count_.toInt();
}

/*          ***** ***** ***** *****          */

void CreditCalculator::setProcent(QString count_) {
  m_n_procentCredit = count_.toDouble();
}

/*          ***** ***** ***** *****          */

void CreditCalculator::setIsMount(bool isMount_) { m_isMount = isMount_; }

void CreditCalculator::setDifferent(bool isDiff_) { m_isDifferent = isDiff_; }

/*          ***** ***** ***** *****          */

QString CreditCalculator::infoMonthlyPayment() const {
  QString str;

  if (m_isDifferent) {
    str = "Ежемесячный платеж:     " +
          QString("%L1").arg(m_s_data.mount, 0, 'f', 2) + " ... " +
          QString("%L1").arg(m_s_data.mount_last, 0, 'f', 2) + " руб.";
  } else {
    str = "Ежемесячный платеж:     " +
          QString("%L1").arg(m_s_data.mount, 0, 'f', 2) + " руб.";
  }
  str = str.replace(",", " ");

  return (str);
}

/*          ***** ***** ***** *****          */

QString CreditCalculator::infoAccruedInterest() const {
  QString str;

  str = "Начисленные проценты: " +
        QString("%L1").arg(m_s_data.procents, 0, 'f', 2) + " руб.";
  str = str.replace(",", " ");
  return (str);
}

/*          ***** ***** ***** *****          */

QString CreditCalculator::infoDebgAndInterest() const {
  QString str;

  str =
      "Долг + проценты:      " + QString("%L1").arg(m_s_data.total, 0, 'f', 2) +
      " руб.";
  str = str.replace(",", " ");

  return (str);
}

/*          ***** ***** ***** *****          */

void CreditCalculator::resetData() {
  m_s_data.mount = 0;
  m_s_data.mount_last = 0;
  m_s_data.procents = 0;
  m_s_data.total = 0;
}
