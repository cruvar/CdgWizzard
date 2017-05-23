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
    w.addBrackets('(',')');
    w.addBrackets('[',']');
    w.addBrackets('{','}');
    QString testStr = "()(){}({d() cv[ xxa[vcv] rq((((()))))we]df }df)";
    //QString TestStr = "( [ xxx ) ]";
    //if (w.isValid(testStr)) qDebug() << "Str is Valid!";
    //else qDebug() << "Str is NOT Valid!";

    return a.exec();
}

