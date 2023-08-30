#ifndef SRC_INCLUDES_VIEW_MAINWINDOW_HPP_
#define SRC_INCLUDES_VIEW_MAINWINDOW_HPP_

#include <QMainWindow>

#include "../calculationsmartcalc.hpp"
#include "../creditcalculator.hpp"
#include "./dialoggraph.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

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
  Ui::MainWindow *ui;

  int m_is_clear;
  QString m_str;
  QString m_strForGraph;
  CalculationSmartCalc m_calc;
  DialogGraph *m_graph;
  CreditCalculator m_credit;

#ifdef FOR_TEST

 public:
#else

 private:
#endif

  QString fixedString(QString str_);
  QString fixedForDisplay2(QString str_);

  void reset_data_str();
  void openGraphic();
  void checkXData();

  void add_text_to_str(QString str_);
  void settingsCredit();
  void settingsGraph();

  void calculateCredit();

  void setBrackets(QString str_);

  void connection_configurations();
  void connection_num();
  void connection_sign();
  void connection_functions();
  void connection_graphic();

  void connection_credit();
};
#endif  // SRC_INCLUDES_VIEW_MAINWINDOW_HPP_
