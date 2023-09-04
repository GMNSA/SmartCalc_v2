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
  QString Calculate(QString const &str) override;
  void AddValue(QString const &str) override;
  void SetBrackets(QString const &str, bool const is_smart,
                   bool is_checked) override;
  void Reset() override;

 private:
  QString raw_text_;
  QString ready_text_;
  PolishNotation *polish_notation_;
  ValidateText *validator_text_;
};

// ----------------------------------------------------------------------------

};  // namespace ns_model

#endif  // INCLUDES_MODEL_MODELCALCULATOR_HPP_
