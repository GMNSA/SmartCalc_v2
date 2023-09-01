#include "../includes/tst_model_calculator.hpp"

#include <gtest/gtest.h>

#include <QHash>
#include <QStack>

QStack<QString> ModelCalculatorTest::get_stack() const {
  return model_calculator_->get_stack();
}

QString ModelCalculatorTest::CalculateNotation(QString str) {
  return model_calculator_->CalculateNotation(str);
}

qint64 ModelCalculatorTest::Priority(QChar ch) {
  return model_calculator_->Priority(ch);
}

bool ModelCalculatorTest::IsSign(QChar ch) {
  return model_calculator_->IsSign(ch);
}

bool ModelCalculatorTest::IsMathFunction(QString str) {
  return model_calculator_->IsMathFunction(str);
}

bool ModelCalculatorTest::IsCustomNumber(QString str) {
  return model_calculator_->IsCustomNumber(str);
}

qint64 ModelCalculatorTest::FindStr(QString const &str, QString const &needle,
                                    qint64 i) {
  return model_calculator_->FindStr(str, needle, i);
}

qint64 ModelCalculatorTest::AddMathFunction(QString const &src,
                                            qint64 i_begin) {
  return model_calculator_->AddMathFunction(src, i_begin);
}

QHash<QString, qint64> ModelCalculatorTest::GetNumberFromString(
    QString str, qint64 i_begin) {
  return model_calculator_->GetNumberFromString(str, i_begin);
}

bool ModelCalculatorTest::IsFindInStackBrackets(QStack<QString> const &stack) {
  return model_calculator_->IsFindInStackBrackets(stack);
}

QString ModelCalculatorTest::StrToPostfix(QString const &str) {
  return model_calculator_->StrToPostfix(str);
}

QStack<QString> ModelCalculatorTest::StringToStack(QString const &str) {
  return model_calculator_->StringToStack(str);
}

// ----------------------------------------------------------------------------

TEST_F(ModelCalculatorTest, TestPriority) {
  QChar sign = '*';
  qint64 res = Priority(sign);
  qDebug() << "res: " << res;
}

// -- -- -- --

TEST_F(ModelCalculatorTest, TestIsSign) {
  // Exercises the Xyz feature of Foo.

  EXPECT_TRUE(IsSign('^'));
  EXPECT_TRUE(IsSign('*'));
  EXPECT_TRUE(IsSign('+'));
  EXPECT_TRUE(IsSign('-'));
  EXPECT_TRUE(IsSign('/'));
  EXPECT_TRUE(IsSign('%'));
  EXPECT_FALSE(IsSign('l'));
  EXPECT_FALSE(IsSign('!'));
}

// -- -- -- --

TEST_F(ModelCalculatorTest, IsMathFunction) {
  EXPECT_FALSE(IsMathFunction("llog"));
  EXPECT_FALSE(IsMathFunction("og"));
  EXPECT_FALSE(IsMathFunction("coss"));
  EXPECT_FALSE(IsMathFunction("solo"));
  EXPECT_FALSE(IsMathFunction("tang"));

  EXPECT_TRUE(IsMathFunction("cos"));
  EXPECT_TRUE(IsMathFunction("sin"));
  EXPECT_TRUE(IsMathFunction("tan"));
  EXPECT_TRUE(IsMathFunction("acs"));
  EXPECT_TRUE(IsMathFunction("asn"));
  EXPECT_TRUE(IsMathFunction("atn"));
  EXPECT_TRUE(IsMathFunction("sqrt"));
  EXPECT_TRUE(IsMathFunction("ln"));
  EXPECT_TRUE(IsMathFunction("log"));
}

// -- -- -- --

TEST_F(ModelCalculatorTest, TestIsCustomNumber) {
  EXPECT_FALSE(IsCustomNumber("39a28"));
  EXPECT_FALSE(IsCustomNumber("39+28"));
  EXPECT_FALSE(IsCustomNumber("+3928"));
  EXPECT_FALSE(IsCustomNumber("0.o"));
  EXPECT_FALSE(IsCustomNumber("k"));

  EXPECT_TRUE(IsCustomNumber("3928"));
  EXPECT_TRUE(IsCustomNumber("-3914"));
  EXPECT_TRUE(IsCustomNumber("-49.424"));
  EXPECT_TRUE(IsCustomNumber("49920.0042"));
}

