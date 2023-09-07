#ifndef INCLUDES_VIEW_CALCULATOR_HPP_
#define INCLUDES_VIEW_CALCULATOR_HPP_

#include <QMainWindow>

#include "../Controller/icalculatorcontroller.hpp"
#include "../creditcalculator.hpp"
#include "./dialoggraph.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class Calculator;
}
QT_END_NAMESPACE

class Calculator : public QMainWindow {
  Q_OBJECT

 public:
  explicit Calculator(
      ns_simple_controller::ICalculatorController *controller = nullptr,
      QWidget *parent = nullptr);
  ~Calculator();

 signals:
  void signal_reset_data();

 private slots:
  void on_button0Clicked();
  void on_button1Clicked();
  void on_button2Clicked();
  void on_button3Clicked();
  void on_button4Clicked();
  void on_button5Clicked();
  void on_button6Clicked();
  void on_button7Clicked();
  void on_button8Clicked();
  void on_button9Clicked();
  void on_buttonDotClicked();
  void on_buttonXClicked();
  void on_buttonPClicked();
  void on_buttonCeClicked();
  void on_buttonDelClicked();
  void on_buttonCosClicked();
  void on_buttonSinClicked();
  void on_buttonTanClicked();
  void on_buttonAcosClicked();
  void on_buttonAsinClicked();
  void on_buttonAtanClicked();
  void on_buttonSqrtClicked();
  void on_buttonPowClicked();
  void on_buttonLnClicked();
  void on_buttonLogClicked();
  void on_buttonChangeClicked();

  void on_buttonSumClicked();
  void on_buttonSubClicked();
  void on_buttonMulClicked();
  void on_buttonDivClicked();
  void on_buttonModClicked();

  void on_buttonBracketLeftClicked();
  void on_buttonBracketRightClicked();

  void on_buttonEqualClicked();

  void on_buttonGraphClicked();

  void on_buttonCalculationCredit();

  void formatText();

 private:
  Ui::Calculator *ui;

  int m_is_clear;
  QString display_text_;
  QString m_strForGraph;
  ns_simple_controller::ICalculatorController *calculator_;
  DialogGraph *m_graph;
  CreditCalculator m_credit;
  int min_x_;
  int max_x_;

#ifdef FOR_TEST

 public:
#else

 private:
#endif

  // QString fixedString(QString str_);
  // QString fixedForDisplay2(QString str_);

  void ResetDisplay(QString const &str);
  void ResetRepeatDisplay(QString const &str);
  void openGraphic();
  void checkXData();

  // void add_text_to_str(QString str_);
  void settingsCredit();
  void settingsGraph();

  void CalculateSimple();
  void calculateCredit();

  // void setBrackets(QString str_);

  void connection_configurations();
  void connection_num();
  void connection_sign();
  void connection_functions();
  void connection_graphic();

  void connection_credit();
};
#endif  // INCLUDES_VIEW_CALCULATOR_HPP_
