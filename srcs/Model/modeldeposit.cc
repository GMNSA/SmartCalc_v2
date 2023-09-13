#include "../../includes/Model/modeldeposit.hpp"

#include <cmath>

namespace s21 {

constexpr double AVERAGE_DAYS = 30.416666666666667851;
constexpr double NDFL = 13.0 / 100.0;

ModelDeposit::ModelDeposit()
    : deposit_sum_(100000),
      percent_rate_(20),
      placement_period_(24),
      tax_rate_(0.0),
      frequentcy_payments_(PeriodicityPayments::kOnce),
      capitalization_(Capitalization::kNo),
      top_up_account_(nullptr),
      widthdraw_from_account_(nullptr),
      accrued_interest_(0.0),
      tax_amount_(0.0),
      total_amount_(0.0) {}

// ----------------------------------------------------------------------------

ModelDeposit::~ModelDeposit() {}

// ----------------------------------------------------------------------------

void ModelDeposit::set_deposit_sum(QString const deposit_sum) {
  QString tmp = deposit_sum;
  deposit_sum_ = tmp.replace(" ", "").toLongLong();
}

// ----------------------------------------------------------------------------

void ModelDeposit::set_percent_rate(QString const percent_rate) {
  percent_rate_ = percent_rate.toDouble();
}

// ----------------------------------------------------------------------------

void ModelDeposit::set_placement_period(QString const placement_period) {
  placement_period_ = placement_period.toDouble();
}

// ----------------------------------------------------------------------------

void ModelDeposit::set_tax_rate(QString const tax_rate) {
  tax_rate_ = tax_rate.toDouble();
}

// ----------------------------------------------------------------------------

void ModelDeposit::set_frequency_payments(PeriodicityPayments const &pp) {
  frequentcy_payments_ = pp;
}

// ----------------------------------------------------------------------------

void ModelDeposit::set_capitalization(Capitalization const &cap) {
  capitalization_ = cap;
}

// ----------------------------------------------------------------------------

void ModelDeposit::set_top_up_account(QListWidget *top_up_account) {
  top_up_account_ = top_up_account;
}

// ----------------------------------------------------------------------------

void ModelDeposit::set_widthdraw_from_account(
    QListWidget *widthdraw_from_account) {
  widthdraw_from_account_ = widthdraw_from_account;
}

// ----------------------------------------------------------------------------

QString ModelDeposit::get_total_deposit_amount() const { return "0"; }

// ----------------------------------------------------------------------------

QString ModelDeposit::get_withdrawal_amount() const { return "0"; }

// ----------------------------------------------------------------------------

QString ModelDeposit::get_accrued_interest() const {
  return QString::number(accrued_interest_, 'f', 2);
}

// ----------------------------------------------------------------------------

QString ModelDeposit::get_amount_taxes() const {
  return QString::number(tax_amount_, 'f', 2);
}

// ----------------------------------------------------------------------------

QString ModelDeposit::get_total_amount() const {
  return QString::number(total_amount_, 'f', 2);
}

// ----------------------------------------------------------------------------

void ModelDeposit::Calculate() {
  double amounts_deposits = deposit_sum_;
  double withdraw_amount = 0.0;
  double tax_rate = tax_rate_;
  double part_for_tax = 0.0;
  QListWidgetItem *list_item = nullptr;
  int n_list = -1;

  if (top_up_account_) {
    n_list = top_up_account_->count() - 1;

    while (n_list != -1) {
      list_item = top_up_account_->takeItem(n_list);
      amounts_deposits += list_item->text().toDouble();
      delete list_item;
      --n_list;
    }
  }

  if (widthdraw_from_account_) {
    n_list = widthdraw_from_account_->count() - 1;

    while (n_list != -1) {
      list_item = widthdraw_from_account_->takeItem(n_list);
      withdraw_amount += list_item->text().toDouble();
      delete list_item;
      --n_list;
    }
  }

  amounts_deposits -= withdraw_amount;

  if (capitalization_ == Capitalization::kMontly &&
      frequentcy_payments_ == PeriodicityPayments::kMontly) {
    accrued_interest_ =
        (amounts_deposits *
         std::pow((1 + (percent_rate_ / 100.0) / 12), placement_period_)) -
        amounts_deposits;
  } else {
    accrued_interest_ = (amounts_deposits * percent_rate_ * placement_period_ *
                         AVERAGE_DAYS / 365) /
                        100;
  }

  tax_rate = tax_rate * 1000000 / 100;

  part_for_tax = accrued_interest_ - tax_rate;

  if (part_for_tax > 0 && tax_rate != 0.0)
    tax_amount_ = part_for_tax * NDFL;
  else
    tax_amount_ = 0;

  total_amount_ = amounts_deposits + accrued_interest_ - tax_amount_;
}

}  // namespace s21
