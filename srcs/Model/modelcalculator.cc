#include "../../includes/Model/modelcalculator.hpp"

#include <QRegularExpression>
#include <QString>
#include <cmath>

namespace s21 {

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
    // calculated_text_ = "0";
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

void ModelCalculator::ChangeSign() {
  QRegularExpression re;
  QRegularExpressionMatch reMatch = re.match("\\d");

  QString tmp;
  bool is_find = 0;
  unsigned n_str = 0;

  if (!display_text_.isEmpty()) {
    if (display_text_.size() == 1) {
      if (display_text_[0].isDigit())
        AddMinux(&display_text_);
      else
        AddBrackets(&display_text_);
    } else if (display_text_.size() >= 4) {
      if (display_text_[0] == '-' && display_text_[1] == '(' &&
          display_text_[display_text_.size() - 1] == ')') {
        n_str = display_text_.length() - 1;
        for (unsigned i = n_str - 1; i > 0; --i) {
          if (display_text_[i] == '(' && i > 0 &&
              display_text_[i - 1].isLetter()) {
            AddBrackets(&display_text_);
            is_find = true;
            break;
          } else if (display_text_[i] == ')') {
            RemoveBrackets(&display_text_);
            is_find = true;
            break;
          }
        }

        if (!is_find) RemoveBrackets(&display_text_);

      } else if (display_text_[0] == '-' && display_text_[1].isDigit() &&
                 display_text_[display_text_.size() - 1].isDigit()) {
        display_text_.remove(0, 1);
      } else {
        AddBrackets(&display_text_);
      }
    } else if (display_text_[0] != '-') {
      if (reMatch.hasMatch()) {
        AddMinux(&display_text_);
      } else {
        AddBrackets(&display_text_);
      }
    } else if (display_text_[0] == '-') {
      RemoveMinux(&display_text_);
    }
  }

  validator_text_->set_text(display_text_);
  display_text_ = validator_text_->get_text();
}

// ----------------------------------------------------------------------------

void ModelCalculator::RemoveBrackets(QString *str) {
  if (str) {
    unsigned n_str = str->length() - 1;

    if (n_str >= 3 && str->at(0) == '-' && str->at(1) == '(' &&
        str->at(n_str) == ')') {
      str->remove(display_text_.size() - 1, 1);
      str->remove(1, 1);
      str->remove(0, 1);
    }
  }
}

// ----------------------------------------------------------------------------

void ModelCalculator::AddBrackets(QString *str) {
  if (str) {
    QString tmp = "-(" + display_text_ + ")";
    display_text_ = tmp;
  }
}

// ----------------------------------------------------------------------------

void ModelCalculator::AddMinux(QString *str) {
  if (str) {
    QString tmp = "-" + display_text_;
    display_text_ = tmp;
  }
}

// ----------------------------------------------------------------------------

void ModelCalculator::RemoveMinux(QString *str) {
  if (str) {
    unsigned n_str = str->length() - 1;
    if (n_str > 0 && str->at(0) == '-') display_text_.remove(0, 1);
  }
}

// ----------------------------------------------------------------------------

}  // namespace s21
