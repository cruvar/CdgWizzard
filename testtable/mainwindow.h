#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTextTable;
class QTextBlockFormat;
class QTextDocument;
class QTextCursor;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addField(const QString&, const int);


private:
    void appendRow();
    bool rowFilled();


private:
    QTextTable *tab;
    QTextDocument *doc;
    QTextCursor *cur;
    QTextBlockFormat *centerAlignment;
    std::pair<uint,uint> insertCoords;
};

#endif // MAINWINDOW_H
