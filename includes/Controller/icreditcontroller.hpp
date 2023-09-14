#ifndef INCLUDES_CONTROLLER_ICREDITCONTROLLER_HPP_
#define INCLUDES_CONTROLLER_ICREDITCONTROLLER_HPP_

#include <QString>

namespace s21 {

class ICreditController {
 public:
  virtual ~ICreditController() = default;

  virtual void Calculate() = 0;
  virtual void set_sum(QString count) = 0;
  virtual void set_time(QString count) = 0;
  virtual void set_procent(QString count) = 0;
  virtual void set_is_mount(bool is_mount) = 0;
  virtual void set_different(bool is_diff) = 0;

  virtual QString MonthlyPayment() const = 0;
  virtual QString AccruedInterest() const = 0;
  virtual QString DebgAndInterest() const = 0;
};

}  // namespace s21

#endif  // INCLUDES_CONTROLLER_ICREDITCONTROLLER_HPP_
