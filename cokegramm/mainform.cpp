#include "mainform.h"
#include "ui_mainform.h"
#include "lib.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFileDialog>

MainForm::MainForm(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainForm)
{
  ui->setupUi(this);
  // 0
  tbList.append(ui->tbNameCod);
  tbList.append(ui->tbTimpCod);
  tbList.append(ui->tbGroup);
  // 3
  tbList.append(ui->tbVersion);

  tbList.append(ui->tbNamePol);
  tbList.append(ui->tbUnitPol);
  // 6
  tbList.append(ui->tbLsbPol);
  tbList.append(ui->tbCommentPol);

  tbList.append(ui->tbNameSubType);
  // 9
  tbList.append(ui->tbCommentSubType);

  // 0
  cbList.append(ui->cbTypePol);
  cbList.append(ui->cbTypeSubType);

  // 0
  spbList.append(ui->spbSizePol);
  spbList.append(ui->spbSizeSubType);

  typeList.insert("bool", 1);
  typeList.insert("uint8_t", 8);
  typeList.insert("uint16_t", 16);
  typeList.insert("uint32_t", 32);
  userType = 4;
}

MainForm::~MainForm() {
  tbList.clear();
  cbList.clear();
  spbList.clear();
  delete ui;
}

void MainForm::on_btnitmAdd_clicked() {
  auto tw = ui->twType;
  tw->insertRow(tw->rowCount());
}

void MainForm::on_btnitmDel_clicked() {
  auto tw = ui->twType;
  tw->removeRow(tw->currentRow());
}

void MainForm::on_btnitmClean_clicked() {
  auto tw = ui->twType;
  tw->clearContents();
  tw->setRowCount(0);
}

void MainForm::on_actionExportJSON_triggered() {

  QString fileName = QFileDialog::getSaveFileName(this, "Save...",
                                                         QDir::currentPath(),
                                                         "*.json");
  if (fileName.isEmpty()) {
    return;
  }
  QFile saveFile(fileName);

  if (!saveFile.open(QIODevice::WriteOnly)) {
    qWarning("Couldn't open save file.");
    return;
  }

  QJsonObject generalObject;

  writeJsonGeneral(generalObject, tbList, ui->lwImport);
  writeJsonEnum(generalObject, ui->twListNum, enumList);
  writeJsonDescript(generalObject, ui->twType);
  writeJsonSubType(generalObject, ui->twSubTypeList, ui->twSubTypeTable, subType);

  QJsonDocument saveDoc(generalObject);
  saveFile.write(saveDoc.toJson());
  saveFile.close();
}

void MainForm::on_twType_clicked(const QModelIndex &index) {
  QTableWidget *tw(ui->twType);
  int row(index.row());
  // tbNamePol
  QTableWidgetItem *twi(tw->item(row, 0));
  if (twi != nullptr) {
    tbList[4]->setText(twi->text());
  } else {
    tbList[4]->clear();
  }
  // cbTypePol
  twi = tw->item(row, 1);
  if (twi != nullptr) {
    cbList[0]->setCurrentText(twi->text());
  }
  // tbUnitPol
  twi = tw->item(row, 2);
  if (twi != nullptr) {
    tbList[5]->setText(twi->text());
  } else {
    tbList[5]->clear();
  }
  // spbSizePol
  twi = tw->item(row, 3);
  if (twi != nullptr) {
    spbList[0]->setValue(twi->text().toInt());
  }
  // tbLsbPol
  twi = tw->item(row, 4);
  if (twi != nullptr) {
    tbList[6]->setText(twi->text());
  } else {
    tbList[6]->clear();
  }
  // tbCommentPol
  twi = tw->item(row, 5);
  if (twi != nullptr) {
    tbList[7]->setText(twi->text());
  } else {
    tbList[7]->clear();
  }
}

