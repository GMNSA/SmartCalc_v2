#include "../../includes/Model/modelcalculator.hpp"

namespace ns_model {

ModelCalculator::ModelCalculator() : is_error_(false) {}

ModelCalculator::~ModelCalculator() {}

QStack<QString> ModelCalculator::get_stack() const { return stack_; }

// -- -- -- --

QString ModelCalculator::CalculateNotation(QString const &str) {
  return str.toUpper();
}

// -- -- -- --

qint64 ModelCalculator::Priority(QChar ch_) {
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

bool ModelCalculator::IsSign(QChar ch) {
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

bool ModelCalculator::IsMathFunction(QString str) {
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

bool ModelCalculator::IsCustomNumber(QString str) {
  bool res = 1;

  for (QChar const &let : str) {
    if ((!let.isDigit()) && let != '.' && let != '-') res = 0;
  }

  return res;
}

// ----------------------------------------------------------------------------

qint64 ModelCalculator::FindStr(QString const &str, QString const &needle,
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

qint64 ModelCalculator::AddMathFunction(QString const &src, qint64 i_begin) {
  qint64 res = -1;

  if (!src.isEmpty()) {
    if ((res = FindStr(src, "cos", i_begin)) != -1) {
      // push_stack(stack, "cos");
      stack_.push_back("cos");
    } else if ((res = FindStr(src, "sin", i_begin)) != -1) {
      stack_.push_back("sin");
      // push_stack(stack, "sin");
    } else if ((res = FindStr(src, "alg", i_begin)) != -1) {
      stack_.push_back("alg");
      // push_stack(stack, "alg");
    } else if ((res = FindStr(src, "tan", i_begin)) != -1) {
      stack_.push_back("tan");
      // push_stack(stack, "tan");
    } else if ((res = FindStr(src, "acs", i_begin)) != -1) {
      stack_.push_back("acs");
      // push_stack(stack, "acs");
    } else if ((res = FindStr(src, "asn", i_begin)) != -1) {
      stack_.push_back("asn");
      // push_stack(stack, "asn");
    } else if ((res = FindStr(src, "atn", i_begin)) != -1) {
      stack_.push_back("atn");
      // push_stack(stack, "atn");
    } else if ((res = FindStr(src, "sqrt", i_begin)) != -1) {
      stack_.push_back("sqrt");
      // push_stack(stack, "sqrt");
    } else if ((res = FindStr(src, "ln", i_begin)) != -1) {
      stack_.push_back("ln");
      // push_stack(stack, "ln");
    } else if ((res = FindStr(src, "log", i_begin)) != -1) {
      stack_.push_back("log");
      // push_stack(stack, "log");
    } else if ((res = FindStr(src, "mod", i_begin)) != -1) {
      stack_.push_back("mod");
      // push_stack(stack, "mod");
    }

    // *i_begin = res != -1 ? res : *i_begin;
  }
  if (res == -1) is_error_ = true;

  // return (res);
  return res != -1 ? (unsigned)res : i_begin;
}

// -- -- -- --

bool ModelCalculator::IsFindInStackBrackets(QStack<QString> const &stack) {
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

QString ModelCalculator::StrToPostfix(QString const &str) {
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
        // if (add_math_function(str_, &i, &s) == -1) is_error = 1;
      } else if (c == '(') {
        stack_.push_back("(");
      } else if (c == ')') {
        if (c == ')' && prev_ch == '(') is_error_ = 1;
        while (!stack_.isEmpty() && stack_.last() != "(" && !is_error_) {
          tmp = stack_.pop();
          res += " ";
          res += tmp;
        }
        if (stack_.isEmpty() || (stack_.last() != "(")) {
          is_error_ = 1;
        }
        // stack_.clear();
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

QHash<QString, qint64> ModelCalculator::GetNumberFromString(QString str,
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

QStack<QString> ModelCalculator::StringToStack(QString const &str) {
  QStack<QString> tmp;
  auto split_str = str.split(' ');

  for (auto &word : split_str) {
    if (!word.isEmpty()) tmp.push_back(word);
  }

  return tmp;
}

}  // namespace ns_model