// -- -- -- --

TEST_F(ModelCalculatorTest, TestFindStr) {
  QString str = "there is no spoon.";
  const char *needle = "the";
  qint64 i = 0;
  qint64 n = FindStr(str, needle, i);

  EXPECT_NE(n, 1);
  EXPECT_EQ(n, 2);

  str = "there is no spoon.";
  needle = "there";
  i = 0;

  n = FindStr(str, needle, i);
  EXPECT_EQ(n, 4);

  str = "there is no spoon.";
  needle = "ehere";
  i = 0;

  n = FindStr(str, needle, i);
  EXPECT_EQ(n, -1);

  str = "there is no spoon.";
  needle = "t";
  i = 0;

  n = FindStr(str, needle, i);
  EXPECT_EQ(n, 0);

  /* *****  ***** */
  str = "cos(2 * x)";
  needle = "cos";
  i = 0;

  n = FindStr(str, needle, i);
  EXPECT_EQ(n, 2);
}

// -- -- -- --

TEST_F(ModelCalculatorTest, TestAddMathFunctions) {
  QStack<QString> dest;
  QString src = "There srcsis nolnmod spooon. cosalog";
  unsigned n_src = src.length();
  QString tmp = "";

  for (qint64 i = 0; i < n_src && i != -1; ++i) {
    i = AddMathFunction(src, i);
  }

  dest = get_stack();

  if (dest.isEmpty())
    tmp = "";
  else
    tmp = dest.pop();
  EXPECT_EQ(tmp, "log");

  if (dest.isEmpty())
    tmp = "";
  else
    tmp = dest.pop();
  EXPECT_EQ(tmp, "cos");

  if (dest.isEmpty())
    tmp = "";
  else
    tmp = dest.pop();
  EXPECT_EQ(tmp, "mod");

  if (dest.isEmpty())
    tmp = "";
  else
    tmp = dest.pop();
  EXPECT_EQ(tmp, "ln");

  if (dest.isEmpty())
    tmp = "";
  else
    tmp = dest.pop();
  EXPECT_EQ(tmp, "");
}

// -- -- -- --

TEST_F(ModelCalculatorTest, TestGetNumberFromString) {
  QString str = "t32.42 8th";
  auto res = GetNumberFromString(str, 0);

  EXPECT_EQ(res.begin().key(), "");
  EXPECT_EQ(res.begin().value(), 0);

  res = GetNumberFromString(str, 1);
  EXPECT_EQ(res.begin().key(), "32.42");
  EXPECT_EQ(res.begin().value(), 6);

  res = GetNumberFromString(str, 6);
  EXPECT_EQ(res.begin().key(), "");
  EXPECT_EQ(res.begin().value(), 6);

  res = GetNumberFromString(str, 7);
  EXPECT_EQ(res.begin().key(), "8");
  EXPECT_EQ(res.begin().value(), 8);

  res = GetNumberFromString(str, 8);
  EXPECT_EQ(res.begin().key(), "");
  EXPECT_EQ(res.begin().value(), 8);

  res = GetNumberFromString(str, 9);
  EXPECT_EQ(res.begin().key(), "");
  EXPECT_EQ(res.begin().value(), 9);
}

// -- -- -- --

TEST_F(ModelCalculatorTest, TestIsFindInStackBrackets) {
  QStack<QString> s;

  s.push_back("there");
  s.push_back("is");
  s.push_back("no");
  s.push_back("spoon");

  bool res = IsFindInStackBrackets(s);

  EXPECT_EQ(res, 0);

  /* *****  ***** */
  s.push_back("(");
  res = IsFindInStackBrackets(s);
  EXPECT_EQ(res, 1);

  /* *****  ***** */

  s.clear();
  res = IsFindInStackBrackets(s);
  EXPECT_EQ(res, 0);

  /* *****  ***** */

  s.push_back(")");
  res = IsFindInStackBrackets(s);
  EXPECT_EQ(res, 1);
  s.clear();

  /* *****  ***** */

  s.push_back(")");
  s.push_back("there");
  res = IsFindInStackBrackets(s);
  EXPECT_EQ(res, 1);
  s.clear();

  /* *****  ***** */

  s.push_back(")");
  s.push_back("there");
  res = IsFindInStackBrackets(s);
  EXPECT_EQ(res, 1);
  s.clear();

  /* *****  ***** */

  res = IsFindInStackBrackets(s);
  EXPECT_EQ(res, 0);
}

