#ifndef ENUMITEMLIST_H
#define ENUMITEMLIST_H
#include <QString>
#include <QStringList>

class enumItemList
{
private:
    QStringList keysEnum;
    QStringList valuesEnum;
    int countPoles;
protected:
    void syncCount();

    //dev
    void setKeysEnum(const QStringList& value);
    void setValuesEnum(const QStringList& value);

public:
    enumItemList();
    enumItemList(const enumItemList& old);
    enumItemList(const QString key, const QString value);

    enumItemList& operator =(const enumItemList &rhs);

    const QString& key(int i) const;
    const QString& value(int i) const;

    void setKey(const QString key, int i);
    void setValue(const QString value,int i);

    const QStringList& getKeysEnum() const;
    const QStringList& getValuesEnum() const;

    QStringList getPoleAt(int i) const;
    void setPoleAt(int column, int row, const QString data);

    void removeAt(int i);
    void clean();
    void addRow();
    int getCountPoles() const;
};


#endif // ENUMITEMLIST_H
