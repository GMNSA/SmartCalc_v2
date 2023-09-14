#ifndef INCLUDES_MODEL_IMODEL_HPP_
#define INCLUDES_MODEL_IMODEL_HPP_

#include <QString>

namespace s21 {

class IModel {
 public:
  virtual ~IModel() = default;

  virtual void Calculate(QString const &str = "", QString const &x = "") = 0;
  virtual QString GetResult() const = 0;
  virtual QString GetResultGraph() const = 0;
  virtual void AddValue(QString const &str) = 0;
  virtual void SetBrackets(QString const &str, bool const is_smart,
                           bool is_checked) = 0;
  virtual void Reset() = 0;
  virtual QString FixTextDisplay() const = 0;
  virtual QString TextRepeatDisplay() const = 0;
  virtual void DelOne() = 0;

  virtual bool IsGraph() const = 0;
  virtual void ReplaceX(QString *str, QString const &x) = 0;
  virtual void ChangeSign() = 0;
};

}  // namespace s21

#endif  // INCLUDES_MODEL_IMODEL_HPP_
