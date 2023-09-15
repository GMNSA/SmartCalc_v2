#ifndef INCLUDES_CONTROLLER_IGRAPHCONTROLLER_HPP_
#define INCLUDES_CONTROLLER_IGRAPHCONTROLLER_HPP_

#include <QGraphicsScene>

namespace s21 {

class IGraphController {
 public:
  virtual ~IGraphController() {}

  virtual void set_size_graph(double const &width, double const &height) = 0;
  virtual void set_x_range(double const &x_min = -10, double const &x_max = 10,
                           double const &x = 0) = 0;
  virtual double get_x() const = 0;
  virtual void DrawGraphic(QString const &str_num, QGraphicsScene *scene) = 0;
};

}  // namespace s21

#endif  // INCLUDES_CONTROLLER_IGRAPHCONTROLLER_HPP_
