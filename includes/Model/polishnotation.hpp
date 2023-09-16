#ifndef INCLUDES_MODEL_POLISHNOTATION_HPP_
#define INCLUDES_MODEL_POLISHNOTATION_HPP_

#include <gtest/gtest_prod.h>

#include <QHash>
#include <QStack>

namespace s21 {

class PolishNotation {
 public:
  PolishNotation();
  PolishNotation(PolishNotation const &other) = delete;
  PolishNotation &operator=(PolishNotation const &other) = delete;

  virtual ~PolishNotation();

  QString CalculateNotation(QString const &str);

 public:
  void ResetError();
  void Reset();
  bool get_error() const;
  QStack<QString> get_stack() const;
  bool IsNumber(QString const &str) const;

  /**
   * @brief Priority of operations.
   *            The more importatn the operation, the higher the number.
   *
   * @param ch -> Sign.
   *
   * @return   -> from 0 -> 6.
   */
  qint64 Priority(QChar const &ch);
  bool IsSign(QChar const &ch);
  bool IsMathFunction(QString const &str);
  bool IsCustomNumber(QString const &str);
  qint64 FindStr(QString const &str, QString const &needle, qint64 i_begin);
  qint64 AddMathFunction(QString const &src, qint64 i_begin);
  QHash<QString, qint64> GetNumberFromString(QString str, qint64 i_begin);
  bool IsFindInStackBrackets(QStack<QString> const &stack);
  QString StrToPostfix(QString const &str);
  QStack<QString> StringToStack(QString const &str);

  /**
   * @brief Calculation of actions (multiplication, division, etc.).
   *
   * @param num1  -> First number.
   * @param str   -> Action.
   * @param num2  -> Second number.
   *
   * @return      -> Result number.
   */
  double CalculateNumbersMul(double num1, QString const &str, double num2);

  /**
   * @brief  Calculation of functons (cos, sin, etc.).
   *
   * @param str_num -> String number.
   * @param str     -> Function.
   *
   * @return  -> Result (double)
   */
  double CalculateStrNumbersSingle(QString const &str_num, QString const &str);

  /**
   * @brief Removing extra zeros after the dot.
   *
   * @param str -> String number.
   */
  void ZerosRemove(QString *str);

  // -- templates  --

  template <typename T>
  void ReverseStack(QStack<T> *stack, qint64 const n_stack);

  // -- -- -- --

 private:
  bool is_error_;
  QStack<QString> stack_;
  QString str_data_tmp_;
  QStack<QString> str_split_;
  QStack<QString> data_stack_;
  QString text_;

 private:
  friend class PolishNotationTest;
};

// ----------------------------------------------------------------------------

template <typename T>
void PolishNotation::ReverseStack(QStack<T> *stack, qint64 const n_stack) {
  QStack<T> tmp;
  if (stack && n_stack <= stack->size()) {
    while (!stack->isEmpty()) tmp.push_back(stack->pop());
  }
  *stack = tmp;
}

}  // namespace s21

#endif  // INCLUDES_MODEL_POLISHNOTATION_HPP_
