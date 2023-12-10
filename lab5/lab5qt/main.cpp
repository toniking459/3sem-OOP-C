#include "mainwindow.h"
#include <QLabel>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
   //w.show();
    QLabel *label = new QLabel("Hello, World!");
    label -> resize(144,144);
    label -> show();

    return a.exec();
}