void MainForm::on_btnitmSave_clicked() {
  QTableWidget *tw(ui->twType);
  int row(tw->currentRow());
  // tbNamePol
  QTableWidgetItem *twi(tw->item(row, 0));
  if (twi != nullptr) {
    twi->setText(tbList[4]->text());
  } else {
    twi = new QTableWidgetItem(tbList[4]->text());
    tw->setItem(row, 0, twi);
  }
  // cbTypePol
  twi = tw->item(row, 1);
  if (twi != nullptr) {
    twi->setText(cbList[0]->currentText());
  } else {
    twi = new QTableWidgetItem(cbList[0]->currentText());
    tw->setItem(row, 1, twi);
  }
  // tbNamePol
  twi = tw->item(row, 2);
  if (twi != nullptr) {
    twi->setText(tbList[5]->text());
  } else {
    twi = new QTableWidgetItem(tbList[5]->text());
    tw->setItem(row, 2, twi);
  }
  // spbSizeSubType
  twi = tw->item(row, 3);
  if (twi != nullptr) {
    twi->setText(QString::number(spbList[0]->value()));
  } else {
    twi = new QTableWidgetItem(QString::number(spbList[0]->value()));
    tw->setItem(row, 3, twi);
  }
  // tbLsbPol
  twi = tw->item(row, 4);
  if (twi != nullptr) {
    twi->setText(tbList[6]->text());
  } else {
    twi = new QTableWidgetItem(tbList[6]->text());
    tw->setItem(row, 4, twi);
  }
  // tbCommentPol
  twi = tw->item(row, 6);
  if (twi != nullptr) {
    twi->setText(tbList[7]->text());
  } else {
    twi = new QTableWidgetItem(tbList[7]->text());
    tw->setItem(row, 6, twi);
  }
}

void MainForm::on_btnImportitmAdd_clicked() {
  auto tw = ui->lwImport;
  tw->insertRow(tw->rowCount());
}

void MainForm::on_btnImportitmDel_clicked() {
  auto tw = ui->lwImport;
  tw->removeRow(tw->currentRow());
}

void MainForm::on_btnImportitmClean_clicked() {
  auto tw = ui->lwImport;
  tw->clearContents();
  tw->setRowCount(0);
}

void MainForm::on_btnEnumitmAdd_clicked() {
  auto tw = ui->twListNum;
  tw->insertRow(tw->rowCount());  
  enumList.append(enumItemList());
}

void MainForm::on_btnEnumitmDel_clicked() {
  auto tw = ui->twListNum;
  tw->removeRow(tw->currentRow());  
  enumList.removeAt(tw->currentRow());
}

void MainForm::on_btnEnumitmClean_clicked() {
  auto tw = ui->twListNum;
  tw->clearContents();
  tw->setRowCount(0);  
  enumList.clear();
}

void MainForm::on_btnEnumitmAdd_2_clicked() {
  auto tw = ui->twDescpNum;
  tw->insertRow(tw->rowCount());
  int row(ui->twListNum->currentRow());
  if(row < 0) {
      return;
  }
  enumList[row].addRow();
}

void MainForm::on_btnEnumitmDel_2_clicked() {
  auto tw = ui->twDescpNum;
  tw->removeRow(tw->currentRow());
  int row(ui->twListNum->currentRow());
  if(row < 0) {
      return;
  }
  enumList[row].removeAt(row);
}

void MainForm::on_btnEnumitmClean_2_clicked() {
  auto tw = ui->twDescpNum;
  tw->clearContents();
  tw->setRowCount(0);
  int row(ui->twListNum->currentRow());
  if(row < 0) {
      return;
  }
  enumList[row].clean();
}

void MainForm::on_twListNum_clicked(const QModelIndex &index) {
  auto *tw(ui->twDescpNum);
  int row(index.row());
  int countRow(enumList.at(row).getCountPoles());
  tw->setRowCount(countRow);

  auto &st(enumList);
  loadItemTable(countRow, st, row, tw);
}



void MainForm::on_btnEnumitmSave_2_clicked() {
  auto *twL(ui->twListNum);
  auto *twD(ui->twDescpNum);
  int row(twD->currentRow());
  if((row < 0) || (twL->currentRow() < 0) ) {
      return;
  }
  auto &st = enumList[twL->currentRow()];
  saveItemTable(st, twD);
}

