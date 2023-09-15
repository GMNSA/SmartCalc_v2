#ifndef INCLUDES_MODELCREDIT_HPP_
#define INCLUDES_MODELCREDIT_HPP_

#include "./imodelcredit.hpp"

/**
 * @brief Class for tests.
 */
class ModelCreditTest;

// ----------------------------------------------------------------------------

namespace s21 {

class ModelCredit : public IModelCredit {
 public:
  ModelCredit();
  ModelCredit(ModelCredit const &other) = delete;
  ModelCredit &operator=(ModelCredit const &other) = delete;
  virtual ~ModelCredit();

  void Calculate() override;
  void set_sum(QString const &count) override;
  void set_time(QString const &count) override;
  void set_procent(QString const &count) override;
  void set_is_mount(bool const &is_mount) override;
  void set_different(bool const &is_diff) override;

  QString MonthlyPayment() const override;
  QString AccruedInterest() const override;
  QString DebgAndInterest() const override;

 private:
  void ResetData();
  void CalculatorAnnuit();
  void CalculatorDifferent();
  void MyRound(long double *num);

 private:
  quint64 sum_credit_;
  unsigned time_credit_;
  double procents_credit_;

  bool is_mount_;
  bool is_different_;

  long double mount_;
  long double mount_last_;
  long double procents_;
  long double total_;

  friend ModelCreditTest;
};

}  // namespace s21

#endif  // INCLUDES_MODELCREDIT_HPP_
