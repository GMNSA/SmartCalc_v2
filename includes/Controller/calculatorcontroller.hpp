#ifndef INCLUDES_CONTROLLER_CALCULATORCONTROLLER_HPP_
#define INCLUDES_CONTROLLER_CALCULATORCONTROLLER_HPP_

#include "../Model/imodel.hpp"
#include "./icalculatorcontroller.hpp"

namespace s21 {

class CalculatorController : public ICalculatorController {
 public:
  explicit CalculatorController(IModel *model);
  virtual ~CalculatorController();

  void Calculate(QString const &str = "", QString const &x = "") override;
  QString GetData() const override;
  QString GetDatatGraph() const override;
  void AddValue(QString const &str) override;
  void SetBrackets(QString const &str, bool const is_smart,
                   bool is_checked) override;
  void Reset() override;
  QString GetTextDisplay() const override;
  QString GetTextRepeatDisplay() const override;
  void DelOne() override;
  bool IsGraph() const override;
  void ChangeSign() override;

 private:
  IModel *model_;
};

}  // namespace s21

#endif  // INCLUDES_CONTROLLER_CALCULATORCONTROLLER_HPP_
