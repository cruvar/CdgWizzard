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
    void addBrackets(const char, const char);
    bool isValid(QString&);
    void addField(const QString&, const int);
    void appendRow();
    bool rowFilled();


private:
    int  checkOpBracket(QCharRef);
    bool isCloseBracket(QCharRef);
    bool checkRange(QString&, int&, const int);
    void checkRowFieldsLimit();


private:
    QTextTable *tab;
    QTextDocument *doc;
    QTextCursor *cur;
    QTextBlockFormat *centerAlignment;
    std::pair<uint,uint> insertCoords;
    QString opBracketArr = "";
    QString closeBracketArr = "";
};

#endif // MAINWINDOW_H
