#include "mainwindow.h"

#include <QApplication>
#include <QtDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.testInit();
    w.printODT();
    w.printPDF();
    w.show();

    return a.exec();
}

