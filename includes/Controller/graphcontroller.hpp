#ifndef INCLUDES_CONTROLLER_GRAPHCONTROLLER_HPP_
#define INCLUDES_CONTROLLER_GRAPHCONTROLLER_HPP_

#include "../Model/imodelgraph.hpp"
#include "./igraphcontroller.hpp"

namespace s21 {

class GraphController : public IGraphController {
 public:
  explicit GraphController(IModelGraph *model);
  virtual ~GraphController();

  void set_size_graph(double const &width, double const &height) override;
  void set_x_range(double const &x_min = -10, double const &x_max = 10,
                   double const &x = 0) override;
  double get_x() const override;
  void DrawGraphic(QString const &str_num, QGraphicsScene *scene) override;

 private:
  IModelGraph *model_;
};

}  // namespace s21

#endif  // INCLUDES_CONTROLLER_GRAPHCONTROLLER_HPP_
