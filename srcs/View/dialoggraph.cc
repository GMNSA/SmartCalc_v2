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

// -----------------------------------------------------------------------------

DialogGraph::DialogGraph(
    ns_simple_controller::ICalculatorController *calculator_controller,
    QWidget *parent)
    : QDialog(parent),
      ui(new Ui::DialogGraph),
      m_width(0),
      m_height(0),
      m_xMin(-3),
      m_xMax(20),
      m_x(0),
      m_scale(0),
      isError_(0),
      m_num_of_grid(10),
      m_scene(nullptr),
      calculator_(calculator_controller) {
  ui->setupUi(this);

  createDialog();

  connection_configurations();
}

// ----------------------------------------------------------------------------

DialogGraph::~DialogGraph() {
  if (m_scene) delete m_scene;
  if (ui) delete ui;
}

// ----------------------------------------------------------------------------

void DialogGraph::resetData() {
  createDialog();

  m_scale = 0;
  isError_ = 0;
  m_res = 0;
  m_width = 0;
  m_height = 0;
}

// ----------------------------------------------------------------------------

void DialogGraph::on_buttonCloseClicked() {
  this->hide();
  qDebug("HIDE");
}

// ----------------------------------------------------------------------------

void DialogGraph::setHeigth(double heigth) { m_height = heigth; }

// ----------------------------------------------------------------------------

void DialogGraph::setWidth(double width) { m_width = width; }

// ----------------------------------------------------------------------------

void DialogGraph::setStrNum(const QString &strNum) {
  m_strNum = strNum;
  qDebug() << "str num: " << m_strNum;
}

// ----------------------------------------------------------------------------

double DialogGraph::x() const { return m_x; }

// ----------------------------------------------------------------------------

void DialogGraph::setX(double x) { m_x = x; }

// ----------------------------------------------------------------------------

void DialogGraph::openGraphic() {
  resetData();
  dataConversion();

  if (isError_ || m_xMax <= m_xMin) {
  } else {
    m_scene->clear();
    QPen graphLine(Qt::darkGreen);
    graphLine.setWidthF(0.5);
    drawField(m_scene);
    double x = m_xMin;
    double moveX = 0.02;
    double y = calclulateXCustom(m_strNum, x, m_scale) - m_res;
    double y1 = 0;

    for (int i = -m_width * 50; i <= m_width * 50; ++i, x += moveX) {
      y1 = calclulateXCustom(m_strNum, x + moveX, m_scale) - m_res;
      if (y >= -m_height && y <= m_height && y1 >= -m_height &&
          y1 <= m_height) {
        if (std::isnan(y1) || y1 == 0) continue;
        m_scene->addLine(x, -y, x + moveX, -y1, graphLine);
      }
      y = y1;
    }

    ui->graphicsView->setScene(m_scene);
  }
}

// ----------------------------------------------------------------------------

void DialogGraph::dataConversion() {
  setWidth((ui->graphicsView->width() - OFFSET_WIDTH) / 2.0);
  setHeigth((ui->graphicsView->height() - OFFSET_HEIGHT) / 2.0);
  QString r = QString("((%1) + (%2)) / 2.0").arg(m_xMax).arg(m_xMin);
  m_res = calclulateX(m_strNum, r).toDouble();
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

    r = QString("((%1) + (%2)) / 2 + %3").arg(m_xMax).arg(m_xMin).arg(count);
    res0 = calclulateX(m_strNum, r).toDouble();
    r = QString("((%1) + (%2)) / 2 - %3").arg(m_xMax).arg(m_xMin).arg(count);
    res1 = calclulateX(m_strNum, r).toDouble();
    if (!std::isnormal((res0) && std::isnormal(res1))) res0 = 0;
    if (!std::isnormal(res1) && std::isnormal(res0)) res1 = 0;
    m_res = (res0 + res1) / 2;
  }

  if (!std::isfinite(m_res)) m_res = 0;
  if (!m_xMin && !m_xMax) {
    m_xMax += fabs(m_res) + 2 * M_PI + count;
    m_xMin -= fabs(m_res) + 2 * M_PI + count;
    m_res = 0;
  } else if (fabs(m_res) < m_xMax / 2) {
    m_res = 0;
  }

  m_scale = 2 * m_width / (m_xMax - m_xMin);
  m_xMax *= m_scale;
  m_xMin *= m_scale;
  m_res *= m_scale;
}

