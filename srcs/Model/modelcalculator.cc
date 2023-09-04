#include "../../includes/Model/modelcalculator.hpp"

#include <cmath>

namespace ns_model {

ModelCalculator::ModelCalculator()
    : display_text_(""),
      calculated_text_(""),
      polish_notation_(new PolishNotation()),
      validator_text_(new ValidateText()) {}

ModelCalculator::~ModelCalculator() {
  if (polish_notation_) delete polish_notation_;
  if (validator_text_) delete validator_text_;
}

void ModelCalculator::Calculate(QString const &str) {
  calculated_text_ = polish_notation_->CalculateNotation(str);
}

QString ModelCalculator::GetResult() const { return calculated_text_; };

void ModelCalculator::AddValue(QString const &str) {
  // TODO(_who): I will need think about reset_text validator and reset text
  // model text.
  validator_text_->AddTextToStr(str);
  display_text_ = validator_text_->get_text();
}

void ModelCalculator::SetBrackets(QString const &str, bool const is_smart,
                                  bool is_checked) {
  validator_text_->SetBrackets(str, is_smart, is_checked);
  validator_text_->get_text();
}

void ModelCalculator::Reset() {
  // TODO(_who): release reset ...
  qDebug() << "RESET MODEL CALCULATOR.";
  validator_text_->Reset();
  polish_notation_->Reset();
}

QString ModelCalculator::FixTextDisplay() const { return display_text_; }

}  // namespace ns_model
