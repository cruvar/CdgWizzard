#include "mainwindow.h"

#include <QTextTable>
#include <QTextEdit>
#include <QTextTableFormat>
#include <QTextDocumentWriter>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QtDebug>

//create table maket
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    int rowCount = 4;
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
    *cur = tab->cellAt(3, 0).firstCursorPosition();
    cur->setBlockFormat(*centerAlignment);
    cur->insertText("Nh+0");

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
    if (rowFilled()) appendRow();//checkRowFieldsLimit();
    int columnNumber = insertCoords.second - length;
    if (columnNumber > 0)
    {
        insertCoords.second = columnNumber;
        tab->mergeCells(insertCoords.first, insertCoords.second, 1, length);
        *cur = tab->cellAt(insertCoords.first, insertCoords.second).firstCursorPosition();
        cur->setBlockFormat(*centerAlignment);
        cur->insertText(str);
    }
}

void MainWindow::appendRow()
{
    insertCoords.first +=  1;
    insertCoords.second = 33;
    tab->appendRows(1);
    *cur = tab->cellAt(insertCoords.first, 0).firstCursorPosition();
    cur->setBlockFormat(*centerAlignment);
    cur->insertText("Nh+"+QString::number(tab->rows()-4));
}

bool MainWindow::rowFilled()
{
    if (insertCoords.second == 1) return true;
    else return false;
}

