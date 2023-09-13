#ifndef INCLUDES_MODEL_MODELDEPOSIT_HPP_
#define INCLUDES_MODEL_MODELDEPOSIT_HPP_

#include <QString>

#include "./imodeldeposit.hpp"

namespace s21 {

class ModelDeposit : public IModelDeposit {
 public:
  ModelDeposit();
  virtual ~ModelDeposit();

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
  double deposit_sum_;
  double percent_rate_;
  double placement_period_;
  double tax_rate_;

  PeriodicityPayments frequentcy_payments_;
  Capitalization capitalization_;

  QListWidget *top_up_account_;
  QListWidget *widthdraw_from_account_;

  double accrued_interest_;
  double tax_amount_;
  double total_amount_;
};

}  // namespace s21

#endif  // INCLUDES_MODEL_MODELDEPOSIT_HPP_