// -- -- -- --

TEST_F(ModelCalculatorTest, TestStrToPostfix) {
  QString res = StrToPostfix("(8 + 2 * 5) / (1 + 3 * 2 - 4)");
  QString example = "8 2 5 * + 1 3 2 * + 4 - /";

  EXPECT_EQ(res, example);

  res = StrToPostfix("(8 + 2 * 5) / (1 + 3 * 2 - 4)");

  EXPECT_EQ(res, "8 2 5 * + 1 3 2 * + 4 - /");

  // -- -- -- --

  res = StrToPostfix("3 + 4 * 2 / (1 - 5) ^ 2");
  EXPECT_EQ(res, "3 4 2 * 1 5 - 2 ^ / +");

  /* *****  ***** */

  res = StrToPostfix("398 + 4487 * 224 / (128 - 548) ^ 20");
  EXPECT_EQ(res, "398 4487 224 * 128 548 - 20 ^ / +");

  /* *****  ***** */

  res = StrToPostfix("3.98 + 4 * 2.0 / (1.5 - 5) ^ 2");
  EXPECT_EQ(res, "3.98 4 2.0 * 1.5 5 - 2 ^ / +");

  /* *****  ***** */

  res = StrToPostfix("(3 + 4) * (2 / (1 - 5) ^ 2)");
  EXPECT_EQ(res, "3 4 + 2 1 5 - 2 ^ / *");

  /* *****  ***** */

  res = StrToPostfix("(3 + 4) * ((2) / (1 - 5) ^ 2)");
  EXPECT_EQ(res, "3 4 + 2 1 5 - 2 ^ / *");

  /* *****  ***** */

  res = StrToPostfix("(3 + 4) * ((2.8) / (1 - 5) ^ 2)");
  EXPECT_EQ(res, "3 4 + 2.8 1 5 - 2 ^ / *");

  /* *****  ***** */

  res = StrToPostfix("(-3 + 4) * ((2.8) / (1 - 5) ^ 2)");
  EXPECT_EQ(res, "3 ~ 4 + 2.8 1 5 - 2 ^ / *");

  /* *****  ***** */

  res = StrToPostfix("(-3 + 4) * ((-2.8) / (1 - 5) ^ 2)");
  EXPECT_EQ(res, "3 ~ 4 + 2.8 ~ 1 5 - 2 ^ / *");

  /* *****  ***** */

  res = StrToPostfix("(-3 + 4) * ((-2.8) / (-1 - 5) ^ +2)");
  EXPECT_EQ(res, "3 ~ 4 + 2.8 ~ 1 ~ 5 - ^ / 2 + *");

  /* *****  ***** */

  res = StrToPostfix("(-3 + 4) * ((-2.8) / (-1 - 5) ^ +(2))");
  EXPECT_EQ(res, "3 ~ 4 + 2.8 ~ 1 ~ 5 - ^ / 2 + *");

  /* *****  ***** */

  res = StrToPostfix("(-3 + 4) * ((-2.8) / (-1 - 5) ^ +(2)");
  EXPECT_TRUE(res.isEmpty());

  /* *****  ***** */

  res = StrToPostfix("(-3 + 4) * ((-2.8) / (1 - 5) ^ 2)");
  EXPECT_EQ(res, "3 ~ 4 + 2.8 ~ 1 5 - 2 ^ / *");

  /* *****  ***** */

  res = StrToPostfix("-(122.33 + 33)");
  EXPECT_EQ(res, "122.33 33 + ~");

  /* *****  ***** */

  res = StrToPostfix("-(122 + 33) + 28 - ((22 - 3) + (33 - 2))");
  EXPECT_EQ(res, "122 33 + ~ 28 + 22 3 - 33 2 - + -");

  /* *****  ***** */

  res = StrToPostfix("-(-42)+1");
  EXPECT_EQ(res, "42 ~ ~ 1 +");

  /* *****  ***** */

  res = StrToPostfix("2 / (3 - (4 + (5 * 6))) ");
  EXPECT_EQ(res, "2 3 4 5 6 * + - /");

  /* *****  ***** */

  res = StrToPostfix("-( -(129.0000000) * 6 )");
  EXPECT_EQ(res, "129.0000000 ~ 6 * ~");

  /* *****  ***** */

  res = StrToPostfix("(atn(8)*sqrt(4))+((ln(88.2)*ln(8.3))-3)");
  EXPECT_EQ(res, "8 atn 4 sqrt * 88.2 ln 8.3 ln * 3 - +");

  /* *****  ***** */

  res = StrToPostfix("(aton(8)*sqrt(4))+((ln(88.2)*ln(8.3))-3)");
  EXPECT_TRUE(res.isEmpty());

  /* *****  ***** */

  res = StrToPostfix("(atn(8)*sqrt(4))+((ln(88.2)*ln(8.3)) - 3)");
  EXPECT_EQ(res, "8 atn 4 sqrt * 88.2 ln 8.3 ln * 3 - +");

  /* *****  ***** */

  res = StrToPostfix("(-3 + 6) * -2");
  EXPECT_EQ(res, "3 ~ 6 + 2 ~ *");

  /* *****  ***** */

  res = StrToPostfix("(84 + x * (x - 473.938 * x - (x / x)))");
  EXPECT_EQ(res, "84 x x 473.938 x * - x x / - * +");

  /* *****  ***** */

  res = StrToPostfix(
      "(84 + x * (x - 473.938 * x - (x / x * atn(x)))) + cos(x) * mod(87.44)");
  EXPECT_EQ(res,
            "84 x x 473.938 x * - x x / x atn * - * + x cos 87.44 mod * +");

  /* *****  ***** */

  res = StrToPostfix("(84+x*(x-473.938*x-(x/x*atn(x))))+cos(x)*mod(87.44)");
  EXPECT_EQ(res,
            "84 x x 473.938 x * - x x / x atn * - * + x cos 87.44 mod * +");

  /* *****  ***** */

  res = StrToPostfix("((x * x / x + 0.1)) + (x * x * x * x * x)");
  EXPECT_EQ(res, "x x * x / 0.1 + x x * x * x * x * +");

  /* *****  ***** */

  res = StrToPostfix("alg(1) * atn(2)");
  EXPECT_EQ(res, "1 alg 2 atn *");

  /* *****  ***** */

  res = StrToPostfix("3--3");
  EXPECT_TRUE(res.isEmpty());
}

