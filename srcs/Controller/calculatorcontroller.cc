#include "../../includes/Controller/calculatorcontroller.hpp"

namespace ns_simple_controller {

CalculatorController::CalculatorController(ns_model::ModelCalculator *model)
    : model_(model) {
  // TODO(_who): reslese
}

void CalculatorController::Calculate(QString const &str) {
  model_->Calculate(str);
}

// -- -- -- --

QString CalculatorController::GetData() const { return model_->GetResult(); }

// -- -- -- --

void CalculatorController::AddValue(QString const &str) {
  model_->AddValue(str);
}

// -- -- -- --

void CalculatorController::SetBrackets(QString const &str, bool const is_smart,
                                       bool is_checked) {
  model_->SetBrackets(str, is_smart, is_checked);
}

// -- -- -- --

void CalculatorController::Reset() { model_->Reset(); }

// -- -- -- --

QString CalculatorController::GetTextForDisplay() const {
  return model_->FixTextDisplay();
};

// -- -- -- --

CalculatorController::~CalculatorController() {}

}  // namespace ns_simple_controller
