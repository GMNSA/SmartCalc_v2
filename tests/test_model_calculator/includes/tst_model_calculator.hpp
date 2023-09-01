#ifndef TESTS_TEST_MODEL_CALCULATOR_INCLUDES_TST_MODEL_CALCULATOR_HPP_
#define TESTS_TEST_MODEL_CALCULATOR_INCLUDES_TST_MODEL_CALCULATOR_HPP_

#include <gtest/gtest.h>

#include <QDebug>

#include "../../../includes/Model/modelcalculator.hpp"

class ModelCalculatorTest : public ::testing::Test {
 public:
  ModelCalculatorTest() : model_calculator_(new ns_model::ModelCalculator) {
    // initialization code here
  }

  void SetUp() {
    // code here will execute just before the test ensues
  }

  void TearDown() {
    // code here will be called just after the test completes
    // ok to through exceptions from here if need be
  }

  ~ModelCalculatorTest() {
    // cleanup any pending stuff, but no exceptions allowed
    if (model_calculator_) delete model_calculator_;
  }

  QStack<QString> get_stack() const;
  QString CalculateNotation(QString str);
  qint64 Priority(QChar ch);
  bool IsSign(QChar ch);
  bool IsMathFunction(QString str);
  bool IsCustomNumber(QString str);
  qint64 FindStr(QString const &str, QString const &needle, qint64 i);
  qint64 AddMathFunction(QString const &src, qint64 i_begin);
  QHash<QString, qint64> GetNumberFromString(QString str, qint64 i_begin);
  bool IsFindInStackBrackets(QStack<QString> const &stack);
  QString StrToPostfix(QString const &str);
  QStack<QString> StringToStack(QString const &str);

  // put in any custom data members that you need
 private:
  ns_model::ModelCalculator *model_calculator_;
};

#endif  // TESTS_TEST_MODEL_CALCULATOR_INCLUDES_TST_MODEL_CALCULATOR_HPP_
