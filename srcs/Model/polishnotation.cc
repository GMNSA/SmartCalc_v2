#include "../../includes/Model//polishnotation.hpp"

#include <QRegularExpression>
#include <cmath>

namespace ns_model {

PolishNotation::PolishNotation() : is_error_(false) {}

PolishNotation::~PolishNotation() {}

void PolishNotation::ResetError() { is_error_ = 0; }

// -- -- -- --

void PolishNotation::Reset() {
  ResetError();
  stack_.clear();
  str_data_tmp_.clear();
  sp_str_split_.clear();
  sp_tmp_data_.clear();
  text_.clear();
}

// -- -- -- --

bool PolishNotation::get_error() const { return is_error_; }

// -- -- -- --

QStack<QString> PolishNotation::get_stack() const { return stack_; }

// -- -- -- --

bool PolishNotation::IsNumber(QString const &str) const {
  QRegularExpression re("^[-]?[0-9]+(\\.[0-9]+)?$");
  bool res = re.match(str).hasMatch();

  return res;
}

// -- -- -- --

QString PolishNotation::CalculateNotation(QString const &str) {
  QString p_result;
  is_error_ = 0;
  double tmp_num = 0;
  Q_UNUSED(tmp_num);
  Q_UNUSED(str);
  sp_tmp_data_.clear();

  if (!str.isEmpty()) {
    sp_str_split_ = StringToStack(str);
    QString p_tmp;
    QString p_one_arg;
    QString p_two_arg;
    QString p_sign_arg;

    ReverseStack(&sp_str_split_, sp_str_split_.size());

    for (auto const &word : sp_str_split_) {
      Q_UNUSED(word);

      p_tmp = sp_str_split_.top();
      sp_tmp_data_.push_back(p_tmp);

      if (!(sp_tmp_data_.isEmpty())) {
        if (sp_tmp_data_.size() >= 2 && p_tmp[0] == '~') {
          sp_tmp_data_.pop();
          p_one_arg = sp_tmp_data_.pop();
          tmp_num = p_one_arg.toDouble();

          tmp_num = CalculateNumbersMul(0, "-", tmp_num);
          p_tmp = QString::number(tmp_num, 'f', 12);
          sp_tmp_data_.push_back(p_tmp);

          p_one_arg.clear();
          p_tmp.clear();
        } else if (sp_tmp_data_.size() >= 2 && IsMathFunction(p_tmp)) {
          p_sign_arg = sp_tmp_data_.pop();
          p_one_arg = sp_tmp_data_.pop();

          if (!IsNumber(p_one_arg)) is_error_ = 1;

          tmp_num = CalculateStrNumbersSingle(p_one_arg, p_sign_arg);
          if (std::isnan(tmp_num)) is_error_ = 1;
          p_tmp = QString::number(tmp_num, 'f', 12);
          sp_tmp_data_.push_back(p_tmp);
          p_sign_arg.clear();
          p_one_arg.clear();
          p_two_arg.clear();
          p_tmp.clear();

        } else if (sp_tmp_data_.size() >= 3 && IsSign(p_tmp[0])) {
          p_sign_arg = sp_tmp_data_.pop();
          p_two_arg = sp_tmp_data_.pop();
          p_one_arg = sp_tmp_data_.pop();

          if (!IsNumber(p_two_arg) || !IsNumber(p_one_arg)) is_error_ = 1;

          tmp_num = CalculateNumbersMul(p_one_arg.toDouble(), p_sign_arg,
                                        p_two_arg.toDouble());
          p_tmp.setNum(tmp_num, 'f', 12);
          sp_tmp_data_.push_back(p_tmp);

          p_sign_arg.clear();
          p_one_arg.clear();
          p_two_arg.clear();
          p_tmp.clear();
        }
      }

      if (is_error_) {
        break;
      }
      sp_str_split_.pop();
    }

  } else {
    is_error_ = 1;
  }

  if (sp_tmp_data_.size() == 1 && !is_error_) {
    p_result = sp_tmp_data_.pop();
  } else {
    p_result = "error";
  }

  p_result = p_result.left(p_result.indexOf('.') + 8);
  ZerosRemove(&p_result);

  return (p_result);
}

// -- -- -- --

qint64 PolishNotation::Priority(QChar const &ch_) {
  qint64 res = 0;

  if (ch_ == '(' || ch_ == ')')
    res = 6;
  else if (ch_ == 'c' || ch_ == 's' || ch_ == 't' || ch_ == 'l' || ch_ == 'a')
    res = 5;
  else if (ch_ == '~')
    res = 4;
  else if (ch_ == '^' || ch_ == '%')
    res = 3;
  else if (ch_ == '*' || ch_ == '/')
    res = 2;
  else if (ch_ == '+' || ch_ == '-')
    res = 1;
  else
    res = 0;

  return (res);
}

// -- -- -- --

bool PolishNotation::IsSign(QChar const &ch) {
  bool is_res = 0;

  if (ch == '^')
    is_res = 1;
  else if (ch == '*')
    is_res = 1;
  else if (ch == '/')
    is_res = 1;
  else if (ch == '+')
    is_res = 1;
  else if (ch == '-')
    is_res = 1;
  else if (ch == '%')
    is_res = 1;
  else
    is_res = 0;

  return (is_res);
}

// -- -- -- --

bool PolishNotation::IsMathFunction(QString const &str) {
  bool res = 0;

  if (!str.isEmpty()) {
    if (str == "cos") res = 1;
    if (str == "sin") res = 1;
    if (str == "tan") res = 1;
    if (str == "acs") res = 1;
    if (str == "asn") res = 1;
    if (str == "atn") res = 1;
    if (str == "sqrt") res = 1;
    if (str == "ln") res = 1;
    if (str == "log") res = 1;
  }

  return (res);
}

// -- -- -- --

bool PolishNotation::IsCustomNumber(QString const &str) {
  bool res = 1;

  for (QChar const &let : str) {
    if ((!let.isDigit()) && let != '.' && let != '-') res = 0;
  }

  return res;
}

// ----------------------------------------------------------------------------

qint64 PolishNotation::FindStr(QString const &str, QString const &needle,
                               qint64 i_begin) {
  qint64 res = -1;

  if (!str.isEmpty() && !needle.isEmpty()) {
    unsigned n_str = str.length();
    unsigned n_needle = needle.length();

    if (n_str >= n_needle) {
      unsigned i_str = i_begin;
      int i_needle = 0;
      for (; i_str < n_str; ++i_str, ++i_needle) {
        if (needle[i_needle] == '\0' || (str[i_str] != needle[i_needle])) {
          break;
        }
      }
      if ((unsigned)i_needle == n_needle) {
        res = i_begin + i_needle - 1;
      }
    }
  }

  return res;
}

// -- -- -- --

qint64 PolishNotation::AddMathFunction(QString const &src, qint64 i_begin) {
  qint64 res = -1;

  if (!src.isEmpty()) {
    if ((res = FindStr(src, "cos", i_begin)) != -1) {
      stack_.push_back("cos");
    } else if ((res = FindStr(src, "sin", i_begin)) != -1) {
      stack_.push_back("sin");
    } else if ((res = FindStr(src, "alg", i_begin)) != -1) {
      stack_.push_back("alg");
    } else if ((res = FindStr(src, "tan", i_begin)) != -1) {
      stack_.push_back("tan");
    } else if ((res = FindStr(src, "acs", i_begin)) != -1) {
      stack_.push_back("acs");
    } else if ((res = FindStr(src, "asn", i_begin)) != -1) {
      stack_.push_back("asn");
    } else if ((res = FindStr(src, "atn", i_begin)) != -1) {
      stack_.push_back("atn");
    } else if ((res = FindStr(src, "sqrt", i_begin)) != -1) {
      stack_.push_back("sqrt");
    } else if ((res = FindStr(src, "ln", i_begin)) != -1) {
      stack_.push_back("ln");
    } else if ((res = FindStr(src, "log", i_begin)) != -1) {
      stack_.push_back("log");
    } else if ((res = FindStr(src, "mod", i_begin)) != -1) {
      stack_.push_back("mod");
    }
  }
  if (res == -1) is_error_ = true;

  return res != -1 ? (unsigned)res : i_begin;
}

// -- -- -- --

bool PolishNotation::IsFindInStackBrackets(QStack<QString> const &stack) {
  bool is_find_brackets = 0;

  for (auto const &word : stack) {
    if ((word == "(") || word == ")") {
      is_find_brackets = 1;
      break;
    }
  }

  return (is_find_brackets);
}

// -- -- -- --

QString PolishNotation::StrToPostfix(QString const &str) {
  QStack<QString> s;
  QString tmp = "";
  QString res = "";

  is_error_ = 0;

  if (str.isEmpty()) is_error_ = 1;

  if (!is_error_) {
    unsigned n_str = str.length();
    QChar prev_ch = '\0';
    QChar c = '\0';
    QChar op = '\0';

    for (unsigned i = 0; i < n_str; ++i) {
      c = str[i];
      if (c.isDigit() || c == 'x') {
        if (c == 'x') {
          if (!res.isEmpty()) res += " ";
          res += c;
        } else {
          auto tmp_data = GetNumberFromString(str, i);
          tmp = tmp_data.begin().key();
          i = tmp_data.begin().value();
          --i;
          if (!res.isEmpty()) res += " ";
          res += tmp;
        }
      } else if (c.isLetter()) {
        i = AddMathFunction(str, i);
      } else if (c == '(') {
        stack_.push_back("(");
      } else if (c == ')') {
        if (c == ')' && prev_ch == '(') is_error_ = 1;
        while (!stack_.isEmpty() && stack_.last() != "(" && !is_error_) {
          tmp = stack_.pop();
          res += " " + tmp;
        }
        if (stack_.isEmpty() || (stack_.last() != "(")) {
          is_error_ = 1;
        }
        stack_.pop();
      } else if (IsSign(c) && Priority(c)) {
        op = c;

        if (op == '-' &&
            (i == 0 || (i >= 1 && (IsSign(prev_ch) || prev_ch == '(')))) {
          op = '~';
        }

        while (!stack_.isEmpty() &&
               (Priority(stack_.last()[0]) >= Priority(op)) &&
               Priority(stack_.last()[0]) <= 5) {
          tmp = stack_.pop();
          res += " ";
          res += tmp;
        }
        stack_.push_back(op);
      }

      if ((c == '-' && prev_ch == '-') ||
          ((prev_ch.isLetter() && prev_ch != 'x') && c != '('))
        is_error_ = 1;

      if (c != ' ') prev_ch = c;

      if (is_error_) break;
    }

    is_error_ = is_error_ ? is_error_ : IsFindInStackBrackets(stack_);

    if (!is_error_) {
      while (!stack_.isEmpty()) {
        tmp = stack_.pop();
        res += " ";
        res += tmp;
      }
    } else {
      res.clear();
    }
    stack_.clear();
  }

  return (res);
}

// -- -- -- --

QHash<QString, qint64> PolishNotation::GetNumberFromString(QString str,
                                                           qint64 i_begin) {
  QString tmp = "";
  qint64 n_str = str.length();

  for (; i_begin < n_str && (str[i_begin].isDigit() || str[i_begin] == '.');
       ++i_begin) {
    tmp += str[i_begin];
  }

  QHash<QString, qint64> res;
  res.insert(tmp, i_begin);

  return {res};
}

// -- -- -- --

QStack<QString> PolishNotation::StringToStack(QString const &str) {
  QStack<QString> tmp;
  auto split_str = str.split(' ');

  for (auto &word : split_str) {
    if (!word.isEmpty()) tmp.push_back(word);
  }

  return tmp;
}

// -- -- -- --

double PolishNotation::CalculateNumbersMul(double num1, QString const &str,
                                           double num2) {
  double res = 0.0;

  if (!str.isEmpty() && is_error_ != true) {
    if (str == "+") {
      res = num1 + num2;
    } else if (str == "-") {
      res = num1 - num2;
    } else if (str == "/") {
      res = num1 / num2;
    } else if (str == "*") {
      res = num1 * num2;
    } else if (str == "^") {
      res = pow(num1, num2);
    } else if (str == "%") {
      res = fmod(num1, num2);
    } else {
      is_error_ = 1;
    }
  } else {
    is_error_ = 1;
  }

  return res;
}

// -- -- -- --

double PolishNotation::CalculateStrNumbersSingle(QString const &str_num,
                                                 QString const &str) {
  double res = 0;

  if (!str_num.isEmpty() && (is_error_) == false) {
    QString tmp;
    if (str == "sin") {
      res = std::sin(str_num.toDouble());
    } else if (str == "cos") {
      res = std::cos(str_num.toDouble());
    } else if (str == "tan") {
      res = std::tan(str_num.toDouble());
    } else if (str == "acs") {
      res = std::acos(str_num.toDouble());
    } else if (str == "asn") {
      res = std::asin(str_num.toDouble());
    } else if (str == "atn") {
      res = std::atan(str_num.toDouble());
    } else if (str == "sqrt") {
      res = std::sqrt(str_num.toDouble());
    } else if (str == "ln") {
      res = std::log(str_num.toDouble());
    } else if (str == "log") {
      res = std::log10(str_num.toDouble());
    } else {
      is_error_ = true;
    }
  } else {
    is_error_ = true;
  }

  return res;
}

// ----------------------------------------------------------------------------

void PolishNotation::ZerosRemove(QString *str) {
  if (str) {
    unsigned n_str = str->length() - 1;
    for (int i = n_str; i > 0 && (str->at(i) == '0' || str->at(i) == '.');
         --i) {
      if (str->at(i) == '0' && i > 1) {
        str->truncate(i);
      } else if (str->at(i) == '.') {
        str->truncate(i);
        i = 1;
      }
    }
  }
}

}  // namespace ns_model
