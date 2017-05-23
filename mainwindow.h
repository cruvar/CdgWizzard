#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBlockFormat>

class QTextBlockFormat;
class QTextTable;
class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

private:
    void appendRows(int);
    void insertNumberLine(int row);
    void insertField(const QString & text, int row, int col, int len = 1);

    void testInit();

private:
    const int wordLen = 32;
    QTextTable * table;
    QTextBlockFormat textFormat;
    QTextDocument * document;

};

#endif // MAINWINDOW_H
