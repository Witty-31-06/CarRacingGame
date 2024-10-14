#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Car Racing Game");
    w.showMaximized();
    w.show();
    return a.exec();
}
