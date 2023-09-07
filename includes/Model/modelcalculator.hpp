#ifndef INCLUDES_MODEL_MODELCALCULATOR_HPP_
#define INCLUDES_MODEL_MODELCALCULATOR_HPP_

#include <QHash>
#include <QStack>

#include "./imodel.hpp"
#include "./polishnotation.hpp"
#include "./validatetext.hpp"

namespace ns_model {

class ModelCalculator : public IModel {
 public:
  ModelCalculator();
  ModelCalculator(ModelCalculator const &other) = delete;
  ModelCalculator &operator=(ModelCalculator const &other) = delete;

  virtual ~ModelCalculator();

  // -- override --
  void Calculate(QString const &str = "", QString const &x = "") override;
  QString GetResult() const override;
  QString GetResultGraph() const override;
  void AddValue(QString const &str) override;
  void SetBrackets(QString const &str, bool const is_smart,
                   bool is_checked) override;
  void Reset() override;
  QString FixTextDisplay() const override;
  QString TextRepeatDisplay() const override;
  void DelOne() override;
  bool IsGraph() const override;
  void ReplaceX(QString *str, QString const &x) override;

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

};  // namespace ns_model

#endif  // INCLUDES_MODEL_MODELCALCULATOR_HPP_
