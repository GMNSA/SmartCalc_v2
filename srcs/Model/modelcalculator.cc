#include "../../includes/Model/modelcalculator.hpp"

#include <cmath>

namespace ns_model {

ModelCalculator::ModelCalculator()
    : raw_text_(""),
      ready_text_(""),
      polish_notation_(new PolishNotation()),
      validator_text_(new ValidateText()) {}

ModelCalculator::~ModelCalculator() {
  if (polish_notation_) delete polish_notation_;
  if (validator_text_) delete validator_text_;
}

QString ModelCalculator::Calculate(QString const &str) {
  return polish_notation_->CalculateNotation(str);
}

void ModelCalculator::AddValue(QString const &str) {
  // TODO(_who): I will need think about reset_text validator and reset text
  // model text.
  validator_text_->AddTextToStr(str);
  validator_text_->get_text();
}

void ModelCalculator::SetBrackets(QString const &str, bool const is_smart,
                                  bool is_checked) {
  validator_text_->SetBrackets(str, is_smart, is_checked);
  validator_text_->get_text();
}

void ModelCalculator::Reset() {
  // TODO(_who): release reset ...
  qDebug() << "RESET MODEL CALCULATOR.";
}
}  // namespace ns_model
