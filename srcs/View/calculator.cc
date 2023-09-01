#include "../../includes/View/calculator.hpp"

#include <QDialog>
#include <QRegularExpressionValidator>
#include <QtDebug>

#include "./ui_calculator.h"

int is_left_bracket(QString str_) {
  int n_left = 0;
  int n_right = 0;

  for (auto const &i : str_) {
    if (i == '(')
      ++n_left;
    else if (i == ')')
      ++n_right;
  }

  return (n_left > n_right ? 1 : 0);
}

// -------------------------------------------

int is_sign(QChar ch_) {
  int res = 0;
  if (ch_ == '*')
    res = 1;
  else if (ch_ == '/')
    res = 1;
  else if (ch_ == '-')
    res = 1;
  else if (ch_ == '+')
    res = 1;
  else if (ch_ == '^')
    res = 1;
  else if (ch_ == '%')
    res = 1;

  return (res);
}

// *******************************************

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Calculator),
      m_is_clear(1),
      m_str(""),
      m_calc(),
      m_graph(nullptr) {
  ui->setupUi(this);
  ui->checkBox_smart->setCheckState(Qt::CheckState::Checked);

  if (!(m_graph = new DialogGraph(this))) ui->menubar->close();

  settingsCredit();
  settingsGraph();

  connection_configurations();

  if (m_is_clear) m_str = "0";
}

// -------------------------------------------

Calculator::~Calculator() { delete ui; }

// -------------------------------------------

void Calculator::on_button0Clicked() { add_text_to_str("0"); }

// -------------------------------------------

void Calculator::on_button1Clicked() { add_text_to_str("1"); }

// -------------------------------------------

void Calculator::on_button2Clicked() { add_text_to_str("2"); }

void Calculator::on_button3Clicked() { add_text_to_str("3"); }

void Calculator::on_button4Clicked() { add_text_to_str("4"); }

// -------------------------------------------

void Calculator::on_button5Clicked() { add_text_to_str("5"); }

// -------------------------------------------

void Calculator::on_button6Clicked() { add_text_to_str("6"); }

// -------------------------------------------

void Calculator::on_button7Clicked() { add_text_to_str("7"); }

// -------------------------------------------

void Calculator::on_button8Clicked() { add_text_to_str("8"); }

// -------------------------------------------

void Calculator::on_button9Clicked() { add_text_to_str("9"); }

// -------------------------------------------

void Calculator::on_buttonDotClicked() { add_text_to_str("."); }

// -------------------------------------------

void Calculator::on_buttonXClicked() { add_text_to_str("x"); }

// -------------------------------------------

void Calculator::on_buttonPClicked() { add_text_to_str("π"); }

// -------------------------------------------

void Calculator::on_buttonCeClicked() {
  m_str.clear();
  m_is_clear = 1;
  m_str = "0";
  reset_data_str();
  ui->display_repeat->setText("");
}

// -------------------------------------------

void Calculator::on_buttonDelClicked() {
  int n_str = m_str.size();
  m_str = m_str.trimmed();

  if (m_str.endsWith("cos(")) {
    m_str.remove(n_str - 4, n_str);
  } else if (m_str.endsWith("sin(")) {
    m_str.remove(n_str - 4, n_str);
  } else if (m_str.endsWith("tan(")) {
    m_str.remove(n_str - 4, n_str);
  } else if (m_str.endsWith("acos(")) {
    m_str.remove(n_str - 5, n_str);
  } else if (m_str.endsWith("asin(")) {
    m_str.remove(n_str - 5, n_str);
  } else if (m_str.endsWith("atan(")) {
    m_str.remove(n_str - 5, n_str);
  } else if (m_str.endsWith("sqrt(")) {
    m_str.remove(n_str - 5, n_str);
  } else if (m_str.endsWith("ln(")) {
    m_str.remove(n_str - 3, n_str);
  } else if (m_str.endsWith("log(")) {
    m_str.remove(n_str - 4, n_str);
  } else {
    m_str.chop(1);
  }

  if (m_str.size() == 0) {
    m_str = "0";
    m_is_clear = 1;
  }
  reset_data_str();
}

