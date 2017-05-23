#include "mainwindow.h"
#include <QTextTable>
#include <QTextEdit>
#include <QTextTableFormat>
#include <QTextDocumentWriter>
#include <QtPrintSupport/QPrinter>
#include <QFileDialog>

QTextBlockFormat getTextFormat()
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
    for(int i = 0; i < 32; ++i)
        constraints << QTextLength(QTextLength::FixedLength, 21);
    tableFormat.setColumnWidthConstraints(constraints);

    return tableFormat;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QTextEdit* teEditor = new QTextEdit();
    this->setCentralWidget(teEditor);

    document = new QTextDocument(teEditor);
    QTextCursor cur(document);
    teEditor->setDocument(document);

    table = cur.insertTable(1, wordLen + 1, tableFormat());

    textFormat = getTextFormat();

    insertNumberLine(0);
    insertNumberLine(2);

    insertField("№ Слова",    0, 0);
    insertField("0...(Nh-1)", 1, 0);

    testInit();



    QTextDocumentWriter writer;
    writer.setFormat("HTML");
    writer.setFileName("timob.odt");
    writer.write(document);


    QPrinter printer(QPrinter::HighResolution);
    printer.setPaperSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Portrait);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("output.pdf");

    teEditor->document()->print(&printer);
}

void MainWindow::appendRows(int count)
{
    auto rowCount = table->rows();
    table->appendRows(count);

    for (int i = rowCount; i < rowCount + count; ++i )
    {
        auto cur = table->cellAt(i, 0).firstCursorPosition();
        cur.setBlockFormat(textFormat);
        cur.insertText("Nh + " + QString::number(i - rowCount));
    }
}

void MainWindow::insertNumberLine(int row)
{
    table->appendRows(1);
    for(int j = 0; j < wordLen; ++j)
    {
        QTextCursor cursor = table->cellAt(row, j+1).firstCursorPosition();
        cursor.setBlockFormat(textFormat);
        cursor.insertText(QString::number(wordLen - j - 1));
    }
}

void MainWindow::insertField(const QString &text, int row, int col, int len)
{
    table->mergeCells(row, col, 1, len);

    auto cur = table->cellAt(row, col).firstCursorPosition();
    cur.setBlockFormat(textFormat);
    cur.insertText(text);
}

void MainWindow::testInit()
{
    appendRows(5);

    insertField("Общий заголовок тип 3", 1, 1, 32);

    insertField("SyncCounter", 3, 1, 32);

    insertField("FreqNum",  4, 4, 7);
    insertField("P",        4, 11, 2);
    insertField("Adapt",    4, 12);
    insertField("CI",       4, 14);
    insertField("S",        4, 15);
    insertField("I",        4, 16);
    insertField("Azimuth",  4, 17, 18);

    insertField("ScanProg",      5, 1, 8);
    insertField("SectAD_step",   5, 9, 8);
    insertField("SectAD_end",    5, 17, 8);
    insertField("SectAD_Beg",    5, 25, 8);

    insertField("ED",      6, 1, 8);
    insertField("AD_NRZ",  6, 9, 8);
    insertField("AD",      6, 17, 8);
    insertField("AD_Reg",  6, 25, 8);

    insertField("AD_AKP3",  7, 9, 8);
    insertField("AD_AKP2",  7, 17, 8);
    insertField("AD_AKP1",  7, 25, 8);
}
