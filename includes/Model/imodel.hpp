#ifndef INCLUDES_MODEL_IMODEL_HPP_
#define INCLUDES_MODEL_IMODEL_HPP_

#include <QGraphicsScene>
#include <QString>

namespace s21 {

class IModel {
 public:
  virtual ~IModel() = default;

  virtual QString get_result() const = 0;
  virtual QString get_result_graph() const = 0;
  virtual QString get_fix_text_display() const = 0;
  virtual QString get_text_repeat_display() const = 0;
  virtual bool get_is_graph() const = 0;

  virtual void Calculate(QString const &str = "", QString const &x = "") = 0;
  virtual void AddValue(QString const &str) = 0;
  virtual void SetBrackets(QString const &str, bool const is_smart,
                           bool is_checked) = 0;
  virtual void Reset() = 0;
  virtual void DelOne() = 0;
  virtual void ReplaceX(QString *str, QString const &x) = 0;
  virtual void ChangeSign() = 0;
};

}  // namespace s21

#endif  // INCLUDES_MODEL_IMODEL_HPP_
