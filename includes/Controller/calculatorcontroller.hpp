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

  /**
   * @brief Calcualte str number. The first parameter if empty
   *        value is taken from the class if str != empty then
   *        the first argument is evaluated.
   *
   * @param str -> str number.
   * @param x   -> x coordinate.
   */
  void Calculate(QString const &str = "", QString const &x = "") override;

  void AddValue(QString const &str) override;

  /**
   * @brief Set brakcets.
   *
   * @param str        -> Bracket if is_start == true then then smart
   *                        insertion is enabled
   *                        (it doesn't matter which bracket).
   * @param is_smart   -> Smart input.
   * @param is_checked -> Auxiliary variable for manual input.
   */
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