// -------------------------------------------

void Calculator::on_buttonCosClicked() { add_text_to_str("cos("); }

// -------------------------------------------

void Calculator::on_buttonSinClicked() { add_text_to_str("sin("); }

// -------------------------------------------

void Calculator::on_buttonTanClicked() { add_text_to_str("tan("); }

// -------------------------------------------

void Calculator::on_buttonAcosClicked() { add_text_to_str("acos("); }

// -------------------------------------------

void Calculator::on_buttonAsinClicked() { add_text_to_str("asin("); }

// -------------------------------------------

void Calculator::on_buttonAtanClicked() { add_text_to_str("atan("); }

// -------------------------------------------

void Calculator::on_buttonSqrtClicked() { add_text_to_str("sqrt("); }

// -------------------------------------------

void Calculator::on_buttonPowClicked() { add_text_to_str("^"); }

// -------------------------------------------

void Calculator::on_buttonLnClicked() { add_text_to_str("ln("); }

// -------------------------------------------

void Calculator::on_buttonLogClicked() { add_text_to_str("log("); }

// -------------------------------------------

void Calculator::on_buttonChangeClicked() {
  QString tmp;
  QRegularExpression re;
  QRegularExpressionMatch reMatch = re.match("\\d");

  if (!m_str.isEmpty()) {
    if (m_str.size() == 1) {
      if (m_str[0].isDigit()) {
        tmp = "-" + m_str;
      } else {
        tmp = "-(" + m_str + ")";
      }
      m_str = tmp;
    } else if (m_str.size() >= 4) {
      if (m_str[0] == '-' && m_str[1] == '(' &&
          m_str[m_str.size() - 1] == ')') {
        m_str.remove(m_str.size() - 1, 1);
        m_str.remove(1, 1);
        m_str.remove(0, 1);
      } else if (m_str[0] == '-' && m_str[1].isDigit() &&
                 m_str[m_str.size() - 1].isDigit()) {
        m_str.remove(0, 1);
      } else {
        tmp = "-(" + m_str + ")";
        m_str = tmp;
      }
    } else if (m_str[0] != '-') {
      if (reMatch.hasMatch()) {
        tmp = "-" + m_str;
        m_str = tmp;
      } else {
        tmp = "-(" + m_str + ")";
        m_str = tmp;
      }
    } else if (m_str[0] == '-') {
      m_str.remove(0, 1);
    }
  }
  ui->display->setText(m_str);
}

// -------------------------------------------

void Calculator::on_buttonSumClicked() { add_text_to_str(" + "); }

// -------------------------------------------

void Calculator::on_buttonSubClicked() { add_text_to_str(" - "); }

// -------------------------------------------

void Calculator::on_buttonMulClicked() { add_text_to_str(" * "); }

// -------------------------------------------

void Calculator::on_buttonDivClicked() { add_text_to_str(" / "); }

// -------------------------------------------

void Calculator::on_buttonModClicked() { add_text_to_str("%"); }

void Calculator::on_buttonBracketLeftClicked() { setBrackets("("); }

void Calculator::on_buttonBracketRightClicked() { setBrackets(")"); }

// -------------------------------------------

void Calculator::on_buttonEqualClicked() {
  int is_graph = 0;
  m_str = ui->display->toPlainText();
  m_str = fixedForDisplay2(m_str);
  ui->display_repeat->setText(m_str);
  m_str = fixedString(m_str);

  checkXData();

  if (m_str.indexOf("x") != -1) {
    m_strForGraph = m_str;
    m_str.replace(QString("x"), QString::number(m_graph->x()));
    is_graph = 1;
  }

  m_str = m_calc.calculate(m_str);
  ui->display->setText(m_str);

  if (is_graph && m_str != "error" && m_str != "na") {
    openGraphic();
  }
}

