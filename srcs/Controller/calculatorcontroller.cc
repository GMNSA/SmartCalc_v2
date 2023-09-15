#include "../../includes/Controller/calculatorcontroller.hpp"

namespace s21 {

CalculatorController::CalculatorController(IModel *model) : model_(model) {
  // TODO(_who): reslese
}

// ----------------------------------------------------------------------------

CalculatorController::~CalculatorController() {
  if (model_) delete model_;
}

// ----------------------------------------------------------------------------

void CalculatorController::Calculate(QString const &str, QString const &x) {
  model_->Calculate(str, x);
}

// ----------------------------------------------------------------------------

QString CalculatorController::get_data() const { return model_->get_result(); }

// ----------------------------------------------------------------------------

QString CalculatorController::get_data_graph() const {
  return model_->get_result_graph();
}

// ----------------------------------------------------------------------------

void CalculatorController::AddValue(QString const &str) {
  model_->AddValue(str);
}

// ----------------------------------------------------------------------------

void CalculatorController::SetBrackets(QString const &str, bool const is_smart,
                                       bool is_checked) {
  model_->SetBrackets(str, is_smart, is_checked);
}

// ----------------------------------------------------------------------------

void CalculatorController::Reset() { model_->Reset(); }

// ----------------------------------------------------------------------------

QString CalculatorController::get_text_display() const {
  return model_->get_fix_text_display();
}

// ----------------------------------------------------------------------------

QString CalculatorController::get_text_repeat_display() const {
  return model_->get_text_repeat_display();
}

// ----------------------------------------------------------------------------

void CalculatorController::DelOne() { model_->DelOne(); }

// ----------------------------------------------------------------------------

bool CalculatorController::get_is_graph() const {
  return model_->get_is_graph();
}

// ----------------------------------------------------------------------------

void CalculatorController::ChangeSign() { model_->ChangeSign(); }

}  // namespace s21
