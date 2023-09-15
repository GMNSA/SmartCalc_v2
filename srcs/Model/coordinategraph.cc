#include "../../includes/Model/coordinategraph.hpp"

#include <QGraphicsTextItem>

namespace s21 {

double CoordinateGraph::inf_ = 1.0 / 0.0;

CoordinateGraph::CoordinateGraph() {}

CoordinateGraph::~CoordinateGraph() {
  if (scene_) delete scene_;
}

// ----------------------------------------------------------------------------

double CoordinateGraph::get_x_max() const { return x_max_; }

// ----------------------------------------------------------------------------

void CoordinateGraph::set_x_max(double const &x_max) { x_max_ = x_max; }

// ----------------------------------------------------------------------------

double CoordinateGraph::get_x() const { return x_; }

// ----------------------------------------------------------------------------

void CoordinateGraph::set_x(double const &x) { x_ = x; }

// ----------------------------------------------------------------------------

double CoordinateGraph::get_x_min() const { return x_min_; }

// ----------------------------------------------------------------------------

void CoordinateGraph::set_x_min(double const &x_min) { x_min_ = x_min; }

// ----------------------------------------------------------------------------

void CoordinateGraph::DataConversion() {
  // SetWidth((ui->graphicsView->width() - offset_width_) / 2.0);
  // SetHeight((ui->graphicsView->height() - offset_height_) / 2.0);

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

void CoordinateGraph::DrawField(QGraphicsScene *scene_) {
  QPen grid_line(Qt::black);
  QPen axis_line(Qt::black);
  axis_line.setWidthF(1.5);
  scene_->addLine(x_min_, height_, x_max_, height_, axis_line);
  scene_->addLine(x_min_, -height_, x_min_, height_, axis_line);
  QString grid_txt;
  double grid_move = 2 * width_ / num_of_grid_;
  double gridP = x_min_ + grid_move;
  grid_line.setWidthF(0.2);

  for (unsigned count = 1; count < num_of_grid_; ++count, gridP += grid_move) {
    grid_txt = QString::number(gridP / scale_, 'f', 2);
    QGraphicsTextItem *p_xp =
        new QGraphicsTextItem(grid_txt, qobject_cast<QGraphicsItem *>(scene_));
    p_xp->setPos(gridP, height_);
    scene_->addLine(gridP, -height_, gridP, height_, grid_line);
    scene_->addLine(gridP, height_ - 10, gridP, height_, axis_line);
    scene_->addItem(qobject_cast<QGraphicsItem *>(p_xp));
    // (QGraphicsItem *)
  }

  grid_move = 2 * height_ / num_of_grid_;
  gridP = height_ - grid_move;

  grid_line.setWidthF(0.2);
  for (int count = num_of_grid_; count > 1; --count, gridP -= grid_move) {
    grid_txt = QString::number((-gridP + m_res) / scale_, 'f', 2);
    QGraphicsTextItem *p_y =
        new QGraphicsTextItem(grid_txt, qobject_cast<QGraphicsItem *>(scene_));

    p_y->setPos(x_min_, gridP);
    scene_->addLine(x_min_, gridP, x_max_, gridP, grid_line);
    scene_->addLine(x_min_, gridP, x_min_ + 10, gridP, axis_line);
    scene_->addItem(p_y);
  }
}

// ----------------------------------------------------------------------------

void CoordinateGraph::SetStrNum(const QString &str_num) { str_num_ = str_num; }

// ----------------------------------------------------------------------------

void CoordinateGraph::DrawGraphic(QGraphicsScene *scene) {
  AttachScene(scene);
  ResetData();
  DataConversion();

  if (is_error_ || x_max_ <= x_min_) {
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

    // ui->graphicsView->setScene(scene_);
  }
}

// ----------------------------------------------------------------------------

void CoordinateGraph::ResetData() {}
QString CoordinateGraph::CalculateX(QString str_, QString x_) {
  QString res;

  if (is_error_) {
    res = "error";
  } else {
    str_ = str_.replace("x", "( " + x_ + ")");
    res = Calculate(str_);
    if (res == "na") is_error_ = 1;
  }

  return (res);
}

// ----------------------------------------------------------------------------

double CoordinateGraph::CalculateXCustom(QString str, double x_coord,
                                         double scale) {
  QString res;
  double x = 0;
  double xRes = x_coord / scale;
  str = str.replace("x", "( " + QString::number(xRes) + " )");
  res = Calculate(str);

  if (res == "error" || res == "na" || res == "-na") {
    is_error_ = 1;
    x = CoordinateGraph::inf_;
  } else {
    x = res.toDouble() * scale;
  }

  return x;
}

// ----------------------------------------------------------------------------

QString CoordinateGraph::Calculate(QString const &num_str) {
  auto postfix = polish_notation_->StrToPostfix(num_str);
  auto res = polish_notation_->CalculateNotation(postfix);

  return res;
}

// ----------------------------------------------------------------------------

void CoordinateGraph::AttachScene(QGraphicsScene *scene) {
  if (scene_ != nullptr) {
    delete scene_;
    scene_ = scene;
  }
}

}  // namespace s21
