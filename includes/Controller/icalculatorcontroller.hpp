#ifndef INCLUDES_CONTROLLER_ICALCULATORCONTROLLER_HPP_
#define INCLUDES_CONTROLLER_ICALCULATORCONTROLLER_HPP_

#include <QString>

namespace ns_simple_controller {

class ICalculatorController {
 public:
  virtual ~ICalculatorController() = default;
  virtual void Calculate(QString const &str = "", QString const &x = "") = 0;
  virtual QString GetData() const = 0;
  virtual QString GetDatatGraph() const = 0;
  virtual void AddValue(QString const &str) = 0;
  virtual void SetBrackets(QString const &str, bool const is_smart,
                           bool is_checked) = 0;
  virtual void Reset() = 0;
  virtual QString GetTextDisplay() const = 0;
  virtual QString GetTextRepeatDisplay() const = 0;
  virtual void DelOne() = 0;
  virtual bool IsGraph() const = 0;
  virtual void ChangeSign() = 0;

 protected:
};

}  // namespace ns_simple_controller

#endif  // INCLUDES_CONTROLLER_ICALCULATORCONTROLLER_HPP_
