#ifndef INCLUDES_VIEW_DIALOGGRAPH_HPP_
#define INCLUDES_VIEW_DIALOGGRAPH_HPP_

#include <QDialog>
#include <QGraphicsScene>

#include "../Controller/igraphcontroller.hpp"

namespace Ui {
class DialogGraph;
}

namespace s21 {

class DialogGraph : public QDialog {
  Q_OBJECT

 public:
  explicit DialogGraph(IGraphController *graphic_controller,
                       QWidget *parent = nullptr);
  ~DialogGraph();

  void ResetData();

  double get_x_min() const;
  void set_x_min(double Xmin);

  double get_x_max() const;
  void set_x_max(double XMax);

  double x() const;
  void set_x(double x);

  void set_width(double width);
  void set_height(double heigth);

  void DrawGraphic(QString const &str_num);

 private:
  Ui::DialogGraph *ui;

 private slots:
  void on_buttonCloseClicked();

 private:
  double width_;
  double height_;
  double x_min_;
  double x_max_;
  double x_;
  QGraphicsScene *scene_;
  IGraphController *graph_;

 private:
  void ConnectionConfigurations();
  void CreateDialog();
};

}  // namespace s21

#endif  // INCLUDES_VIEW_DIALOGGRAPH_HPP_
