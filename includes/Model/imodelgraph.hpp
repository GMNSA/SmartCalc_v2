#ifndef INCLUDES_MODEL_IMODELGRAPH_HPP_
#define INCLUDES_MODEL_IMODELGRAPH_HPP_

#include <QGraphicsScene>

namespace s21 {

class IModelGraph {
 public:
  virtual ~IModelGraph() {}

  virtual void set_width(double const &width) = 0;
  virtual void set_height(double const &height) = 0;
  virtual void set_x_min(double const &x_min) = 0;
  virtual void set_x_max(double const &x_max) = 0;
  virtual void set_x(double const &x) = 0;
  virtual double get_x() const = 0;
  virtual void set_str_number(const QString &strNum) = 0;

  virtual void DrawGraphic(QGraphicsScene *scene) = 0;
};

}  // namespace s21

#endif  // INCLUDES_MODEL_IMODELGRAPH_HPP_
