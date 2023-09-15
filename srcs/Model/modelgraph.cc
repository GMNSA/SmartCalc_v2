#include "../../includes/Model/modelgraph.hpp"

#include <QDebug>
#include <QGraphicsTextItem>

namespace s21 {

double const ModelGraph::kINF_ = 1.0 / 0.0;

// ----------------------------------------------------------------------------

ModelGraph::ModelGraph()
    : width_(0),
      height_(0),
      x_min_(-10),
      x_max_(10),
      x_(0),
      scale_(0),
      is_error_(false),
      num_of_grid_(10),
      scene_(nullptr),
      polish_notation_(new PolishNotation),
      offset_width_(18),
      offset_height_(26) {
  ResetData();
}

// ----------------------------------------------------------------------------

ModelGraph::~ModelGraph() {
  if (polish_notation_) {
    delete polish_notation_;
    polish_notation_ = nullptr;
  }
}

// ----------------------------------------------------------------------------

void ModelGraph::set_width(double const &width) {
  Q_UNUSED(width);
  width_ = (width - offset_width_) / 2.0;
}

// ----------------------------------------------------------------------------

void ModelGraph::set_height(double const &height) {
  height_ = (height - offset_height_) / 2.0;
}

// ----------------------------------------------------------------------------

void ModelGraph::set_x_min(double const &x_min) { x_min_ = x_min; }

// ----------------------------------------------------------------------------

void ModelGraph::set_x_max(double const &x_max) { x_max_ = x_max; }

// ----------------------------------------------------------------------------

void ModelGraph::set_x(double const &x) { x_ = x; }

// ----------------------------------------------------------------------------

double ModelGraph::get_x() const { return x_; }

// ----------------------------------------------------------------------------

void ModelGraph::set_str_number(const QString &str_num) { str_num_ = str_num; }

// ----------------------------------------------------------------------------

void ModelGraph::DataConversion() {
  QString r = QString("((%1) + (%2)) / 2.0").arg(x_max_).arg(x_min_);
  res_ = CalculateX(str_num_, r).toDouble();
  int count = 0;
  double res0 = 0;
  double res1 = 0;

  while (!std::isfinite(res_) && count < 1e8) {
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
    res_ = (res0 + res1) / 2;
  }

  if (!std::isfinite(res_)) res_ = 0;
  if (!x_min_ && !x_max_) {
    x_max_ += fabs(res_) + 2 * M_PI + count;
    x_min_ -= fabs(res_) + 2 * M_PI + count;
    res_ = 0;
  } else if (fabs(res_) < x_max_ / 2) {
    res_ = 0;
  }

  scale_ = 2 * width_ / (x_max_ - x_min_);
  x_max_ *= scale_;
  x_min_ *= scale_;
  res_ *= scale_;
}

// ----------------------------------------------------------------------------

void ModelGraph::DrawField(QGraphicsScene *scene_) {
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
  }

  grid_move = 2 * height_ / num_of_grid_;
  gridP = height_ - grid_move;

  grid_line.setWidthF(0.2);
  for (int count = num_of_grid_; count > 1; --count, gridP -= grid_move) {
    grid_txt = QString::number((-gridP + res_) / scale_, 'f', 2);
    QGraphicsTextItem *p_y =
        new QGraphicsTextItem(grid_txt, qobject_cast<QGraphicsItem *>(scene_));

    p_y->setPos(x_min_, gridP);
    scene_->addLine(x_min_, gridP, x_max_, gridP, grid_line);
    scene_->addLine(x_min_, gridP, x_min_ + 10, gridP, axis_line);
    scene_->addItem(p_y);
  }
}

// ----------------------------------------------------------------------------

void ModelGraph::DrawGraphic(QGraphicsScene *scene) {
  AttachScene(scene);
  DataConversion();

  if (!is_error_ && x_max_ > x_min_ && scene_) {
    scene_->clear();
    QPen graphLine(Qt::darkGreen);
    graphLine.setWidthF(0.5);
    DrawField(scene_);
    double x = x_min_;
    double moveX = 0.02;
    double y = CalculateXCustom(str_num_, x, scale_) - res_;
    double y1 = 0;

    double end_width = width_ * 50;
    for (int i = -width_ * 50; i <= end_width; ++i, x += moveX) {
      y1 = CalculateXCustom(str_num_, x + moveX, scale_) - res_;
      if (y >= -height_ && y <= height_ && y1 >= -height_ && y1 <= height_) {
        if (std::isnan(y1) || y1 == 0) continue;
        scene_->addLine(x, -y, x + moveX, -y1, graphLine);
      }
      y = y1;
    }
  }
  ResetData();
}

// ----------------------------------------------------------------------------

void ModelGraph::ResetData() {
  scale_ = 0;
  is_error_ = 0;
  res_ = 0;
  width_ = 0;
  height_ = 0;
}

// ----------------------------------------------------------------------------

QString ModelGraph::CalculateX(QString str_, QString x_) {
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

double ModelGraph::CalculateXCustom(QString str, double x_coord, double scale) {
  QString res;
  double x = 0;
  double xRes = x_coord / scale;
  str = str.replace("x", "( " + QString::number(xRes) + " )");
  res = Calculate(str);

  if (res == "error" || res == "na" || res == "-na") {
    is_error_ = 1;
    x = ModelGraph::kINF_;
  } else {
    x = res.toDouble() * scale;
  }

  return x;
}

// ----------------------------------------------------------------------------

QString ModelGraph::Calculate(QString const &num_str) {
  auto postfix = polish_notation_->StrToPostfix(num_str);
  auto res = polish_notation_->CalculateNotation(postfix);

  return res;
}

// ----------------------------------------------------------------------------

void ModelGraph::AttachScene(QGraphicsScene *scene) { scene_ = scene; }

}  // namespace s21
