#ifndef INCLUDES_CONTROLLER_ICALCULATORCONTROLLER_HPP_
#define INCLUDES_CONTROLLER_ICALCULATORCONTROLLER_HPP_

#include <QString>

class ICalculatorController {
 public:
  virtual ~ICalculatorController() = default;
  virtual void Calculate(QString const &str) = 0;
  virtual QString GetData() const = 0;
  virtual void AddValue(QString const &str) = 0;
  virtual void SetBrackets(QString const &str, bool const is_smart,
                           bool is_checked) = 0;
  virtual void Reset() = 0;
  virtual QString GetTextForDisplay() const = 0;

 protected:
};

#endif  // INCLUDES_CONTROLLER_ICALCULATORCONTROLLER_HPP_
