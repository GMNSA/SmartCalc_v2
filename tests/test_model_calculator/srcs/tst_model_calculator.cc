#include "../includes/tst_model_calculator.hpp"

#include <gtest/gtest.h>

#include <QHash>
#include <QRegularExpression>
#include <QStack>

QString ModalCalculatorTest::Calculate(QString const &str, QString const &x) {
  model_calculator_->Calculate(str, x);
  return model_calculator_->GetResult();
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
