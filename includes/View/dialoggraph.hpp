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
  explicit DialogGraph(
      ns_simple_controller::ICalculatorController *calculator_controller,
      QWidget *parent = nullptr);
  ~DialogGraph();

  void resetData();

  double xMin() const;
  void setXMin(double xMin);

  double xMax() const;
  void setXMax(double xMax);

  double x() const;
  void setX(double x);

  void openGraphic();

  void dataConversion();
  void drawField(QGraphicsScene *scene_);

  void setStrNum(const QString &strNum);

  void setWidth(double width);
  void setHeigth(double heigth);

 private:
  Ui::DialogGraph *ui;

 private slots:
  void on_buttonCloseClicked();

 private:
  QString m_strNum;
  double m_width;
  double m_height;
  double m_xMin;
  double m_xMax;
  double m_x;
  double m_scale;
  bool isError_;
  double m_res;
  unsigned m_num_of_grid;

  QGraphicsScene *m_scene;
  ns_simple_controller::ICalculatorController *calculator_;

#ifdef FOR_TEST

 public:
#else

 private:
#endif
  void connection_configurations();

  QString calclulateX(QString str_, QString x_);
  double calclulateXCustom(QString str_, double x_, double scale_);

  void dataCoordinates();

  void createDialog();
};

}  // namespace s21

#endif  // INCLUDES_VIEW_DIALOGGRAPH_HPP_
