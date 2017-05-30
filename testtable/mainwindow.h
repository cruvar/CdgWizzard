#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTextTable;
class QTextBlockFormat;
class QTextDocument;
class QTextCursor;
class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void insertField(const QString&, const int);
    void printPDF();
    void printODT();
    void insertHeader(const QString&);

    void testInit();

private:
    void appendRow();
    bool rowFilled();
    void createTableDecor();


private:
    QTextTable *tab;
    QTextEdit *teEditor;
    QTextDocument *doc;
    QTextCursor *cur;
    QTextBlockFormat *textFormat;
    std::pair<uint,uint> insertCoords;
};

#endif // MAINWINDOW_H
