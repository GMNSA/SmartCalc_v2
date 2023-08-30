#include <QApplication>
#include <QDebug>
#include <QLoggingCategory>

#include "../includes/View/mainwindow.hpp"

int main(int argc, char *argv[]) {
  qWarning() << "one";
  QApplication a(argc, argv);
  QLoggingCategory::defaultCategory()->setEnabled(QtDebugMsg, true);
  qWarning() << "two";
  MainWindow w;
  w.show();
  qWarning() << "three";
  return a.exec();
}