// ----------------------------------------------------------------------------

void DialogGraph::drawField(QGraphicsScene *scene_) {
  QPen gridLine(Qt::black);
  QPen axisLine(Qt::black);
  axisLine.setWidthF(1.5);
  scene_->addLine(m_xMin, m_height, m_xMax, m_height, axisLine);
  scene_->addLine(m_xMin, -m_height, m_xMin, m_height, axisLine);
  QString gridTxt;
  double gridMove = 2 * m_width / m_num_of_grid;
  double gridP = m_xMin + gridMove;
  gridLine.setWidthF(0.2);

  for (unsigned count = 1; count < m_num_of_grid; ++count, gridP += gridMove) {
    gridTxt = QString::number(gridP / m_scale, 'f', 2);
    QGraphicsTextItem *p_xp =
        new QGraphicsTextItem(gridTxt, qobject_cast<QGraphicsItem *>(m_scene));
    p_xp->setPos(gridP, m_height);
    scene_->addLine(gridP, -m_height, gridP, m_height, gridLine);
    scene_->addLine(gridP, m_height - 10, gridP, m_height, axisLine);
    scene_->addItem((QGraphicsItem *)(p_xp));
  }

  gridMove = 2 * m_height / m_num_of_grid;
  gridP = m_height - gridMove;

  gridLine.setWidthF(0.2);
  for (int count = m_num_of_grid; count > 1; --count, gridP -= gridMove) {
    gridTxt = QString::number((-gridP + m_res) / m_scale, 'f', 2);
    QGraphicsTextItem *p_y =
        new QGraphicsTextItem(gridTxt, qobject_cast<QGraphicsItem *>(m_scene));

    p_y->setPos(m_xMin, gridP);
    scene_->addLine(m_xMin, gridP, m_xMax, gridP, gridLine);
    scene_->addLine(m_xMin, gridP, m_xMin + 10, gridP, axisLine);
    scene_->addItem(p_y);
  }
}

// ----------------------------------------------------------------------------

double DialogGraph::xMax() const { return m_xMax; }

// ----------------------------------------------------------------------------

void DialogGraph::setXMax(double xMax) { m_xMax = xMax; }

// ----------------------------------------------------------------------------

double DialogGraph::xMin() const { return m_xMin; }

// ----------------------------------------------------------------------------

void DialogGraph::setXMin(double xMin) { m_xMin = xMin; }

// ----------------------------------------------------------------------------

void DialogGraph::connection_configurations() {
  connect(ui->btn_close, &QPushButton::clicked, this,
          &DialogGraph::on_buttonCloseClicked);
}

// ----------------------------------------------------------------------------

QString DialogGraph::calclulateX(QString str_, QString x_) {
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

double DialogGraph::calclulateXCustom(QString str_, double x_, double scale_) {
  QString res;
  double x = 0;
  double xRes = x_ / scale_;
  str_ = str_.replace("x", "( " + QString::number(xRes) + " )");
  calculator_->Calculate(str_);
  res = calculator_->GetData();

  if (res == "error" || res == "na" || res == "-na") {
    isError_ = 1;
    x = INF;
  } else {
    x = res.toDouble() * scale_;
  }
  return (x);
}

// ----------------------------------------------------------------------------

void DialogGraph::createDialog() {
  if (m_scene != nullptr) {
    delete m_scene;
    m_scene = nullptr;
  }

  if (!(m_scene = new QGraphicsScene(ui->graphicsView))) this->close();
  m_scene->setParent(this);
}

}  // namespace s21
