#include "../../includes/View/dialoggraph.hpp"

#include <QGraphicsTextItem>
#include <cmath>

#include "./ui_dialoggraph.h"

namespace s21 {

// #define NUM_OF_GRID 12
// #define GRID_ACCURACY_F "%.2f"
// #define GRID_ACCURACY_E "%.1e"
//
#define OFFSET_WIDTH 18
#define OFFSET_HEIGHT 26
//
//
// #include <QGraphicsTextItem>
// #include <QTransform>
#define INF 1.0 / 0.0
// #include <QLabel>
// #include <QPainter>
//
// int equalDouble(double a_, double b_) { return (fabs(a_ - b_) < 1e-7); }
//

double DialogGraph::inf_ = 1.0 / 0.0;

// -----------------------------------------------------------------------------

DialogGraph::DialogGraph(
    ns_simple_controller::ICalculatorController *calculator_controller,
    QWidget *parent)
    : QDialog(parent),
      ui(new Ui::DialogGraph),
      width_(0),
      height_(0),
      x_min_(-3),
      x_max_(20),
      m_x(0),
      scale_(0),
      isError_(0),
      num_of_grid_(10),
      scene_(nullptr),
      calculator_(calculator_controller) {
  ui->setupUi(this);

  CreateDialog();

  ConnectionConfigurations();
}

// ----------------------------------------------------------------------------

DialogGraph::~DialogGraph() {
  if (scene_) delete scene_;
  if (ui) delete ui;
}

// ----------------------------------------------------------------------------

void DialogGraph::ResetData() {
  CreateDialog();

  scale_ = 0;
  isError_ = 0;
  m_res = 0;
  width_ = 0;
  height_ = 0;
}

// ----------------------------------------------------------------------------

void DialogGraph::on_buttonCloseClicked() {
  this->hide();
  qDebug("HIDE");
}

// ----------------------------------------------------------------------------

void DialogGraph::SetHeight(double heigth) { height_ = heigth; }

// ----------------------------------------------------------------------------

void DialogGraph::SetWidth(double width) { width_ = width; }

// ----------------------------------------------------------------------------

void DialogGraph::SetStrNum(const QString &strNum) {
  str_num_ = strNum;
  qDebug() << "str num: " << str_num_;
}

// ----------------------------------------------------------------------------

double DialogGraph::x() const { return m_x; }

// ----------------------------------------------------------------------------

void DialogGraph::set_x(double x) { m_x = x; }

// ----------------------------------------------------------------------------

void DialogGraph::OpenGraphic() {
  ResetData();
  DataConversion();

  if (isError_ || x_max_ <= x_min_) {
  } else {
    scene_->clear();
    QPen graphLine(Qt::darkGreen);
    graphLine.setWidthF(0.5);
    DrawField(scene_);
    double x = x_min_;
    double moveX = 0.02;
    double y = CalculateXCustom(str_num_, x, scale_) - m_res;
    double y1 = 0;

    for (int i = -width_ * 50; i <= width_ * 50; ++i, x += moveX) {
      y1 = CalculateXCustom(str_num_, x + moveX, scale_) - m_res;
      if (y >= -height_ && y <= height_ && y1 >= -height_ && y1 <= height_) {
        if (std::isnan(y1) || y1 == 0) continue;
        scene_->addLine(x, -y, x + moveX, -y1, graphLine);
      }
      y = y1;
    }

    ui->graphicsView->setScene(scene_);
  }
}

// ----------------------------------------------------------------------------

void DialogGraph::DataConversion() {
  SetWidth((ui->graphicsView->width() - OFFSET_WIDTH) / 2.0);
  SetHeight((ui->graphicsView->height() - OFFSET_HEIGHT) / 2.0);
  QString r = QString("((%1) + (%2)) / 2.0").arg(x_max_).arg(x_min_);
  m_res = CalculateX(str_num_, r).toDouble();
  int count = 0;
  double res0 = 0;
  double res1 = 0;

  while (!std::isfinite(m_res) && count < 1e8) {
    if (count < 1e2)
      ++count;
    else if (count < 1e6)
      count *= 5;
    else
      count *= 10;

    r = QString("((%1) + (%2)) / 2 + %3").arg(x_max_).arg(x_min_).arg(count);
    res0 = CalculateX(str_num_, r).toDouble();
    r = QString("((%1) + (%2)) / 2 - %3").arg(x_max_).arg(x_min_).arg(count);
    res1 = CalculateX(str_num_, r).toDouble();
    if (!std::isnormal((res0) && std::isnormal(res1))) res0 = 0;
    if (!std::isnormal(res1) && std::isnormal(res0)) res1 = 0;
    m_res = (res0 + res1) / 2;
  }

  if (!std::isfinite(m_res)) m_res = 0;
  if (!x_min_ && !x_max_) {
    x_max_ += fabs(m_res) + 2 * M_PI + count;
    x_min_ -= fabs(m_res) + 2 * M_PI + count;
    m_res = 0;
  } else if (fabs(m_res) < x_max_ / 2) {
    m_res = 0;
  }

  scale_ = 2 * width_ / (x_max_ - x_min_);
  x_max_ *= scale_;
  x_min_ *= scale_;
  m_res *= scale_;
}

// ----------------------------------------------------------------------------

void DialogGraph::DrawField(QGraphicsScene *scene_) {
  QPen gridLine(Qt::black);
  QPen axisLine(Qt::black);
  axisLine.setWidthF(1.5);
  scene_->addLine(x_min_, height_, x_max_, height_, axisLine);
  scene_->addLine(x_min_, -height_, x_min_, height_, axisLine);
  QString gridTxt;
  double gridMove = 2 * width_ / num_of_grid_;
  double gridP = x_min_ + gridMove;
  gridLine.setWidthF(0.2);

  for (unsigned count = 1; count < num_of_grid_; ++count, gridP += gridMove) {
    gridTxt = QString::number(gridP / scale_, 'f', 2);
    QGraphicsTextItem *p_xp =
        new QGraphicsTextItem(gridTxt, qobject_cast<QGraphicsItem *>(scene_));
    p_xp->setPos(gridP, height_);
    scene_->addLine(gridP, -height_, gridP, height_, gridLine);
    scene_->addLine(gridP, height_ - 10, gridP, height_, axisLine);
    scene_->addItem((QGraphicsItem *)(p_xp));
  }

  gridMove = 2 * height_ / num_of_grid_;
  gridP = height_ - gridMove;

  gridLine.setWidthF(0.2);
  for (int count = num_of_grid_; count > 1; --count, gridP -= gridMove) {
    gridTxt = QString::number((-gridP + m_res) / scale_, 'f', 2);
    QGraphicsTextItem *p_y =
        new QGraphicsTextItem(gridTxt, qobject_cast<QGraphicsItem *>(scene_));

    p_y->setPos(x_min_, gridP);
    scene_->addLine(x_min_, gridP, x_max_, gridP, gridLine);
    scene_->addLine(x_min_, gridP, x_min_ + 10, gridP, axisLine);
    scene_->addItem(p_y);
  }
}

// ----------------------------------------------------------------------------

double DialogGraph::get_x_max() const { return x_max_; }

// ----------------------------------------------------------------------------

void DialogGraph::set_x_max(double XMax) { x_max_ = XMax; }

// ----------------------------------------------------------------------------

double DialogGraph::get_x_min() const { return x_min_; }

// ----------------------------------------------------------------------------

void DialogGraph::set_x_min(double Xmin) { x_min_ = Xmin; }

// ----------------------------------------------------------------------------

void DialogGraph::ConnectionConfigurations() {
  connect(ui->btn_close, &QPushButton::clicked, this,
          &DialogGraph::on_buttonCloseClicked);
}

// ----------------------------------------------------------------------------

QString DialogGraph::CalculateX(QString str_, QString x_) {
  QString res;

  if (isError_) {
    res = "error";
  } else {
    str_ = str_.replace("x", "( " + x_ + ")");
    calculator_->Calculate(str_);
    res = calculator_->GetData();

    if (res == "na") isError_ = 1;
  }

  return (res);
}

// ----------------------------------------------------------------------------

double DialogGraph::CalculateXCustom(QString str_, double x_, double scale_) {
  QString res;
  double x = 0;
  double xRes = x_ / scale_;
  str_ = str_.replace("x", "( " + QString::number(xRes) + " )");
  calculator_->Calculate(str_);
  res = calculator_->GetData();

  if (res == "error" || res == "na" || res == "-na") {
    isError_ = 1;
    x = DialogGraph::inf_;
  } else {
    x = res.toDouble() * scale_;
  }
  return (x);
}

// ----------------------------------------------------------------------------

void DialogGraph::CreateDialog() {
  if (scene_ != nullptr) {
    delete scene_;
    scene_ = nullptr;
  }

  if (!(scene_ = new QGraphicsScene(ui->graphicsView))) this->close();
  scene_->setParent(this);
}

}  // namespace s21