// -- -- -- --

TEST_F(ModelCalculatorTest, TestStringToStack) {
  QString str = "21 22 23 24";
  QString res = "";
  QStack<QString> stack;

  stack = StringToStack(str);

  EXPECT_TRUE(!stack.isEmpty());
  EXPECT_EQ(stack.size(), 4);

  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_EQ(res, "24");

  /* *****  ***** */
  stack.clear();

  str = "21 22 23 24  ";
  stack = StringToStack(str);

  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.size(), 4);

  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_EQ(res, "24");

  /* *****  ***** */

  str = "21 22 23 24        ";
  stack = StringToStack(str);

  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.size(), 4);

  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_EQ(res, "24");

  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_EQ(res, "23");

  /* *****  ***** */

  str = "       21 22 23 24        ";
  stack = StringToStack(str);

  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.size(), 4);

  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_EQ(res, "24");

  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_EQ(res, "23");

  /* *****  ***** */

  stack.clear();
  str = "1 ";
  stack = StringToStack(str);
  EXPECT_FALSE(stack.isEmpty());
  EXPECT_EQ(stack.size(), 1);
  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_EQ(res, "1");
  for (auto const &t : stack) qDebug() << "res: " << t;

  res.clear();
  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_TRUE(res.isEmpty());

  /* *****  ***** */

  str = "  ";
  stack = StringToStack(str);
  EXPECT_TRUE(stack.isEmpty());
  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_TRUE(res.isEmpty());

  /* *****  ***** */

  str = " ";
  stack = StringToStack(str);
  EXPECT_TRUE(stack.isEmpty());
  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_TRUE(res.isEmpty());

  /* *****  ***** */

  str = "";
  stack = StringToStack(str);
  EXPECT_TRUE(stack.isEmpty());
  if (!stack.isEmpty()) res = stack.pop();
  EXPECT_TRUE(res.isEmpty());
}

// ----------------------------------------------------------------------------

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
