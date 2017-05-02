#include "enumitemlist.h"

const QStringList& enumItemList::getKeysEnum() const
{
  return keysEnum;
}

int enumItemList::getCountPoles() const
{
    return countPoles;
}

void enumItemList::syncCount()
{
    int i(0);
    for(i = keysEnum.length(); i < countPoles; ++i) {
    keysEnum.append("");
  }
  for(i = valuesEnum.length(); i < countPoles; ++i) {
    valuesEnum.append("");
  }
}

void enumItemList::setKeysEnum(const QStringList &value)
{
  keysEnum = value;
}

const QStringList& enumItemList::getValuesEnum() const
{
  return valuesEnum;
}

QStringList enumItemList::getPoleAt(int i) const
{
  switch (i)
  {
    case 0: {
      return getKeysEnum();
    }
    case 1: {
      return getValuesEnum();
    }
  }

  QStringList tmp;
  return tmp;
}

void enumItemList::setPoleAt(int column, int row, const QString data)
{
  switch (column)
  {
    case 0: {
      setKey(data, row);
      break;
    }
    case 1: {
      setValue(data, row);
      break;
    }
  }
}

void enumItemList::removeAt(int i)
{
  if(i > 0) {
    keysEnum.removeAt(i);
    valuesEnum.removeAt(i);
    --countPoles;
  }
}

void enumItemList::clean()
{
  keysEnum.clear();
  valuesEnum.clear();
  countPoles = 0;
}

void enumItemList::addRow()
{
  keysEnum.append("");
  valuesEnum.append("");
  ++countPoles;
}

void enumItemList::setValuesEnum(const QStringList &value)
{
  valuesEnum = value;
}

enumItemList::enumItemList() : keysEnum(""), valuesEnum(""), countPoles(1) {}

enumItemList::enumItemList(const enumItemList &old)
  : keysEnum(old.keysEnum), valuesEnum(old.valuesEnum),
      countPoles(old.countPoles) {}

enumItemList::enumItemList(const QString key, const QString value) :
  keysEnum(key), valuesEnum(value), countPoles(1)
{

}

enumItemList &enumItemList::operator=(const enumItemList &rhs) {
  keysEnum = rhs.keysEnum;
  valuesEnum = rhs.valuesEnum;
  countPoles = rhs.countPoles;
  return *this;
}

const QString& enumItemList::key(int i) const { return keysEnum.at(i); }

const QString& enumItemList::value(int i) const { return valuesEnum.at(i); }

void enumItemList::setKey(const QString key, int i)
{
  if(i >= 0 && i < countPoles) {
      keysEnum.replace(i, key);
  } else {
      keysEnum.append(key);
      ++countPoles;
      syncCount();
  }
}

void enumItemList::setValue(const QString value, int i)
{
  if(i >= 0 && i < countPoles) {
      valuesEnum.replace(i, value);
  } else {
      valuesEnum.append(value);
      ++countPoles;
      syncCount();
  }
}
