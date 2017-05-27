#include "mainwindow.h"

#include <QTextTable>
#include <QTextEdit>
#include <QTextTableFormat>
#include <QTextDocumentWriter>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>
#include <QtDebug>


QTextTableFormat tableFormat()
{
    QTextTableFormat tableFormat;

    QBrush brush = tableFormat.borderBrush();
    brush.setColor(QColor(Qt::black));
    brush.setStyle(Qt::SolidPattern);
    tableFormat.setBorderBrush(brush);
    tableFormat.setWidth(QTextLength(QTextLength::PercentageLength, 100));
    tableFormat.setCellSpacing(0);
    tableFormat.setCellPadding(1);
    tableFormat.setBorder(1);

    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::FixedLength, 70);
    for (int i = 0; i < 32; ++i)
        constraints << QTextLength(QTextLength::FixedLength, 17);
    tableFormat.setColumnWidthConstraints(constraints);

    return tableFormat;
}

QTextBlockFormat getTableTextFormat()
{
    QTextBlockFormat format;

    format.setAlignment(Qt::AlignHCenter);
    format.setTopMargin(0.0);
    format.setRightMargin(0.0);
    format.setBottomMargin(0.0);
    format.setLeftMargin(0.0);
    format.setIndent(0);
    format.setNonBreakableLines(true);

    return format;
}

QTextCharFormat getCommentTextFormat()
{
    QTextCharFormat format;
    format.setFontFamily("Times");
    format.setFontPointSize(14);
    return format;
}

//create table maket
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    teEditor = new QTextEdit;
    this->setCentralWidget(teEditor);
    teEditor->setFontFamily("Courier");
    teEditor->setFontPointSize(14);
    doc = new QTextDocument(teEditor);
    cur = new QTextCursor(doc);
    teEditor->setDocument(doc);
    tab = cur->insertTable(5, 33, tableFormat());

    textFormat = new QTextBlockFormat();
    *textFormat = getTableTextFormat();
    commentTextFormat = new QTextCharFormat();
    *commentTextFormat = getCommentTextFormat();
    createCarcass();

    insertCoords.first  = 3;
    insertCoords.second = 33;
}

MainWindow::~MainWindow()
{

}

void MainWindow::insertField(const QString &fieldName, const int lengthOfField_bit)
{
    if (rowFilled()) appendRow();
    int columnNumber = insertCoords.second - lengthOfField_bit;
    if (columnNumber > 0)
    {
        insertCoords.second = columnNumber;
        tab->mergeCells(insertCoords.first, insertCoords.second, 1, lengthOfField_bit);
        *cur = tab->cellAt(insertCoords.first, insertCoords.second).firstCursorPosition();
        cur->setBlockFormat(*textFormat);
        cur->insertText(fieldName);
    }
}

void MainWindow::printPDF()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setPaperSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("output.pdf");
    printer.setResolution(300);
    doc->print(&printer);
}

void MainWindow::printODT()
{
    QTextDocumentWriter writer;
    writer.setFormat("HTML");
    writer.setFileName("timob.odt");
    writer.write(doc);
}

void MainWindow::insertHeader(const QString &str)
{
    *cur = tab->cellAt(1, 1).firstCursorPosition();
    cur->setBlockFormat(*textFormat);
    cur->insertText(str);
}

void MainWindow::insertComment(const QString &fieldName, const QString &fieldComment)
{
    cur->movePosition(QTextCursor::End);
    cur->insertBlock();
    cur->setCharFormat(*commentTextFormat);
    cur->insertText("\n"+fieldName+"\t"+fieldComment);
}

void MainWindow::appendRow()
{
    int rowNumber = tab->rows()-1;
    insertCoords.first +=  1;
    insertCoords.second = 33;
    tab->insertRows(rowNumber, 1);
    *cur = tab->cellAt(insertCoords.first, 0).firstCursorPosition();
    cur->setBlockFormat(*textFormat);
    cur->insertText("Nh+"+QString::number(tab->rows()-4));
}

bool MainWindow::rowFilled()
{
    if (insertCoords.second == 1) return true;
    else return false;
}

void MainWindow::createCarcass()
{
    //fill standard table fields
    tab->mergeCells(1, 1, 1, 32);
    *cur = tab->cellAt(0, 0).firstCursorPosition();
    cur->setBlockFormat(*textFormat);
    cur->insertText("№ Слова");
    *cur = tab->cellAt(1, 0).firstCursorPosition();
    cur->setBlockFormat(*textFormat);
    cur->insertText("0...(Nh-1)");
    *cur = tab->cellAt(3, 0).firstCursorPosition();
    cur->setBlockFormat(*textFormat);
    cur->insertText("Nh+0");
    //fill bit lines
    for(int i = 31, j = 1; i >= 0; --i, ++j)
    {
        *cur = tab->cellAt(0, j).firstCursorPosition();
        cur->setBlockFormat(*textFormat);
        cur->insertText(QVariant(i).toString());
        *cur = tab->cellAt(2, j).firstCursorPosition();
        cur->setBlockFormat(*textFormat);
        cur->insertText(QVariant(i).toString());
        *cur = tab->cellAt(4, j).firstCursorPosition();
        cur->setBlockFormat(*textFormat);
        cur->insertText(QVariant(i).toString());
    }
}

void MainWindow::testInit()
{
    insertHeader("Общий заголовок тип 3");

    insertField("SyncCounter", 32);
    insertField("Azimuth",     16);
    insertField("I",            1);
    insertField("S",            1);
    insertField("CI",           1);
    insertField("P",            1);
    insertField("Adapt",        2);
    insertField("FreqNum",      7);
    insertField("",             1);
    insertField("",             1);
    insertField("",             1);
    insertField("SectAD_Beg",   8);
    insertField("SectAD_end",   8);
    insertField("SectAD_step",  8);
    insertField("ScanProg",     8);
    insertField("AD_Reg",       8);
    insertField("AD",           8);
    insertField("AD_NRZ",       8);
    insertField("ED",           8);
    insertField("AD_AKP1",      8);
    insertField("AD_AKP2",      8);
    insertField("AD_AKP3",      8);

    insertComment("Azimuth", "Азимут (ЕМР = 360º/65536)");
    insertComment("CI", "Признак того, что пеленгация проводилась по сигналу из помеховой зоны");
    insertComment("S", "Признак секторного режима.");
    insertComment("Mod[i]", "Модуляция зондирующего импульса в i-м режиме пакета (0 — отсутствие ЗИ, 1 — немодулированный ЗИ, 2 — ЛЧМ с нарастанием частоты, 3 — ЛЧМ с убыванием частоты)");
}
