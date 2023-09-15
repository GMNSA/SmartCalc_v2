#ifndef INCLUDES_MODEL_COORDINATEGRAPH_HPP_
#define INCLUDES_MODEL_COORDINATEGRAPH_HPP_

#include <QGraphicsScene>
#include <QString>

#include "./polishnotation.hpp"

namespace s21 {

class CoordinateGraph {
 public:
  CoordinateGraph();
  virtual ~CoordinateGraph();

  void set_x_min(double const &x_min);
  void set_x_max(double const &x_max);
  void set_x(double const &x);
  double get_x_min() const;
  double get_x_max() const;
  double get_x() const;

  void DrawGraphic(QGraphicsScene *scene);
  void SetStrNum(const QString &str_num);

 private:
  void ResetData();
  void DataConversion();
  void DrawField(QGraphicsScene *scene_);
  QString CalculateX(QString str_, QString x_);
  double CalculateXCustom(QString str_, double x_, double scale_);
  QString Calculate(QString const &num_str);

  void AttachScene(QGraphicsScene *scene = nullptr);

 private:
  QString str_num_;
  double width_;
  double height_;
  double x_min_;
  double x_max_;
  double x_;
  double scale_;
  bool is_error_;
  double m_res;
  unsigned num_of_grid_;
  QGraphicsScene *scene_;
  // ICalculatorController *calculator_;
  PolishNotation *polish_notation_;
  int offset_width_;
  int offset_height_;
  static double inf_;
};

}  // namespace s21

#endif  // INCLUDES_MODEL_COORDINATEGRAPH_HPP_
