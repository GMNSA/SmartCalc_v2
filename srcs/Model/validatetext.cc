#include "../../includes/Model/validatetext.hpp"

namespace ns_model {

ValidateText::ValidateText(QString const &str)
    : text_(str), is_valid_(1), is_clear_(1), is_graph_(0) {}

// ----------------------------------------------------------------------------

void ValidateText::AddTextToStr(QString const &str) {
  AddText(str);
  // if (display_text_.indexOf("x") != -1) {
  //   m_strForGraph = display_text_;
  //   display_text_.replace(QString("x"), QString::number(m_graph->x()));
  //   is_graph = true;
  // }
  text_ = ReplaceDummyFunctions(text_);
  text_ = FixedText(text_);
}

// ----------------------------------------------------------------------------

void ValidateText::AddText(QString const &str) {
  QString tmp_num = str.trimmed();
  if ((is_clear_ == 1 || text_ == "error" || text_ == "na" || text_ == "0")) {
    if (tmp_num == "+" || tmp_num == "/" || tmp_num == "*" || tmp_num == "." ||
        tmp_num == "-" || tmp_num == "%") {
      is_clear_ = 0;
      text_ += str;
    } else {
      text_ = str;
      is_clear_ = 0;
    }
  } else {
    text_ += str;
  }
}

// ----------------------------------------------------------------------------

void ValidateText::SetBrackets(QString const &str, bool const is_smart,
                               bool is_checked) {
  if (!is_smart) {
    if (str == "(" || str == ")") AddTextToStr(str);
  } else {
    bool is_left_brackets = IsLeftBracket(text_);

    if (is_checked) {
      if (is_left_brackets == 0) {
        AddTextToStr("(");
      } else {
        AddTextToStr(")");
      }
    }
  }
}

// ----------------------------------------------------------------------------

bool ValidateText::IsLeftBracket(QString const &str) {
  int n_left = 0;
  int n_right = 0;

  for (auto const &i : str) {
    if (i == '(')
      ++n_left;
    else if (i == ')')
      ++n_right;
  }

  return (n_left > n_right ? 1 : 0);
}

// ----------------------------------------------------------------------------

void ValidateText::set_text(QString const &str) {
  if (!str.isEmpty()) is_clear_ = 0;
  text_ = str;
}

// ----------------------------------------------------------------------------

QString ValidateText::get_text() const { return text_; }

// ----------------------------------------------------------------------------

bool ValidateText::IsValid() const { return is_valid_; }

// ----------------------------------------------------------------------------

void ValidateText::Reset() {
  text_.clear();
  is_clear_ = 1;
  is_valid_ = 1;
  // TODO(_who): perhaps you need to assign 0 to text
}

// ----------------------------------------------------------------------------

QString ValidateText::FixedText(QString str) {
  QString res;
  unsigned n_str = 0;
  QChar before = '\0';
  QChar current = '\0';
  QChar after = '\0';

  str.replace(" ", "");
  n_str = str.size();

  for (unsigned i = 0; i < n_str; ++i) {
    before = current;
    current = str[i];

    if (i + 1 != n_str)
      after = str[i + 1];
    else
      after = '\0';

    if (IsSign(current)) {
      if ((before == '\0' || before == '(') &&
          (after.isDigit() || after == '\0' || after == ')')) {
        res += str[i];
      } else if ((before == ')' || before.isDigit() || before.isLetter()) &&
                 (after.isDigit() || after.isLetter())) {
        res += ' ';
        res += str[i];
        res += ' ';
      } else if ((before.isDigit() || before == ')') && after == '(') {
        res += ' ';
        res += str[i];
        res += ' ';
      } else if ((before == '(') && after == '(') {
        res += ' ';
        res += str[i];
      } else {
        res += str[i];
      }
    } else {
      res += str[i];
    }
  }

  return (res);
}

// ----------------------------------------------------------------------------

QString ValidateText::ReplaceDummyFunctions(QString str) {
  QString res;

  if (str.indexOf("atan") != -1) {
    str = str.replace("atan", "atn");
  } else if (str.indexOf("asin") != -1) {
    str = str.replace("asin", "asn");
  } else if (str.indexOf("acos") != -1) {
    str = str.replace("acos", "acs");
  } else if (str.indexOf("π") != -1) {
    str = str.replace("π", QString::number(M_PI));
  }

  res = str;

  return (res);
}

// ----------------------------------------------------------------------------

bool ValidateText::IsSign(QChar const &ch_) {
  int res = 0;
  if (ch_ == '*')
    res = 1;
  else if (ch_ == '/')
    res = 1;
  else if (ch_ == '-')
    res = 1;
  else if (ch_ == '+')
    res = 1;
  else if (ch_ == '^')
    res = 1;
  else if (ch_ == '%')
    res = 1;

  return (res);
}

// ----------------------------------------------------------------------------

void ValidateText::set_clear(bool const is_clear) { is_clear_ = is_clear; }

// ----------------------------------------------------------------------------

ValidateText::~ValidateText() {}

}  // namespace ns_model
