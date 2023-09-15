#include <QApplication>
#include <QDebug>
#include <QLoggingCategory>

#include "../includes/Controller/calculatorcontroller.hpp"
#include "../includes/Controller/icalculatorcontroller.hpp"
#include "../includes/Model/imodel.hpp"
#include "../includes/Model/modelcalculator.hpp"
#include "../includes/View/calculator.hpp"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);

  s21::IModel *model = new s21::ModelCalculator;
  s21::ICalculatorController *controller = new s21::CalculatorController(model);

  s21::Calculator w(controller);
  w.show();

  return a.exec();
}
