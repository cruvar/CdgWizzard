#ifndef LIB_H
#define LIB_H

#include "subtypelist.h"
#include "enumitemlist.h"

#include <QTableWidget>
#include <QJsonObject>

void writeJsonGeneral(QJsonObject &saveObject,  QList<QLineEdit*>& tbList,
                      QTableWidget *&tw);

void writeJsonEnum(QJsonObject &saveObject, QTableWidget *&twLN,
                   QList<enumItemList>& enumList);

void writeJsonDescript(QJsonObject &saveObject, QTableWidget*& tw);

void writeJsonSubType(QJsonObject &saveObject, QTableWidget*& twST,
                      QTableWidget*& twTable, QList<subTypeList>& subType);

void doubOrStr(QString tmp, const QString &str, QJsonObject& valuesEnum);

#endif // LIB_H
