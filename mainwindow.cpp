#include "mainwindow.h"
#include <QTextTable>
#include <QTextEdit>
#include <QTextTableFormat>
#include <QTextDocumentWriter>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
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

//    teEditor->setStyleSheet("table {border-collapse: collapse; border: solid;}");
    //tableFormat.setAlignment(Qt::AlignCenter);

    //set cell`s width in table for each column
    QVector<QTextLength> constraints;
    constraints << QTextLength(QTextLength::FixedLength, 70);
    for(int i = 0; i < 32; ++i)
        constraints << QTextLength(QTextLength::FixedLength, 17);
    tableFormat.setColumnWidthConstraints(constraints);

    QTextDocument* doc = new QTextDocument(teEditor);
    QTextCursor cur(doc);
    QTextTable* tab = cur.insertTable(8, 33, tableFormat);

    tab->mergeCells(1,  1, 1, 32);
    tab->mergeCells(3,  1, 1, 32);
    tab->mergeCells(4,  4, 1,  7);
    tab->mergeCells(4, 12, 1,  2);
    tab->mergeCells(4, 17, 1, 18);
    tab->mergeCells(5,  1, 1,  8);
    tab->mergeCells(5,  9, 1,  8);
    tab->mergeCells(5, 17, 1,  8);
    tab->mergeCells(5, 25, 1,  8);
    tab->mergeCells(6,  1, 1,  8);
    tab->mergeCells(6,  9, 1,  8);
    tab->mergeCells(6, 17, 1,  8);
    tab->mergeCells(6, 25, 1,  8);
    tab->mergeCells(7,  1, 1,  8);
    tab->mergeCells(7,  9, 1,  8);
    tab->mergeCells(7, 17, 1,  8);
    tab->mergeCells(7, 25, 1,  8);

    //fill table
    QTextBlockFormat centerAlignment;
    centerAlignment.setAlignment(Qt::AlignHCenter);

    cur = tab->cellAt(0, 0).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("№ Слова");
    cur = tab->cellAt(1, 0).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("0...(Nh-1)");
    cur = tab->cellAt(3, 0).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("Nh+0");
    cur = tab->cellAt(4, 0).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("Nh+1");
    cur = tab->cellAt(5, 0).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("Nh+2");
    cur = tab->cellAt(6, 0).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("Nh+3");
    cur = tab->cellAt(7, 0).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("Nh+4");
    for(int i = 31, j = 1; i >= 0; --i, ++j)
    {
        cur = tab->cellAt(0, j).firstCursorPosition();
        cur.setBlockFormat(centerAlignment);
        cur.insertText(QVariant(i).toString());
    }
    for(int i = 31, j = 1; i >= 0; --i, ++j)
    {
        cur = tab->cellAt(2, j).firstCursorPosition();
        cur.setBlockFormat(centerAlignment);
        cur.insertText(QVariant(i).toString());
    }

    cur = tab->cellAt(1,1).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("Общий заголовок тип 3");
    cur = tab->cellAt(3,1).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("SyncCounter");
    cur = tab->cellAt(4,4).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("FreqNum");
    cur = tab->cellAt(4,11).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("P");
    cur = tab->cellAt(4,12).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("Adapt");
    cur = tab->cellAt(4,14).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("CI");
    cur = tab->cellAt(4,15).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("S");
    cur = tab->cellAt(4,16).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("I");
    cur = tab->cellAt(4,17).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("Azimuth");
    cur = tab->cellAt(5,1).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("ScanProg");
    cur = tab->cellAt(5,9).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("SectAD_step");
    cur = tab->cellAt(5,17).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("SectAD_end");
    cur = tab->cellAt(5,25).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("SectAD_Beg");
    cur = tab->cellAt(6,1).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("ED");
    cur = tab->cellAt(6,9).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("AD_NRZ");
    cur = tab->cellAt(6,17).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("AD");
    cur = tab->cellAt(6,25).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("AD_Reg");
    cur = tab->cellAt(7,9).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("AD_AKP3");
    cur = tab->cellAt(7,17).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("AD_AKP2");
    cur = tab->cellAt(7,25).firstCursorPosition();
    cur.setBlockFormat(centerAlignment);
    cur.insertText("AD_AKP1");


    teEditor->setDocument(doc);
    teEditor->show();


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
}

MainWindow::~MainWindow()
{

}