// -------------------------------------------

void Calculator::on_buttonGraphClicked() { m_graph->show(); }

// -------------------------------------------

void Calculator::on_buttonCalculationCredit() { calculateCredit(); }

void Calculator::formatText() {
  QString num = ui->lineEdit_sumCredit->text().replace(" ", "");
  QString str = QString("%L1").arg(num.toLongLong());
  str = str.replace(",", " ");

  ui->lineEdit_sumCredit->setText(str);
}

// -------------------------------------------

QString Calculator::fixedString(QString str_) {
  QString res;

  if (str_.indexOf("atan") != -1) {
    str_ = str_.replace("atan", "atn");
  } else if (str_.indexOf("asin") != -1) {
    str_ = str_.replace("asin", "asn");
  } else if (str_.indexOf("acos") != -1) {
    str_ = str_.replace("acos", "acs");
  } else if (str_.indexOf("π") != -1) {
    str_ = str_.replace("π", QString::number(M_PI));
  }

  res = str_;

  return (res);
}

// -------------------------------------------

QString Calculator::fixedForDisplay2(QString str_) {
  QString res;
  unsigned n_str = 0;
  QChar before = '\0';
  QChar current = '\0';
  QChar after = '\0';

  str_.replace(" ", "");
  n_str = str_.size();

  for (unsigned i = 0; i < n_str; ++i) {
    before = current;
    current = str_[i];

    if (i + 1 != n_str)
      after = str_[i + 1];
    else
      after = '\0';

    if (is_sign(current)) {
      if ((before == '\0' || before == '(') &&
          (after.isDigit() || after == '\0' || after == ')')) {
        res += str_[i];
      } else if ((before == ')' || before.isDigit() || before.isLetter()) &&
                 (after.isDigit() || after.isLetter())) {
        res += ' ';
        res += str_[i];
        res += ' ';
      } else if ((before.isDigit() || before == ')') && after == '(') {
        res += ' ';
        res += str_[i];
        res += ' ';
      } else if ((before == '(') && after == '(') {
        res += ' ';
        res += str_[i];
      } else {
        res += str_[i];
      }
    } else {
      res += str_[i];
    }
  }

  return (res);
}

// -------------------------------------------

void Calculator::reset_data_str() { ui->display->setText(m_str); }

// -------------------------------------------

void Calculator::openGraphic() {
  m_graph->setStrNum(m_strForGraph);
  m_graph->show();
  checkXData();
  m_graph->openGraphic();
}

// -------------------------------------------

void Calculator::checkXData() {
  m_graph->setX(ui->lineEdit_x->text().toDouble());

  if (!ui->lineEdit_x_2->text().isEmpty())
    m_graph->setXMin(ui->lineEdit_x_2->text().toDouble());
  else
    m_graph->setXMin(X_MIN);

  if (!ui->lineEdit_x_3->text().isEmpty())
    m_graph->setXMax(ui->lineEdit_x_3->text().toDouble());
  else
    m_graph->setXMax(X_MAX);
}

// -------------------------------------------

void Calculator::add_text_to_str(QString str_) {
  if ((m_is_clear == 1 || m_str == "error" || m_str == "na")) {
    if (str_ == " + " || str_ == " / " || str_ == " * " || str_ == ".") {
      m_is_clear = 0;
      m_str += str_;
    } else {
      m_str = str_;
      m_is_clear = 0;
    }
  } else {
    m_str += str_;
  }
  m_str = fixedForDisplay2(m_str);
  reset_data_str();
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

void Calculator::setBrackets(QString str_) {
  bool isSmart = ui->checkBox_smart->checkState();
  qDebug() << "smart: " << isSmart;

  if (!isSmart) {
    add_text_to_str(str_);
  } else {
    int n_brackets = is_left_bracket(m_str);

    if (ui->checkBox_smart->isChecked()) {
      if (n_brackets == 0) {
        add_text_to_str("(");
      } else {
        add_text_to_str(")");
      }
    }
  }
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
