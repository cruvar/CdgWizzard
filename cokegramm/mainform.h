#ifndef MAINFORM_H
#define MAINFORM_H

#include "subtypelist.h"
#include "enumitemlist.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QTableWidget>

namespace Ui {
class MainForm;
}

class MainForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainForm(QWidget *parent = 0);
    ~MainForm();

private slots:
    void on_btnitmAdd_clicked();

    void on_btnitmDel_clicked();

    void on_btnitmClean_clicked();

    void on_actionExportJSON_triggered();

    void on_twType_clicked(const QModelIndex &index);

    void on_btnImportitmAdd_clicked();

    void on_btnImportitmDel_clicked();

    void on_btnImportitmClean_clicked();

    void on_btnEnumitmAdd_clicked();

    void on_btnEnumitmDel_clicked();

    void on_btnEnumitmClean_clicked();

    void on_btnEnumitmAdd_2_clicked();

    void on_btnEnumitmDel_2_clicked();

    void on_btnEnumitmClean_2_clicked();

    void on_twListNum_clicked(const QModelIndex &index);

    void on_btnEnumitmSave_2_clicked();

    void on_btnitmSave_clicked();

    void on_btnSubTypeitmAdd_clicked();

    void on_btnSubTypeitmDel_clicked();

    void on_btnSubTypeitmClean_clicked();

    void on_twSubTypeTable_clicked(const QModelIndex &index);

    void on_btnSubTypeitmSave_clicked();

    /*
    void addTypeList(int tab);
    void delTypeList(int tab);
    */

    void on_twSubTypeList_clicked(const QModelIndex &index);

    void on_btnSubTypeitmAdd_2_clicked();

    void on_btnSubTypeitmDel_2_clicked();

    void on_btnSubTypeitmClean_2_clicked();

    void on_btnSubTypeitmSave_2_clicked();

private:
    Ui::MainForm *ui;
    QList<QLineEdit*> tbList;
    QList<QComboBox*> cbList;
    QList<QSpinBox*>  spbList;
    QHash<QString, int> typeList;
    int userType;
    QList<subTypeList> subType;
    QList<enumItemList> enumList;
};
template <class T1, class T2>
void saveItemTable(T1 &st, T2 *&twD)
{
  QTableWidgetItem *itm(nullptr);
  for (int i(0), maxI(twD->rowCount()), j, maxJ(twD->columnCount());
       i < maxI; ++i)
  {
    for(j = 0; j < maxJ; ++j) {
      itm = twD->item(i, j);
      if(itm != nullptr) {
        st.setPoleAt(j, i, itm->text());
      }
    }
  }
}
template <class T1>
void loadItemTable(int& countRow, T1 &st, int& row, QTableWidget *&tw)
{
  QTableWidgetItem *twi(nullptr);
  QStringList tmpList;
  for(int i(0), maxI(tw->columnCount()), j; i < maxI; ++i)
  {
    for(j = 0; j < countRow; ++j) {
      tmpList = st.at(row).getPoleAt(i);
      twi = tw->item(j, i);
      if (twi != nullptr) {
        twi->setText(tmpList.at(j));
      } else {
        twi = new QTableWidgetItem(tmpList.at(j));
        tw->setItem(j, i, twi);
      }
    }
  }
}

#endif // MAINFORM_H