void MainForm::on_btnSubTypeitmAdd_clicked() {
  auto tw = ui->twSubTypeTable;
  tw->insertRow(tw->rowCount());
  int row(ui->twSubTypeList->currentRow());
  if(row < 0) {
      return;
  }
  subType[row].addRow();
}

void MainForm::on_btnSubTypeitmDel_clicked() {
  auto tw = ui->twSubTypeTable;
  tw->removeRow(tw->currentRow());
  int row(ui->twSubTypeList->currentRow());
  if(row < 0) {
      return;
  }
  subType[row].removeAt(row);
}

void MainForm::on_btnSubTypeitmClean_clicked() {
  auto tw = ui->twSubTypeTable;
  tw->clearContents();
  tw->setRowCount(0);
  int row(ui->twSubTypeList->currentRow());
  if(row < 0) {
      return;
  }
  subType[row].clear();
}

void MainForm::on_twSubTypeTable_clicked(const QModelIndex &index)
{
  QTableWidget *tw(ui->twSubTypeTable);
  int row(index.row());
  // tbNameSubType
  QTableWidgetItem *twi(tw->item(row, 0));
  if (twi != nullptr) {
    tbList[8]->setText(twi->text());
  } else {
    tbList[8]->clear();
  }
  // cbTypeSubType
  twi = tw->item(row, 1);
  if (twi != nullptr) {
    cbList[1]->setCurrentText(twi->text());
  }
  // spbSizeSubType
  twi = tw->item(row, 2);
  if (twi != nullptr) {
    spbList[1]->setValue(twi->text().toInt());
  }
  // tbCommentSubType
  twi = tw->item(row, 4);
  if (twi != nullptr) {
    tbList[9]->setText(twi->text());
  } else {
    tbList[9]->clear();
  }
}

void MainForm::on_btnSubTypeitmSave_clicked()
{
  QTableWidget *tw(ui->twSubTypeTable);
  int row(tw->currentRow());
  if((row < 0) || (ui->twSubTypeList->currentRow() < 0) ) {
      return;
  }
  auto &st = subType[ui->twSubTypeList->currentRow()];
  // tbNameSubType
  st.setNamePole(tbList[8]->text(), row);  
  // cbTypeSubType
  st.setNameType(cbList[1]->currentText(), row);  
  // spbSizeSubType
  int tmp(spbList[1]->value());
  st.setLengthPole((tmp ? tr("%1").arg(tmp) : QString("")), row);  
  //alignSize
  auto *twi = tw->item(row, 3);
  if (twi != nullptr) {
    st.setASize(twi->text(), row);
  }
  // tbCommentSubType
  st.setCommentPole(tbList[9]->text(), row);

  on_twSubTypeList_clicked(ui->twSubTypeList->currentIndex());
}

void MainForm::on_twSubTypeList_clicked(const QModelIndex &index)
{
  QTableWidget *tw(ui->twSubTypeTable);
  int row(index.row());
  int countRow(subType.at(row).getCountPoles());
  tw->setRowCount(countRow);
  auto &st(subType);
  loadItemTable(countRow, st, row, tw);

}

void MainForm::on_btnSubTypeitmAdd_2_clicked()
{
  auto tw = ui->twSubTypeList;
  tw->insertRow(tw->rowCount());
  subType.append(subTypeList());
}

void MainForm::on_btnSubTypeitmDel_2_clicked()
{
  auto tw = ui->twSubTypeList;
  tw->removeRow(tw->currentRow());
  subType.removeAt(tw->currentRow());
}

void MainForm::on_btnSubTypeitmClean_2_clicked()
{
  auto tw = ui->twSubTypeList;
  tw->clearContents();
  tw->setRowCount(0);
  subType.clear();
}


void MainForm::on_btnSubTypeitmSave_2_clicked()
{
  auto *twL(ui->twSubTypeList);
  auto *twD(ui->twSubTypeTable);
  int row(twD->currentRow());
  if((row < 0) || (twL->currentRow() < 0) ) {
      return;
  }
  auto &st = subType[twL->currentRow()];
  saveItemTable(st, twD);
}




