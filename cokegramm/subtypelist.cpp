#include "subtypelist.h"
#include <list>

const QStringList& subTypeList::getNamePole() const { return namePole; }

void subTypeList::setNamePole(const QString& value, int i)
{
  if(i >= 0 && i < countPoles) {
      namePole.replace(i, value);
  } else {
      namePole.append(value);
      ++countPoles;
      syncCount();
  }
}

void subTypeList::setNamePole(const QStringList& value) {
  namePole = value;
}

const QStringList& subTypeList::getNameType() const { return nameType; }

void subTypeList::setNameType(const QString& value, int i)
{
  if(i >= 0 && i < countPoles) {
      nameType.replace(i, value);
  } else {
      nameType.append(value);
      ++countPoles;
      syncCount();
  }
}

void subTypeList::setNameType(const QStringList& value) { nameType = value; }

const QStringList& subTypeList::getLengthPole() const { return lengthPole; }

void subTypeList::setLengthPole(const QString& value, int i)
{
  if(i >= 0 && i < countPoles) {
      lengthPole.replace(i, value);
  } else {
      lengthPole.append(value);
      ++countPoles;
      syncCount();
  }
}

void subTypeList::setLengthPole(const QStringList& value) { lengthPole = value; }

const QStringList& subTypeList::getCommentPole() const { return commentPole; }

void subTypeList::setCommentPole(const QString& value, int i)
{
  if(i >= 0 && i < countPoles) {
      commentPole.replace(i, value);
  } else {
      commentPole.append(value);
      ++countPoles;
      syncCount();
  }
}

void subTypeList::setCommentPole(const QStringList& value) { commentPole = value; }

const QStringList& subTypeList::getASize() const { return aSize; }

void subTypeList::setASize(const QString& value, int i)
{
  if(i >= 0 && i < countPoles) {
      aSize.replace(i, value);
  } else {
      aSize.append(value);
      ++countPoles;
      syncCount();
  }
}

void subTypeList::setASize(const QStringList& value) { aSize = value; }

QStringList subTypeList::getPoleAt(int i) const
{
  switch (i)
  {
    case 0: {
      return getNamePole();
    }
    case 1: {
      return getNameType();
    }
    case 2: {
      return getLengthPole();
    }
    case 3: {
      return getASize();
    }
    case 4: {
      return getCommentPole();
    }
  }
  QStringList tmp;
  return tmp;
}

void subTypeList::setPoleAt(int i, QStringList data)
{
  switch (i)
  {
    case 0: {
      setNamePole(data);
      break;
    }
    case 1: {
      setNameType(data);
      break;
    }
    case 2: {
      setLengthPole(data);
      break;
    }
    case 3: {
      setASize(data);
      break;
    }
    case 4: {
      setCommentPole(data);
      break;
    }
  }
}

void subTypeList::setPoleAt(int column, int row, const QString data)
{
  switch (column)
  {
    case 0: {
      setNamePole(data, row);
      break;
    }
    case 1: {
      setNameType(data, row);
      break;
    }
    case 2: {
      setLengthPole(data, row);
      break;
    }
    case 3: {
      setASize(data, row);
      break;
    }
    case 4: {
      setCommentPole(data, row);
      break;
    }
  }
}

int subTypeList::getMaxCountPole() const
{
  std::list<int> tmp;
  tmp.emplace_back(namePole.length());
  tmp.emplace_back(nameType.length());
  tmp.emplace_back(lengthPole.length());
  tmp.emplace_back(commentPole.length());
  tmp.emplace_back(aSize.length());
  tmp.sort();
  return tmp.back();
}

void subTypeList::removeAt(int i)
{
  if(i > 0) {
    namePole.removeAt(i);
    nameType.removeAt(i);
    lengthPole.removeAt(i);
    commentPole.removeAt(i);
    aSize.removeAt(i);
    --countPoles;
  }
}

void subTypeList::clear()
{
  namePole.clear();
  nameType.clear();
  lengthPole.clear();
  commentPole.clear();
  aSize.clear();
  countPoles = 0;
}

void subTypeList::addRow()
{
  namePole.append("");
  nameType.append("");
  lengthPole.append("");
  commentPole.append("");
  aSize.append("");
  ++countPoles;
}

int subTypeList::getCountPoles() const
{
  return countPoles;
}

void subTypeList::syncCount()
{
  int i(0);
  for(i = namePole.length(); i < countPoles; ++i) {
      namePole.append("");
  }
  for(i = nameType.length(); i < countPoles; ++i) {
      nameType.append("");
  }
  for(i = lengthPole.length(); i < countPoles; ++i) {
      lengthPole.append("");
  }
  for(i = commentPole.length(); i < countPoles; ++i) {
      commentPole.append("");
  }
  for(i = aSize.length(); i < countPoles; ++i) {
      aSize.append("");
  }
}

subTypeList::subTypeList() :
  namePole(""), nameType(""),
  lengthPole(""), commentPole(""),
  aSize(""), countPoles(1)
{}

subTypeList::subTypeList(const subTypeList& old) :
  namePole(old.namePole), nameType(old.nameType),
  lengthPole(old.lengthPole), commentPole(old.commentPole),
  aSize(old.aSize), countPoles(old.countPoles)
{}

subTypeList& subTypeList::operator =(const subTypeList& rhs)
{
  namePole    = rhs.namePole;
  nameType    = rhs.nameType;
  lengthPole  = rhs.lengthPole;
  commentPole = rhs.commentPole;
  aSize       = rhs.aSize;
  countPoles  = rhs.countPoles;
  return *this;
}
