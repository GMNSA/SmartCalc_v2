#include <QApplication>
#include <QDebug>
#include <QLoggingCategory>

#include "../includes/Controller/calculatorcontroller.hpp"
#include "../includes/Controller/icalculatorcontroller.hpp"
#include "../includes/Model/imodel.hpp"
#include "../includes/Model/modelcalculator.hpp"
#include "../includes/View/calculator.hpp"

int main(int argc, char *argv[]) {
  qWarning() << "one";
  QApplication a(argc, argv);
  QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
  qWarning() << "two";

  ns_model::IModel *model = new ns_model::ModelCalculator;

  ns_simple_controller::ICalculatorController *controller =
      new ns_simple_controller::CalculatorController(model);

  Calculator w(controller);
  w.show();

  qWarning() << "three";
  return a.exec();
}
