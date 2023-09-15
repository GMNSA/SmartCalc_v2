#ifndef INCLUDES_MODEL_MODELGRAPH_HPP_
#define INCLUDES_MODEL_MODELGRAPH_HPP_

#include "../../includes/Model/imodelgraph.hpp"
#include "./polishnotation.hpp"

namespace s21 {

class ModelGraph : public IModelGraph {
 public:
  ModelGraph();
  ModelGraph(ModelGraph const &other) = delete;
  ModelGraph &operator=(ModelGraph const &other) = delete;

  virtual ~ModelGraph();

  void set_width(double const &width) override;
  void set_height(double const &height) override;
  void set_x_min(double const &x_min) override;
  void set_x_max(double const &x_max) override;
  void set_x(double const &x) override;
  double get_x() const override;
  void set_str_number(const QString &str_num) override;

  void DrawGraphic(QGraphicsScene *scene) override;

 private:
  static const double kINF_;

  QString str_num_;
  double width_;
  double height_;
  double x_min_;
  double x_max_;
  double x_;
  double scale_;
  bool is_error_;
  double res_;
  unsigned num_of_grid_;
  QGraphicsScene *scene_;
  PolishNotation *polish_notation_;
  int offset_width_;
  int offset_height_;

 private:
  void ResetData();
  void DataConversion();
  void DrawField(QGraphicsScene *scene_);
  QString CalculateX(QString str_, QString x_);
  double CalculateXCustom(QString str_, double x_, double scale_);
  QString Calculate(QString const &num_str);

  void AttachScene(QGraphicsScene *scene = nullptr);
};

}  // namespace s21

#endif  // INCLUDES_MODEL_MODELGRAPH_HPP_
