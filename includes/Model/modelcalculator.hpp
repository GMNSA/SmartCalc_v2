#ifndef INCLUDES_MODEL_MODELCALCULATOR_HPP_
#define INCLUDES_MODEL_MODELCALCULATOR_HPP_

#include <QHash>
#include <QStack>

#include "./imodel.hpp"
#include "./polishnotation.hpp"
#include "./validatetext.hpp"

namespace s21 {

class ModelCalculator : public IModel {
 public:
  ModelCalculator();
  ModelCalculator(ModelCalculator const &other) = delete;
  ModelCalculator &operator=(ModelCalculator const &other) = delete;

  virtual ~ModelCalculator();

  // -- override --
  // void set_x_min(double const &x_min);
  // void set_x_max(double const &x_max);
  // void set_x(double const &x);
  // double get_x() const;
  // void set_str_num_x(QString const &str);

  // void DrawGraphic(QGraphicsScene *scene);

  // // -- -- -- --

  QString get_result() const override;
  QString get_result_graph() const override;         // ??
  QString get_fix_text_display() const override;     // !!!
  QString get_text_repeat_display() const override;  // OK
  bool get_is_graph() const override;                // OK

  void Calculate(QString const &str = "", QString const &x = "") override;
  void AddValue(QString const &str) override;
  void SetBrackets(QString const &str, bool const is_smart,
                   bool is_checked) override;
  void Reset() override;
  void DelOne() override;
  void ReplaceX(QString *str, QString const &x) override;
  void ChangeSign() override;

 private:
  void RemoveBrackets(QString *str);
  void AddBrackets(QString *str);
  void AddMinux(QString *str);
  void RemoveMinux(QString *str);

 private:
  QString display_text_;
  QString repeat_text_;
  QString calculated_text_;
  bool is_graph_;
  QString graphic_text_;
  PolishNotation *polish_notation_;
  ValidateText *validator_text_;
};

// ----------------------------------------------------------------------------

};  // namespace s21

#endif  // INCLUDES_MODEL_MODELCALCULATOR_HPP_
