#include "mainwindow.h"

#include <QTextTable>
#include <QTextEdit>
#include <QTextTableFormat>
#include <QTextDocumentWriter>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QtDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    int rowCount = 8;
    QTextEdit* teEditor = new QTextEdit;

    QTextTableFormat tableFormat;
    QBrush brush = tableFormat.borderBrush();
    brush.setColor(QColor(Qt::black));
    brush.setStyle(Qt::SolidPattern);
    tableFormat.setBorderBrush(brush);
    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));
    tableFormat.setCellSpacing(0);
    tableFormat.setCellPadding(1);
    tableFormat.setBorder(1);

    //set cell`s width in table for each column
    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::FixedLength, 70);
    for (int i = 0; i < 32; ++i)
        constraints << QTextLength(QTextLength::FixedLength, 17);
    tableFormat.setColumnWidthConstraints(constraints);

    doc = new QTextDocument(teEditor);
    cur = new QTextCursor(doc);
    tab = cur->insertTable(rowCount, 33, tableFormat);
    centerAlignment = new QTextBlockFormat();
    centerAlignment->setAlignment(Qt::AlignHCenter);

    //fill standard table fields
    tab->mergeCells(1, 1, 1, 32);
    *cur = tab->cellAt(0, 0).firstCursorPosition();
    cur->setBlockFormat(*centerAlignment);
    cur->insertText("№ Слова");
    *cur = tab->cellAt(1, 0).firstCursorPosition();
    cur->setBlockFormat(*centerAlignment);
    cur->insertText("0...(Nh-1)");
    for(int i = 0; i < rowCount-3; ++i)
    {
        *cur = tab->cellAt(3+i, 0).firstCursorPosition();
        cur->setBlockFormat(*centerAlignment);
        cur->insertText("Nh+"+QVariant(i).toString());
    }
    for(int i = 31, j = 1; i >= 0; --i, ++j)
    {
        *cur = tab->cellAt(0, j).firstCursorPosition();
        cur->setBlockFormat(*centerAlignment);
        cur->insertText(QVariant(i).toString());
    }
    for(int i = 31, j = 1; i >= 0; --i, ++j)
    {
        *cur = tab->cellAt(2, j).firstCursorPosition();
        cur->setBlockFormat(*centerAlignment);
        cur->insertText(QVariant(i).toString());
    }

    insertCoords.first  = 3;
    insertCoords.second = 33;
    teEditor->setDocument(doc);
    teEditor->show();
/*
    QTextDocumentWriter writer;
    writer.setFormat("ODT");
    writer.setFileName("timob.odt");
    writer.write(doc);

    QPrinter printer(QPrinter::HighResolution);
    printer.setPaperSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("output.pdf");

    teEditor->document()->print(&printer);

// print the document in pdf file
QPrinter printer(QPrinter::HighResolution);
printer.setOutputFileName("output.pdf");
printer.setOutputFormat(QPrinter::PdfFormat);

printer.setPaperSize(QPrinter::A4);
printer.setResolution(300);

previewDoc.print(&printer);
*/
}

MainWindow::~MainWindow()
{

}

void MainWindow::addField(const QString &str, const int length)
{
    int columnNumber = insertCoords.second - length;
    if (columnNumber > 0)
    {
        insertCoords.second = columnNumber;
        tab->mergeCells(insertCoords.first, insertCoords.second, 1, length);
        *cur = tab->cellAt(insertCoords.first, insertCoords.second).firstCursorPosition();
        cur->setBlockFormat(*centerAlignment);
        cur->insertText(str);
        checkRowFieldsLimit();
    }
}

void MainWindow::addBrackets(const char bracket1, const char bracket2)
{
    opBracketArr += bracket1;
    closeBracketArr += bracket2;
}

bool MainWindow::isValid(QString &str)
{
    int indx;
    bool valid;
    int strLen = str.length();
    for (int i = 0; i < strLen; ++i)
    {
        indx = checkOpBracket(str[i]);
        if (indx > -1)
        {
            valid = checkRange(str, i, indx);
            if (!valid) return false;
        }
        else if (isCloseBracket(str[i])) return false;
    }
    return true;
}

int MainWindow::checkOpBracket(QCharRef ch)
{
    for (int i = 0; i < opBracketArr.length(); ++i)
        if (ch == opBracketArr[i]) return i;
    return -1;
}

bool MainWindow::isCloseBracket(QCharRef ch)
{
    for (int i = 0; i < closeBracketArr.length(); ++i)
        if (ch == closeBracketArr[i]) return true;
    return false;
}

bool MainWindow::checkRange(QString& str, int &i, const int closeBracketIndx)
{
    ++i;
    int indx;
    bool valid = true;
    for (; i < str.length(); ++i)
    {
        if (closeBracketArr[closeBracketIndx] == str[i])
            return true;
        indx = checkOpBracket(str[i]);
        if (indx > -1)
        {
            valid = checkRange(str, i, indx);
            if (!valid) return false;
        }
        else
        {
            if (isCloseBracket(str[i]))
                return false;
        }
    }
    return false;
}

void MainWindow::checkRowFieldsLimit()
{
    if (insertCoords.second == 1)
    {
        insertCoords.second = 33;
        insertCoords.first +=  1;
    }
}
