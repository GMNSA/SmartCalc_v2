#include "../../includes/View/calculator.hpp"

#include <QDialog>
#include <QRegularExpressionValidator>
#include <QtDebug>

#include "./ui_calculator.h"

// *******************************************

namespace s21 {

Calculator::Calculator(ns_simple_controller::ICalculatorController *controller,
                       QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Calculator),
      m_is_clear(1),
      display_text_(),
      calculator_(controller),
      m_graph(nullptr),
      m_credit(),
      min_x_(-10),
      max_x_(10) {
  ui->setupUi(this);
  ui->checkBox_smart->setCheckState(Qt::CheckState::Checked);
  ui->lineEdit_x_2->clear();
  ui->lineEdit_x_3->clear();

  if (!(m_graph = new DialogGraph(controller, this))) ui->menubar->close();

  settingsCredit();
  settingsGraph();

  connection_configurations();

  if (m_is_clear) display_text_ = "0";
}

// -------------------------------------------

Calculator::~Calculator() {
  if (m_graph) delete m_graph;
  if (ui) delete ui;
}

// -------------------------------------------

void Calculator::on_button0Clicked() {
  calculator_->AddValue("0");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_button1Clicked() {
  calculator_->AddValue("1");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_button2Clicked() {
  calculator_->AddValue("2");
  ResetDisplay(calculator_->GetTextDisplay());
}

void Calculator::on_button3Clicked() {
  calculator_->AddValue("3");
  ResetDisplay(calculator_->GetTextDisplay());
}

void Calculator::on_button4Clicked() {
  calculator_->AddValue("4");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_button5Clicked() {
  calculator_->AddValue("5");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_button6Clicked() {
  calculator_->AddValue("6");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_button7Clicked() {
  calculator_->AddValue("7");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_button8Clicked() {
  calculator_->AddValue("8");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_button9Clicked() {
  calculator_->AddValue("9");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_buttonDotClicked() {
  calculator_->AddValue(".");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_buttonXClicked() {
  calculator_->AddValue("x");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_buttonPClicked() {
  calculator_->AddValue("π");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_buttonCeClicked() {
  calculator_->Reset();
  ResetDisplay("0");
  ResetRepeatDisplay("");
}

// -------------------------------------------

void Calculator::on_buttonDelClicked() {
  calculator_->DelOne();
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_buttonCosClicked() {
  calculator_->AddValue("cos(");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_buttonSinClicked() {
  calculator_->AddValue("sin(");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_buttonTanClicked() {
  calculator_->AddValue("tan(");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_buttonAcosClicked() {
  calculator_->AddValue("acos(");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_buttonAsinClicked() {
  calculator_->AddValue("asin(");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_buttonAtanClicked() {
  calculator_->AddValue("atan(");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_buttonSqrtClicked() {
  calculator_->AddValue("sqrt(");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_buttonPowClicked() {
  calculator_->AddValue("^");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_buttonLnClicked() {
  calculator_->AddValue("ln(");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_buttonLogClicked() {
  calculator_->AddValue("log(");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_buttonChangeClicked() {
  calculator_->ChangeSign();
  ui->display->setText(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_buttonSumClicked() {
  calculator_->AddValue(" + ");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_buttonSubClicked() {
  calculator_->AddValue(" - ");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_buttonMulClicked() {
  calculator_->AddValue(" * ");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_buttonDivClicked() {
  calculator_->AddValue(" / ");
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_buttonModClicked() {
  calculator_->AddValue("%");
  ResetDisplay(calculator_->GetTextDisplay());
}

// ----------------------------------------------------------------------------

void Calculator::on_buttonBracketLeftClicked() {
  calculator_->SetBrackets("(", ui->checkBox_smart->checkState(),
                           ui->checkBox_smart->isChecked());
  ResetDisplay(calculator_->GetTextDisplay());
}

// ----------------------------------------------------------------------------

void Calculator::on_buttonBracketRightClicked() {
  calculator_->SetBrackets(")", ui->checkBox_smart->checkState(),
                           ui->checkBox_smart->isChecked());
  ResetDisplay(calculator_->GetTextDisplay());
}

// -------------------------------------------

void Calculator::on_buttonEqualClicked() {
  CalculateSimple();
  ResetDisplay(calculator_->GetData());
  ui->display_repeat->setText(calculator_->GetTextRepeatDisplay());

  if (calculator_->IsGraph()) openGraphic();
  qDebug() << "result text: " << calculator_->GetData();
}

// -------------------------------------------

void Calculator::on_buttonGraphClicked() { m_graph->show(); }

// -------------------------------------------

void Calculator::CalculateSimple() {
  calculator_->Calculate("", QString::number(m_graph->x()));
  ui->display->setText(calculator_->GetData());
}

// ----------------------------------------------------------------------------

void Calculator::on_buttonCalculationCredit() { calculateCredit(); }

// ----------------------------------------------------------------------------

void Calculator::formatText() {
  QString num = ui->lineEdit_sumCredit->text().replace(" ", "");
  QString str = QString("%L1").arg(num.toLongLong());
  str = str.replace(",", " ");

  ui->lineEdit_sumCredit->setText(str);
}

// -------------------------------------------

void Calculator::ResetDisplay(QString const &str) { ui->display->setText(str); }

// ----------------------------------------------------------------------------

void Calculator::ResetRepeatDisplay(QString const &str) {
  ui->display_repeat->setText(str);
}

// -------------------------------------------

void Calculator::openGraphic() {
  m_graph->setStrNum(calculator_->GetDatatGraph());
  checkXData();
  m_graph->show();
  m_graph->openGraphic();
}

// -------------------------------------------

void Calculator::checkXData() {
  m_graph->setX(ui->lineEdit_x->text().toDouble());

  if (!ui->lineEdit_x_2->text().isEmpty()) {
    m_graph->setXMin(ui->lineEdit_x_2->text().toDouble());
  } else {
    m_graph->setXMin(min_x_);
  }

  if (!ui->lineEdit_x_3->text().isEmpty()) {
    m_graph->setXMax(ui->lineEdit_x_3->text().toDouble());
  } else {
    m_graph->setXMax(max_x_);
  }
}

// -------------------------------------------

void Calculator::settingsCredit() {
  ui->rb_annuit->setToolTip(
      "Аннуительный платеж - вариант ежемесячного платежа по кредиту, когда "
      "размер"
      "ежемесячного платежа остается постоянный на всем периоде "
      "кредитования.");

  ui->rb_differ->setToolTip(
      "Дифференцированный платеж - вариант ежемесячного платежа по кредиту,"
      "когда размер ежемесячного платежа по погашению кредита постепенно "
      "уменьшается к концу периода "
      "кредитования");

  ui->lineEdit_sumCredit->setValidator(new QIntValidator(this));
  ui->lineEdit_timeCredit->setValidator(new QIntValidator(this));
  ui->lineEdit_procent->setValidator(new QDoubleValidator(this));
}

// -------------------------------------------

void Calculator::settingsGraph() {
  ui->lineEdit_x->setValidator(new QIntValidator(this));
  ui->lineEdit_x_2->setValidator(new QDoubleValidator(this));
  ui->lineEdit_x_3->setValidator(new QDoubleValidator(this));
}

// -------------------------------------------

void Calculator::calculateCredit() {
  m_credit.setSum(ui->lineEdit_sumCredit->text().replace(" ", ""));
  m_credit.setTime(ui->lineEdit_timeCredit->text());
  m_credit.setProcent(ui->lineEdit_procent->text());
  m_credit.setIsMount(!ui->comboBox_time->currentIndex());
  m_credit.setDifferent(ui->rb_differ->isChecked());

  m_credit.calculate();

  ui->label_one->setText(m_credit.infoMonthlyPayment());
  ui->label_two->setText(m_credit.infoAccruedInterest());
  ui->label_three->setText(m_credit.infoDebgAndInterest());
}

// -------------------------------------------

void Calculator::connection_configurations() {
  connection_num();
  connection_sign();
  connection_functions();
  connection_graphic();
  connection_credit();
}

// -------------------------------------------

void Calculator::connection_num() {
  connect(ui->btn_0, &QPushButton::clicked, this,
          &Calculator::on_button0Clicked);
  connect(ui->btn_1, &QPushButton::clicked, this,
          &Calculator::on_button1Clicked);
  connect(ui->btn_2, &QPushButton::clicked, this,
          &Calculator::on_button2Clicked);
  connect(ui->btn_3, &QPushButton::clicked, this,
          &Calculator::on_button3Clicked);
  connect(ui->btn_4, &QPushButton::clicked, this,
          &Calculator::on_button4Clicked);
  connect(ui->btn_5, &QPushButton::clicked, this,
          &Calculator::on_button5Clicked);
  connect(ui->btn_6, &QPushButton::clicked, this,
          &Calculator::on_button6Clicked);
  connect(ui->btn_7, &QPushButton::clicked, this,
          &Calculator::on_button7Clicked);
  connect(ui->btn_8, &QPushButton::clicked, this,
          &Calculator::on_button8Clicked);
  connect(ui->btn_9, &QPushButton::clicked, this,
          &Calculator::on_button9Clicked);
}

// -------------------------------------------

void Calculator::connection_sign() {
  connect(ui->btn_ce, &QPushButton::clicked, this,
          &Calculator::on_buttonCeClicked);
  connect(ui->btn_del, &QPushButton::clicked, this,
          &Calculator::on_buttonDelClicked);
  connect(ui->btn_change, &QPushButton::clicked, this,
          &Calculator::on_buttonChangeClicked);

  connect(ui->btn_equal, &QPushButton::clicked, this,
          &Calculator::on_buttonEqualClicked);

  connect(ui->btn_dot, &QPushButton::clicked, this,
          &Calculator::on_buttonDotClicked);

  connect(ui->btn_sum, &QPushButton::clicked, this,
          &Calculator::on_buttonSumClicked);
  connect(ui->btn_sub, &QPushButton::clicked, this,
          &Calculator::on_buttonSubClicked);
  connect(ui->btn_mul, &QPushButton::clicked, this,
          &Calculator::on_buttonMulClicked);
  connect(ui->btn_div, &QPushButton::clicked, this,
          &Calculator::on_buttonDivClicked);

  connect(ui->btn_mod, &QPushButton::clicked, this,
          &Calculator::on_buttonModClicked);

  connect(ui->btn_brackets_l, &QPushButton::clicked, this,
          &Calculator::on_buttonBracketLeftClicked);

  connect(ui->btn_brackets_r, &QPushButton::clicked, this,
          &Calculator::on_buttonBracketRightClicked);

  connect(ui->btn_p, &QPushButton::clicked, this,
          &Calculator::on_buttonPClicked);
}

// -------------------------------------------

void Calculator::connection_functions() {
  connect(ui->btn_sin, &QPushButton::clicked, this,
          &Calculator::on_buttonSinClicked);
  connect(ui->btn_cos, &QPushButton::clicked, this,
          &Calculator::on_buttonCosClicked);
  connect(ui->btn_tan, &QPushButton::clicked, this,
          &Calculator::on_buttonTanClicked);
  connect(ui->btn_acos, &QPushButton::clicked, this,
          &Calculator::on_buttonAcosClicked);
  connect(ui->btn_asin, &QPushButton::clicked, this,
          &Calculator::on_buttonAsinClicked);
  connect(ui->btn_atan, &QPushButton::clicked, this,
          &Calculator::on_buttonAtanClicked);
  connect(ui->btn_sqrt, &QPushButton::clicked, this,
          &Calculator::on_buttonSqrtClicked);
  connect(ui->btn_pow, &QPushButton::clicked, this,
          &Calculator::on_buttonPowClicked);
  connect(ui->btn_ln, &QPushButton::clicked, this,
          &Calculator::on_buttonLnClicked);
  connect(ui->btn_log, &QPushButton::clicked, this,
          &Calculator::on_buttonLogClicked);
}

// -------------------------------------------

void Calculator::connection_graphic() {
  connect(ui->btn_graph, &QPushButton::clicked, this,
          &Calculator::on_buttonGraphClicked);

  connect(ui->btn_x, &QPushButton::clicked, this,
          &Calculator::on_buttonXClicked);
}

// -------------------------------------------

void Calculator::connection_credit() {
  connect(ui->btn_calculate, &QPushButton::clicked, this,
          &Calculator::on_buttonCalculationCredit);

  connect(ui->lineEdit_sumCredit, &QLineEdit::textEdited, this,
          &Calculator::formatText);
}

}  // namespace s21
