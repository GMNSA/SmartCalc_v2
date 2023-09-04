#ifndef INCLUDES_CONTROLLER_CALCULATORCONTROLLER_HPP_
#define INCLUDES_CONTROLLER_CALCULATORCONTROLLER_HPP_

#include "../Model/imodel.hpp"
#include "../Model/modelcalculator.hpp"
#include "./icalculatorcontroller.hpp"

namespace ns_simple_controller {

class CalculatorController : public ICalculatorController {
 public:
  CalculatorController(ns_model::ModelCalculator *model);
  virtual ~CalculatorController();

  void Calculate(QString const &str) override;
  QString GetData() const override;
  void AddValue(QString const &str) override;
  void SetBrackets(QString const &str, bool const is_smart,
                   bool is_checked) override;
  void Reset() override;
  QString GetTextForDisplay() const override;

 private:
  ns_model::IModel *model_;
};

}  // namespace ns_simple_controller

#endif  // INCLUDES_CONTROLLER_CALCULATORCONTROLLER_HPP_
