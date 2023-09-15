#ifndef INCLUDES_MODEL_IMODELCREDIT_HPP_
#define INCLUDES_MODEL_IMODELCREDIT_HPP_

#include <QString>

namespace s21 {

class IModelCredit {
 public:
  virtual ~IModelCredit() = default;

  virtual void Calculate() = 0;
  virtual void set_sum(QString const &count) = 0;
  virtual void set_time(QString const &count) = 0;
  virtual void set_procent(QString const &count) = 0;
  virtual void set_is_mount(bool const &is_mount) = 0;
  virtual void set_different(bool const &is_diff) = 0;

  virtual QString MonthlyPayment() const = 0;
  virtual QString AccruedInterest() const = 0;
  virtual QString DebgAndInterest() const = 0;
};

}  // namespace s21

#endif  // INCLUDES_MODEL_IMODELCREDIT_HPP_
