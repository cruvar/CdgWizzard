#include "lib.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QList>
#include <QLineEdit>

void doubOrStr(QString tmp, const QString &str, QJsonObject& valuesEnum)
{
  bool ok(false);
  double d(str.toDouble(&ok));
  if (ok) {
    valuesEnum[tmp] = QJsonValue(d);
  } else {
    valuesEnum[tmp] = QJsonValue(str);
  }
}

void writeJsonGeneral(QJsonObject& saveObject, QList<QLineEdit*>& tbList,
                      QTableWidget*& tw)
{
  saveObject["typename"] = tbList.at(0)->text();
  saveObject["typeCode"] = tbList.at(1)->text();
  saveObject["group"]    = tbList.at(2)->text();
  saveObject["version"]  = tbList.at(3)->text();
  QJsonArray imports;
  QTableWidgetItem *itm(nullptr);
  for (int i(0), maxI(tw->rowCount()); i < maxI; ++i) {
    itm = tw->item(i, 0);
    if (itm != nullptr) {
      imports.append(QJsonValue(itm->text()));
    }
  }
  if(!imports.isEmpty()) {
    saveObject["imports"] = imports;
  }
}

void writeJsonEnum(QJsonObject& saveObject, QTableWidget*& twLN,
                   QList<enumItemList>& enumList)
{
  QJsonArray enumArray;
  QTableWidgetItem *twi(nullptr);
  QString tmp;
  for (int i(0), maxI(twLN->rowCount()), j, maxJ; i < maxI; ++i)
  {
    auto &sList(enumList.at(i));
    QJsonObject valuesEnum;
    QJsonObject enumArrayItem;
    for(j = 0, maxJ = sList.getCountPoles(); j < maxJ; ++j )
    {
      tmp = ((sList.key(j).isEmpty()) ? QObject::tr("el_%1").arg(j) : sList.key(j));
      doubOrStr(tmp, sList.value(j), valuesEnum);
    }
    twi = twLN->item(i, 0);
    if (twi == nullptr) {
      enumArrayItem[QObject::tr("enum_%1").arg(i)] = valuesEnum;
    } else {
      enumArrayItem[twi->text()] = valuesEnum;
    }
    enumArray.append(QJsonValue(enumArrayItem));
  }
  if(!enumArray.isEmpty()) {
    saveObject["enum"] = enumArray;
  }
}

void writeJsonDescript(QJsonObject& saveObject, QTableWidget*& tw) {
  QJsonArray fieldsArray;
  QTableWidgetItem *twi(nullptr);
  QString str;
  for (int i(0), maxI(tw->rowCount()),
       j, maxJ(tw->columnCount()); i < maxI; ++i)
  {
    QJsonObject valuesItem;
    QJsonObject ArrayItem;
    for (j = 1; j < maxJ; ++j)
    {
      twi = tw->item(i, j);
      if (twi != nullptr) {
        if (!twi->text().isEmpty()) {
          str = twi->text();
          doubOrStr(tw->horizontalHeaderItem(j)->text(), str, valuesItem);
        }
      }
    }
    twi = tw->item(i, 0);
    if ((twi != nullptr) && (!twi->text().isEmpty())) {
      ArrayItem[twi->text()] = QJsonValue(valuesItem);
    } else {
      ArrayItem[QObject::tr("row_%1").arg(i + 1)] = QJsonValue(valuesItem);
    }
    fieldsArray.append(ArrayItem);
  }
  if(!fieldsArray.isEmpty()) {
    saveObject["fields"] = fieldsArray;
  }
}

void writeJsonSubType(QJsonObject& saveObject, QTableWidget*& twST, QTableWidget*& twTable, QList<subTypeList>& subType)
{
  int rowP(0), maxRowP(0), columnP(0), maxColumnP(twTable->columnCount());

  QJsonArray subTypeArray;
  for (int i(0), maxI(twST->rowCount()); i < maxI; ++i)
  {
    QJsonObject valuesItem;
    QJsonArray fieldsArray;
    auto &spTmp(subType.at(i));

    for(rowP = 0, maxRowP = spTmp.getCountPoles();
        rowP < maxRowP; ++rowP)
    {
      QJsonObject valuesPole;
      QJsonObject ArrayPole;
      for(columnP = 1; columnP < maxColumnP; ++columnP)
      {
        auto &str(spTmp.getPoleAt(columnP).at(rowP));
        if(!str.isEmpty())
        {
          doubOrStr(twTable->horizontalHeaderItem(columnP)->text(),
                    str, valuesPole);
        }
      }
      if(spTmp.getNamePole().at(rowP).isEmpty()) {
        ArrayPole[QObject::tr("supType_%1").arg(rowP + 1)] = QJsonValue(valuesPole);
      } else {
        ArrayPole[spTmp.getNamePole().at(rowP)] = QJsonValue(valuesPole);
      }
      fieldsArray.append(QJsonValue(ArrayPole));
    }
    valuesItem["typename"] = twST->item(i, 0)->text();
    valuesItem["fields"] = QJsonValue(fieldsArray);
    subTypeArray.append(valuesItem);
  }
  if(!subTypeArray.isEmpty()) {
    saveObject["subtypes"] = subTypeArray;
  }
}
