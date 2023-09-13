#include "../../includes/Controller/creditcontroller.hpp"

#include <QDebug>

namespace s21 {

CreditController::CreditController(IModelCredit *model_credit)
    : model_credit_(model_credit) {}

// ----------------------------------------------------------------------------

CreditController::~CreditController() {
  if (model_credit_) delete model_credit_;
}

// ----------------------------------------------------------------------------

void CreditController::Calculate() { model_credit_->Calculate(); };

// ----------------------------------------------------------------------------

void CreditController::set_sum(QString count) {
  if (model_credit_) model_credit_->set_sum(count);
};

// ----------------------------------------------------------------------------

void CreditController::set_time(QString count) {
  if (model_credit_) model_credit_->set_time(count);
};

// ----------------------------------------------------------------------------

void CreditController::set_procent(QString count) {
  if (model_credit_) model_credit_->set_procent(count);
};

// ----------------------------------------------------------------------------

void CreditController::set_is_mount(bool is_mount) {
  if (model_credit_) model_credit_->set_is_mount(is_mount);
};

// ----------------------------------------------------------------------------

void CreditController::set_different(bool is_diff) {
  if (model_credit_) model_credit_->set_different(is_diff);
};

// ----------------------------------------------------------------------------

QString CreditController::MonthlyPayment() const {
  return model_credit_->MonthlyPayment();
};

// ----------------------------------------------------------------------------

QString CreditController::AccruedInterest() const {
  return model_credit_->AccruedInterest();
};

// ----------------------------------------------------------------------------

QString CreditController::DebgAndInterest() const {
  return model_credit_->DebgAndInterest();
};

// ----------------------------------------------------------------------------

}  // namespace s21
