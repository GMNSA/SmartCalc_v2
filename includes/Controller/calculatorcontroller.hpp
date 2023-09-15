#ifndef INCLUDES_CONTROLLER_CALCULATORCONTROLLER_HPP_
#define INCLUDES_CONTROLLER_CALCULATORCONTROLLER_HPP_

#include "../Model/imodel.hpp"
#include "./icalculatorcontroller.hpp"

namespace s21 {

class CalculatorController : public ICalculatorController {
 public:
  explicit CalculatorController(IModel *model);
  CalculatorController(CalculatorController const &other) = delete;
  CalculatorController &operator=(CalculatorController const &other) = delete;
  virtual ~CalculatorController();

  QString get_data() const override;
  QString get_data_graph() const override;
  bool get_is_graph() const override;
  QString get_text_display() const override;
  QString get_text_repeat_display() const override;

  void Calculate(QString const &str = "", QString const &x = "") override;
  void AddValue(QString const &str) override;
  void SetBrackets(QString const &str, bool const is_smart,
                   bool is_checked) override;
  void Reset() override;
  void DelOne() override;
  void ChangeSign() override;

 private:
  IModel *model_;
};

}  // namespace s21

#endif  // INCLUDES_CONTROLLER_CALCULATORCONTROLLER_HPP_
