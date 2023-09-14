#ifndef INCLUDES_VIEW_DIALOGGRAPH_HPP_
#define INCLUDES_VIEW_DIALOGGRAPH_HPP_

#include <QDialog>
#include <QGraphicsScene>

#include "../Controller/icalculatorcontroller.hpp"

#define X_MIN -10
#define X_MAX 10

namespace Ui {
class DialogGraph;
}

namespace s21 {

class DialogGraph : public QDialog {
  Q_OBJECT

 public:
  explicit DialogGraph(ICalculatorController *calculator_controller,
                       QWidget *parent = nullptr);
  ~DialogGraph();

  void ResetData();

  double get_x_min() const;
  void set_x_min(double Xmin);

  double get_x_max() const;
  void set_x_max(double XMax);

  double x() const;
  void set_x(double x);

  void OpenGraphic();

  void DataConversion();
  void DrawField(QGraphicsScene *scene_);

  void SetStrNum(const QString &strNum);

  void SetWidth(double width);
  void SetHeight(double heigth);

 private:
  Ui::DialogGraph *ui;

 private slots:
  void on_buttonCloseClicked();

 private:
  QString str_num_;
  double width_;
  double height_;
  double x_min_;
  double x_max_;
  double m_x;
  double scale_;
  bool isError_;
  double m_res;
  unsigned num_of_grid_;
  QGraphicsScene *scene_;
  ICalculatorController *calculator_;
  int offset_width_;
  int offset_height_;
  static double inf_;

#ifdef FOR_TEST

 public:
#else

 private:
#endif
  void ConnectionConfigurations();
  QString CalculateX(QString str_, QString x_);
  double CalculateXCustom(QString str_, double x_, double scale_);
  void DataCoordinates();
  void CreateDialog();
};

}  // namespace s21

#endif  // INCLUDES_VIEW_DIALOGGRAPH_HPP_
