#include "../../includes/Controller/depositcontroller.hpp"

namespace s21 {

DepositController::DepositController(IModelDeposit *model) : model_(model) {}

// ----------------------------------------------------------------------------

DepositController::~DepositController() {
  if (model_) delete model_;
}

// ----------------------------------------------------------------------------

void DepositController::set_deposit_sum(QString const deposit_sum) {
  model_->set_deposit_sum(deposit_sum);
}

// ----------------------------------------------------------------------------

void DepositController::set_percent_rate(QString const percent_rate) {
  model_->set_percent_rate(percent_rate);
}

// ----------------------------------------------------------------------------

void DepositController::set_placement_period(QString const placement_period) {
  model_->set_placement_period(placement_period);
}

// ----------------------------------------------------------------------------

void DepositController::set_tax_rate(QString const tax_rate) {
  model_->set_tax_rate(tax_rate);
}

// ----------------------------------------------------------------------------

void DepositController::set_frequency_payments(PeriodicityPayments const &pp) {
  model_->set_frequency_payments(pp);
}

// ----------------------------------------------------------------------------

void DepositController::set_capitalization(Capitalization const &cap) {
  model_->set_capitalization(cap);
}

// ----------------------------------------------------------------------------

void DepositController::set_top_up_account(QListWidget *top_up_account) {
  model_->set_top_up_account(top_up_account);
}

// ----------------------------------------------------------------------------

void DepositController::set_widthdraw_from_account(
    QListWidget *widthdraw_from_account) {
  model_->set_widthdraw_from_account(widthdraw_from_account);
}

// ----------------------------------------------------------------------------

QString DepositController::get_total_deposit_amount() const {
  return model_->get_total_deposit_amount();
}

// ----------------------------------------------------------------------------

QString DepositController::get_withdrawal_amount() const {
  return model_->get_withdrawal_amount();
}

// ----------------------------------------------------------------------------

QString DepositController::get_accrued_interest() const {
  return model_->get_accrued_interest();
}

// ----------------------------------------------------------------------------

QString DepositController::get_amount_taxes() const {
  return model_->get_amount_taxes();
}

// ----------------------------------------------------------------------------

QString DepositController::get_total_amount() const {
  return model_->get_total_amount();
}

// ----------------------------------------------------------------------------

void DepositController::Calculate() { model_->Calculate(); }

}  // namespace s21
