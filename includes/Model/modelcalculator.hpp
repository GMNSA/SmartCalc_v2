#ifndef INCLUDES_MODEL_MODELCALCULATOR_HPP_
#define INCLUDES_MODEL_MODELCALCULATOR_HPP_

#include <QHash>
#include <QStack>

#include "./imodel.hpp"

namespace ns_model {

class ModelCalculator : public IModel {
 public:
  ModelCalculator();
  ModelCalculator(ModelCalculator const &other) = delete;
  ModelCalculator &operator=(ModelCalculator const &other) = delete;

  virtual ~ModelCalculator();

  void ResetError();
  bool get_error() const;
  QStack<QString> get_stack() const;
  bool IsNumber(QString const &str) const;
  QString CalculateNotation(QString const &str) override;
  qint64 Priority(QChar ch);
  bool IsSign(QChar ch);
  bool IsMathFunction(QString str);
  bool IsCustomNumber(QString str);
  qint64 FindStr(QString const &str, QString const &needle, qint64 i_begin);
  qint64 AddMathFunction(QString const &src, qint64 i_begin);
  QHash<QString, qint64> GetNumberFromString(QString str, qint64 i_begin);
  bool IsFindInStackBrackets(QStack<QString> const &stack);
  QString StrToPostfix(QString const &str);
  QStack<QString> StringToStack(QString const &str);
  double CalculateNumbersMul(double num1, QString const &str, double num2);
  double CalculateStrNumbersSingle(QString const &str_num, QString const &str);
  QString RoundNum(QString str);
  QString RemoveZeros(QString str);

  template <typename T>
  void ReverseStack(QStack<T> *stack, qint64 n_stack);

  // -- -- -- --

 private:
  bool is_error_;
  QStack<QString> stack_;
  QString str_data_tmp_;
  QStack<QString> sp_str_split_;
  QStack<QString> sp_tmp_data_;
};

// ----------------------------------------------------------------------------

template <typename T>
void ModelCalculator::ReverseStack(QStack<T> *stack, qint64 n_stack) {
  QStack<T> tmp;
  if (stack && n_stack <= stack->size()) {
    while (!stack->isEmpty()) tmp.push_back(stack->pop());
  }
  *stack = tmp;
}

};  // namespace ns_model

#endif  // INCLUDES_MODEL_MODELCALCULATOR_HPP_
