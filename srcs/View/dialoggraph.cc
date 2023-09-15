#include "../../includes/View/dialoggraph.hpp"

#include <QGraphicsTextItem>
#include <cmath>

#include "./ui_dialoggraph.h"

namespace s21 {

// -----------------------------------------------------------------------------

DialogGraph::DialogGraph(IGraphController *graphic_controller, QWidget *parent)
    : QDialog(parent),
      ui(new Ui::DialogGraph),
      width_(0),
      height_(0),
      x_min_(-10),
      x_max_(10),
      x_(0),
      scene_(nullptr),
      graph_(graphic_controller) {
  ui->setupUi(this);

  CreateDialog();

  ConnectionConfigurations();
}

// ----------------------------------------------------------------------------

DialogGraph::~DialogGraph() {
  if (scene_) delete scene_;
  if (graph_) delete graph_;
  if (ui) delete ui;
}

// ----------------------------------------------------------------------------

void DialogGraph::ResetData() {
  CreateDialog();
  width_ = 0;
  height_ = 0;
}

// ----------------------------------------------------------------------------

void DialogGraph::on_buttonCloseClicked() { this->hide(); }

// ----------------------------------------------------------------------------

void DialogGraph::set_height(double heigth) { height_ = heigth; }

// ----------------------------------------------------------------------------

void DialogGraph::set_width(double width) { width_ = width; }

// ----------------------------------------------------------------------------

double DialogGraph::x() const { return x_; }

// ----------------------------------------------------------------------------

void DialogGraph::set_x(double x) { x_ = x; }

// ----------------------------------------------------------------------------

void DialogGraph::DrawGraphic(QString const &str_num) {
  if (graph_ && scene_) {
    graph_->set_x_range(x_min_, x_max_, x_);
    graph_->set_size_graph(ui->graphicsView->width(),
                           ui->graphicsView->height());
    graph_->DrawGraphic(str_num, scene_);
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

void DialogGraph::CreateDialog() {
  if (scene_ != nullptr) {
    delete scene_;
    scene_ = nullptr;
  }

  if (!(scene_ = new QGraphicsScene(ui->graphicsView))) this->close();
  scene_->setParent(this);
  ui->graphicsView->setScene(scene_);
}

}  // namespace s21
