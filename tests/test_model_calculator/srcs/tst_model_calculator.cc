#include "../includes/tst_model_calculator.hpp"

#include <gtest/gtest.h>

#include <QHash>
#include <QRegularExpression>
#include <QStack>

QString ModalCalculatorTest::Calculate(QString const &str, QString const &x) {
  model_calculator_->Calculate(str, x);
  return model_calculator_->GetResult();
}

// -- -- -- --

QString ModalCalculatorTest::GetResult() const {
  return model_calculator_->GetResult();
}

// -- -- -- --

void ModalCalculatorTest::ChangeSign() { model_calculator_->ChangeSign(); }

// -- -- -- --

void ModalCalculatorTest::AddValue(QString const &str) {
  model_calculator_->AddValue(str);
}

// -- -- -- --

QString ModalCalculatorTest::FixTextDisplay() const {
  return model_calculator_->FixTextDisplay();
}

// -- -- -- --

void ModalCalculatorTest::Reset() { model_calculator_->Reset(); }

// ----------------------------------------------------------------------------

TEST_F(ModalCalculatorTest, TestChangeSign) {
  AddValue("2");
  AddValue("*");
  AddValue("2");
  QString res = FixTextDisplay();
  EXPECT_EQ(res, "2 * 2");

  // -- -- -- --

  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "-(2 * 2)");

  // -- -- -- --

  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "2 * 2");

  // -- -- -- --

  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "-(2 * 2)");
  AddValue("+");
  AddValue("8");
  res = FixTextDisplay();
  EXPECT_EQ(res, "-(2 * 2) + 8");

  // -- -- -- --

  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "-(-(2 * 2) + 8)");

  // -- -- -- --

  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "-(2 * 2) + 8");

  // -- -- -- --

  res = FixTextDisplay();
  EXPECT_EQ(res, "-(2 * 2) + 8");
  AddValue("+");
  AddValue("sin(");
  AddValue("19");
  AddValue(")");
  res = FixTextDisplay();
  EXPECT_EQ(res, "-(2 * 2) + 8 + sin(19)");

  // -- -- -- --

  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "-(-(2 * 2) + 8 + sin(19))");

  // -- -- -- --

  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "-(2 * 2) + 8 + sin(19)");
  AddValue("+");
  AddValue("cos(");
  AddValue("20");
  AddValue(")");
  res = FixTextDisplay();
  EXPECT_EQ(res, "-(2 * 2) + 8 + sin(19) + cos(20)");

  // -- -- -- --

  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "-(-(2 * 2) + 8 + sin(19) + cos(20))");

  // -- -- -- --

  Reset();

  AddValue("0");
  res = FixTextDisplay();
  EXPECT_EQ(res, "0");
  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "-0");
  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "0");
  AddValue("+");
  AddValue("8");
  res = FixTextDisplay();
  Calculate();
  res = GetResult();
  EXPECT_EQ(res, "8");
  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "-8");
  ChangeSign();
  res = FixTextDisplay();
  EXPECT_EQ(res, "8");
  AddValue("3");
  AddValue("2");
  res = FixTextDisplay();
  EXPECT_EQ(res, "832");
  ChangeSign();
  res = FixTextDisplay();
  qDebug() << "res: " << res;
  EXPECT_EQ(res, "-832");
}

// ----------------------------------------------------------------------------

TEST_F(ModalCalculatorTest, TestXCoordinates) {
  // TODO(_who): release test

  QString res = Calculate("2 * 2");

  // -- -- -- --

  res = Calculate("2 + 2 * x", "2");

  res = Calculate("x");
  EXPECT_EQ(res, "0");
}

// -- -- -- --

TEST_F(ModalCalculatorTest, TestPriority) {
  // QChar sign = '*';
  // qint64 res = Priority(sign);
  // qDebug() << "res: " << res;
}

// ----------------------------------------------------------------------------

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
