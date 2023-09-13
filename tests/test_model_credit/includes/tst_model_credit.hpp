#ifndef TESTS_TEST_MODEL_credit_INCLUDES_TST_MODEL_credit_HPP_
#define TESTS_TEST_MODEL_credit_INCLUDES_TST_MODEL_credit_HPP_

#include <gtest/gtest.h>

#include <QDebug>

#include "../../../includes/Model/modelcredit.hpp"
#include "../../../includes/custom_types.hpp"

class ModelCreditTest : public ::testing::Test {
 public:
  ModelCreditTest() : model_credit_(new s21::ModelCredit) {
    // initialization code here
  }

  void SetUp() {
    // code here will execute just before the test ensues
  }

  void TearDown() {
    // code here will be called just after the test completes
    // ok to through exceptions from here if need be
  }

  ~ModelCreditTest() {
    // cleanup any pending stuff, but no exceptions allowed
    if (model_credit_) delete model_credit_;
  }
  // put in any custom data members that you need
 private:
  s21::ModelCredit *model_credit_;
};

#endif  // TESTS_TEST_MODEL_credit_INCLUDES_TST_MODEL_credit_HPP_
