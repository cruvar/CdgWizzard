#include "mainwindow.h"

#include <QApplication>
#include <QtDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.addField("Azimuth", 4);
    w.addField("Some", 28);
    w.addField("same", 2);
    w.addField("come", 4);
    w.addField("", 8);
    w.addField("", 18);
    w.addField("came", 6);
    //w.show();

    return a.exec();
}

