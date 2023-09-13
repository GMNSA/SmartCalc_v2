#ifndef INCLUDES_CONTROLLER_CREDITCONTROLLER_HPP_
#define INCLUDES_CONTROLLER_CREDITCONTROLLER_HPP_

#include "../Model/imodelcredit.hpp"
#include "./icreditcontroller.hpp"

namespace s21 {

class CreditController : public ICreditController {
 public:
  CreditController(IModelCredit *model_credit = nullptr);
  CreditController(CreditController const &other);
  virtual ~CreditController();

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
  IModelCredit *model_credit_;
};

}  // namespace s21

#endif  // INCLUDES_CONTROLLER_CREDITCONTROLLER_HPP_
