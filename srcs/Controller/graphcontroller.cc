#include "../../includes/Controller/graphcontroller.hpp"

namespace s21 {

GraphController::GraphController(IModelGraph *model) : model_(model) {}

// ----------------------------------------------------------------------------

GraphController::~GraphController() {
  if (model_) delete model_;
}

// ----------------------------------------------------------------------------

void GraphController::set_size_graph(double const &width,
                                     double const &height) {
  model_->set_width(width);
  model_->set_height(height);
}

// ----------------------------------------------------------------------------

void GraphController::set_x_range(double const &x_min, double const &x_max,
                                  double const &x) {
  model_->set_x_min(x_min);
  model_->set_x_max(x_max);
  model_->set_x(x);
}

// ----------------------------------------------------------------------------

double GraphController::get_x() const { return model_->get_x(); }

// ----------------------------------------------------------------------------

void GraphController::DrawGraphic(QString const &str_num,
                                  QGraphicsScene *scene) {
  model_->set_str_number(str_num);
  model_->DrawGraphic(scene);
}

}  // namespace s21
