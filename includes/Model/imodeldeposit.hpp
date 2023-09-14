#ifndef INCLUDES_MODEL_IMODELDEPOSIT_HPP_
#define INCLUDES_MODEL_IMODELDEPOSIT_HPP_

#include <QListWidget>

#include "../custom_types.hpp"

namespace s21 {

class IModelDeposit {
 public:
  virtual ~IModelDeposit() = default;

  virtual void set_deposit_sum(QString deposit_sum) = 0;
  virtual void set_percent_rate(QString percent_rate) = 0;
  virtual void set_placement_period(QString placement_period) = 0;
  virtual void set_tax_rate(QString tax_rate) = 0;

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
};

}  // namespace s21

#endif  // INCLUDES_MODEL_IMODELDEPOSIT_HPP_
