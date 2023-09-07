#include "../../includes/Controller/calculatorcontroller.hpp"

namespace ns_simple_controller {

CalculatorController::CalculatorController(ns_model::IModel *model)
    : model_(model) {
  // TODO(_who): reslese
}

CalculatorController::~CalculatorController() {}
void CalculatorController::Calculate(QString const &str, QString const &x) {
  model_->Calculate(str, x);
}

// ----------------------------------------------------------------------------

QString CalculatorController::GetData() const { return model_->GetResult(); }

// ----------------------------------------------------------------------------

QString CalculatorController::GetDatatGraph() const {
  return model_->GetResultGraph();
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

QString CalculatorController::GetTextDisplay() const {
  return model_->FixTextDisplay();
}

// ----------------------------------------------------------------------------

QString CalculatorController::GetTextRepeatDisplay() const {
  return model_->TextRepeatDisplay();
}

// ----------------------------------------------------------------------------

void CalculatorController::DelOne() { model_->DelOne(); }

// ----------------------------------------------------------------------------

bool CalculatorController::IsGraph() const { return model_->IsGraph(); }

// ----------------------------------------------------------------------------

void CalculatorController::ChangeSign() { model_->ChangeSign(); }

}  // namespace ns_simple_controller
