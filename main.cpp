#include "mainwindow.h"
//#include "settings.h"
#include <QApplication>

singletonSettings* singletonSettings::instance = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
