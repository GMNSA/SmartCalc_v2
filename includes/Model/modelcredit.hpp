#ifndef INCLUDES_MODELCREDIT_HPP_
#define INCLUDES_MODELCREDIT_HPP_

#include "./imodelcredit.hpp"

namespace s21 {

class ModelCredit : public IModelCredit {
 public:
  ModelCredit();
  // ModelCredit(ModelCredit const &other) = delete;
  // ModelCredit &operator=(ModelCredit const &other) = delete;
  virtual ~ModelCredit();

  void Calculate() override;
  void set_sum(QString count) override;
  void set_time(QString count) override;
  void set_procent(QString count) override;
  void set_is_mount(bool is_mount) override;
  void set_different(bool is_diff) override;

  virtual QString MonthlyPayment() const override;
  virtual QString AccruedInterest() const override;
  virtual QString DebgAndInterest() const override;

 private:
  void ResetData();
  void CalculatorAnnuit();
  void CalculatorDifferent();
  void MyRound(long double *num);

 private:
  unsigned long long sum_credit_;
  unsigned time_credit_;
  double procents_credit_;

  bool is_mount_;
  bool is_different_;

  long double mount_;
  long double mount_last_;
  long double procents_;
  long double total_;
};

}  // namespace s21
#endif  // INCLUDES_MODELCREDIT_HPP_
