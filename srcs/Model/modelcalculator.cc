#include "../../includes/Model/modelcalculator.hpp"

#include <QString>
#include <cmath>

namespace ns_model {

ModelCalculator::ModelCalculator()
    : display_text_(),
      repeat_text_(),
      calculated_text_(),
      is_graph_(0),
      graphic_text_(),
      polish_notation_(new PolishNotation()),
      validator_text_(new ValidateText()) {}

ModelCalculator::~ModelCalculator() {
  if (polish_notation_) delete polish_notation_;
  if (validator_text_) delete validator_text_;
}

// ----------------------------------------------------------------------------

void ModelCalculator::Calculate(QString const &str, QString const &x) {
  QString tmp_str;
  graphic_text_.clear();

  if (str.isEmpty()) {
    tmp_str = polish_notation_->StrToPostfix(display_text_);
  } else {
    tmp_str = polish_notation_->StrToPostfix(str);
  }

  graphic_text_ = display_text_;
  ReplaceX(&tmp_str, x);
  calculated_text_ = polish_notation_->CalculateNotation(tmp_str);
  repeat_text_ = validator_text_->get_text();
  display_text_ = "0";

  if (polish_notation_->get_error()) {
    polish_notation_->Reset();
    validator_text_->Reset();
    calculated_text_ = "0";
    repeat_text_ = "error";
  } else {
    validator_text_->set_text(calculated_text_);
  }

  display_text_ = calculated_text_;
}

// ----------------------------------------------------------------------------

QString ModelCalculator::GetResult() const { return calculated_text_; }

// ----------------------------------------------------------------------------

QString ModelCalculator::GetResultGraph() const { return graphic_text_; }

// ----------------------------------------------------------------------------

void ModelCalculator::AddValue(QString const &str) {
  // TODO(_who): WARNING need to fix !!!!
  // TODO(_who): I will need think about reset_text validator and reset text

  validator_text_->AddTextToStr(str);
  display_text_ = validator_text_->get_text();
  display_text_ = validator_text_->get_text();
}

// ----------------------------------------------------------------------------

void ModelCalculator::SetBrackets(QString const &str, bool const is_smart,
                                  bool is_checked) {
  validator_text_->SetBrackets(str, is_smart, is_checked);
  display_text_ = validator_text_->get_text();
}

// ----------------------------------------------------------------------------

void ModelCalculator::Reset() {
  // TODO(_who): release reset ...
  qDebug() << "RESET MODEL CALCULATOR.";
  validator_text_->Reset();
  polish_notation_->Reset();
  calculated_text_.clear();
  display_text_.clear();
  repeat_text_.clear();
}

// ----------------------------------------------------------------------------

QString ModelCalculator::FixTextDisplay() const { return display_text_; }

// ----------------------------------------------------------------------------

QString ModelCalculator::TextRepeatDisplay() const { return repeat_text_; }

// ----------------------------------------------------------------------------

void ModelCalculator::DelOne() {
  int n_str = display_text_.size();
  display_text_ = display_text_.trimmed();

  if (display_text_.endsWith("cos(")) {
    display_text_.remove(n_str - 4, n_str);
  } else if (display_text_.endsWith("sin(")) {
    display_text_.remove(n_str - 4, n_str);
  } else if (display_text_.endsWith("tan(")) {
    display_text_.remove(n_str - 4, n_str);
  } else if (display_text_.endsWith("acs(")) {
    display_text_.remove(n_str - 5, n_str);
  } else if (display_text_.endsWith("asn(")) {
    display_text_.remove(n_str - 5, n_str);
  } else if (display_text_.endsWith("atn(")) {
    display_text_.remove(n_str - 5, n_str);
  } else if (display_text_.endsWith("sqrt(")) {
    display_text_.remove(n_str - 5, n_str);
  } else if (display_text_.endsWith("ln(")) {
    display_text_.remove(n_str - 3, n_str);
  } else if (display_text_.endsWith("log(")) {
    display_text_.remove(n_str - 4, n_str);
  } else {
    display_text_.chop(1);
  }

  if (display_text_.size() == 0) {
    display_text_ = "0";
    validator_text_->set_clear(true);
  }

  validator_text_->Reset();
  validator_text_->set_text(display_text_);
}

// ----------------------------------------------------------------------------

bool ModelCalculator::IsGraph() const { return is_graph_; }

// ----------------------------------------------------------------------------

void ModelCalculator::ReplaceX(QString *str, QString const &x) {
  if (str && str->indexOf("x") != -1) {
    if (x.isEmpty())
      str->replace(QString("x"), x);
    else
      str->replace(QString("x"), "0");
    is_graph_ = true;
  } else {
    is_graph_ = false;
  }
}

// ----------------------------------------------------------------------------

}  // namespace ns_model
