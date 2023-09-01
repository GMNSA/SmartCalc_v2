#include <QApplication>
#include <QDebug>
#include <QLoggingCategory>

#include "../includes/View/calculator.hpp"

int main(int argc, char *argv[]) {
  qWarning() << "one";
  QApplication a(argc, argv);
  QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
  qWarning() << "two";
  Calculator w;
  w.show();
  qWarning() << "three";
  return a.exec();
}
