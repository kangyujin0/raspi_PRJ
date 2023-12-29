#include "mainwindow.h"
#include <QApplication>
#include <stdio.h>
#include <wiringPi.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setFixedSize(800, 250);
    w.show();
    return a.exec();
}
