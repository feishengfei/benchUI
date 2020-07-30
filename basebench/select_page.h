#ifndef SELECT_PAGE_H
#define SELECT_PAGE_H
#include "cfg_page.h"
#include <QWidget>
#include <QTreeWidgetItem>

namespace Ui {
class select_Page;
}

class select_Page : public QWidget
{
    Q_OBJECT

public:
    select_Page(QString title, QWidget *parent = nullptr);
    ~select_Page();
    void updateParentItem(QTreeWidgetItem* item);
    void init();

private slots:
    void on_selectOKBtn_clicked();

    void on_selectBackBtn_clicked();

    void treeItemChanged(QTreeWidgetItem* Item, int column);

private:
    Ui::select_Page *ui;
};

#endif // SELECT_PAGE_H
