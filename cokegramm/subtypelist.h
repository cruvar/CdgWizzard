#ifndef SUBTYPELIST_H
#define SUBTYPELIST_H

#include <QString>
#include <QStringList>

class subTypeList
{
private:
    //0
    QStringList namePole;
    QStringList nameType;
    QStringList lengthPole;
    //3
    QStringList commentPole;
    QStringList aSize;

    int countPoles;
protected:
    void syncCount();

    //dev
    void setPoleAt(int i, QStringList data);
    void setNamePole(const QStringList& value);
    void setNameType(const QStringList &value);
    void setCommentPole(const QStringList &value);
    void setASize(const QStringList &value);
    void setLengthPole(const QStringList &value);

public:
    subTypeList();
    subTypeList(const subTypeList& old);

    subTypeList& operator =(const subTypeList& rhs);

    const QStringList& getNamePole() const;
    void setNamePole(const QString &value, int i);

    const QStringList& getNameType() const;
    void setNameType(const QString &value, int i);

    const QStringList& getLengthPole() const;
    void setLengthPole(const QString &value, int i);

    const QStringList& getCommentPole() const;
    void setCommentPole(const QString &value, int i);

    const QStringList& getASize() const;
    void setASize(const QString &value, int i);

    QStringList getPoleAt(int i) const;
    void setPoleAt(int column, int row, const QString data);
    int getMaxCountPole() const;

    void removeAt(int i);
    void clear();
    void addRow();
    int getCountPoles() const;
};


#endif // SUBTYPELIST_H
