#ifndef INCLUDES_CONTROLLER_DEPOSITCONTROLLER_HPP_
#define INCLUDES_CONTROLLER_DEPOSITCONTROLLER_HPP_

#include "../Model/imodeldeposit.hpp"
#include "./idepositcontroller.hpp"

namespace s21 {

class DepositController : public IDepositController {
 public:
  explicit DepositController(IModelDeposit *model);
  virtual ~DepositController();

  void set_deposit_sum(QString const deposit_sum) override;
  void set_percent_rate(QString const percent_rate) override;
  void set_placement_period(QString const placement_period) override;
  void set_tax_rate(QString const tax_rate) override;

  void set_frequency_payments(PeriodicityPayments const &pp) override;
  void set_capitalization(Capitalization const &cap) override;

  void set_top_up_account(QListWidget *top_up_account) override;
  void set_widthdraw_from_account(QListWidget *widthdraw_from_account) override;

  QString get_total_deposit_amount() const override;
  QString get_withdrawal_amount() const override;

  QString get_accrued_interest() const override;
  QString get_amount_taxes() const override;
  QString get_total_amount() const override;

  void Calculate() override;

 private:
  IModelDeposit *model_;
};

}  // namespace s21

#endif  // INCLUDES_CONTROLLER_DEPOSITCONTROLLER_HPP_
