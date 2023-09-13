#ifndef INCLUDES_CONTROLLER_IDEPOSITCONTROLLER_HPP_
#define INCLUDES_CONTROLLER_IDEPOSITCONTROLLER_HPP_

#include <QListWidget>
#include <QtPlugin>

#include "../custom_types.hpp"

namespace s21 {

class IDepositController {
 public:
  virtual ~IDepositController() = default;

  virtual void set_deposit_sum(QString const deposit_sum) = 0;
  virtual void set_percent_rate(QString const percent_rate) = 0;
  virtual void set_placement_period(QString const placement_period) = 0;
  virtual void set_tax_rate(QString const tax_rate) = 0;

  virtual void set_frequency_payments(PeriodicityPayments const &pp) = 0;
  virtual void set_capitalization(Capitalization const &cap) = 0;

  virtual void set_top_up_account(QListWidget *top_up_account) = 0;
  virtual void set_widthdraw_from_account(
      QListWidget *widthdraw_from_account) = 0;

  virtual QString get_total_deposit_amount() const = 0;
  virtual QString get_withdrawal_amount() const = 0;

  virtual QString get_accrued_interest() const = 0;
  virtual QString get_amount_taxes() const = 0;
  virtual QString get_total_amount() const = 0;

  virtual void Calculate() = 0;

 protected:
};

}  // namespace s21

// Q_DECLARE_INTERFACE(s21::IDepositController, "s21.IDepositController");

#endif  // INCLUDES_CONTROLLER_IDEPOSITCONTROLLER_HPP_
