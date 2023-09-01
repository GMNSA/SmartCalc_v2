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

  QStack<QString> get_stack() const;
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

  // -- -- -- --

 private:
  bool is_error_;
  QStack<QString> stack_;
  QString data_tmp_;
  QStack<QString> str_split_;
};

};  // namespace ns_model

#endif  // INCLUDES_MODEL_MODELCALCULATOR_HPP_
