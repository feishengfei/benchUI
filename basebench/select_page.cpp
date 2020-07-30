#include "main.h"
#include "select_page.h"
#include "ui_select_page.h"
#include <QDebug>
#include <QDir>
#include <QFile>

QStringList cfg_Page::runlist;
QString cfg_Page::apiversion;
QString cfg_Page::module;

void select_Page::init()
{
    //add init item
    ui->treeWidget->clear();

    QTreeWidgetItem* group = new QTreeWidgetItem(ui->treeWidget);
    group->setText(0,cfg_Page::apiversion);
    group->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group->setCheckState(0,Qt::Checked);

    for (int i = 0;i < cfg_Page::runlist.size(); i++)
    {
        QTreeWidgetItem* subItem = new QTreeWidgetItem(group);
        subItem->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
        subItem->setText(0,cfg_Page::runlist[i]);
        subItem->setCheckState(0,Qt::Checked);
    }
}

select_Page::select_Page(QString title,  QWidget *parent) :
    QWidget(parent),
    ui(new Ui::select_Page)
{
    ui->setupUi(this);

    ui->treeWidget->setHeaderLabel(title);
    init();
    connect(ui->treeWidget,SIGNAL(itemChanged(QTreeWidgetItem*,int)),this,SLOT(treeItemChanged(QTreeWidgetItem*,int)));
}

select_Page::~select_Page()
{
    delete ui;
}

void select_Page::on_selectOKBtn_clicked()
{
    this->close();
    qDebug() << "------------------- write into runlist" << endl;
}

void select_Page::on_selectBackBtn_clicked()
{
    this->close();
    qDebug() << "------------------- do not write into runlist" << endl;
}

void select_Page::treeItemChanged(QTreeWidgetItem* item, int column)
{
    if(Qt::Checked == item->checkState(0))
    {
        int count = item->childCount();
        if(count >0)
        {
            for(int i=0; i<count; i++)
            {
                item->child(i)->setCheckState(0,Qt::Checked);
            }
        }
        else
        {
            updateParentItem(item);
        }
     }
    else if(Qt::Unchecked == item->checkState(0))
    {
        int count = item->childCount();
        if(count > 0)
        {
            for(int i=0; i<count; i++)
            {
                item->child(i)->setCheckState(0,Qt::Unchecked);
            }
        }
        else
        {
            updateParentItem(item);
        }
    }
}

void select_Page::updateParentItem(QTreeWidgetItem* item)
{
    QTreeWidgetItem *parent = item->parent();
    if(parent == NULL)
    {
        return ;
    }
    int selectedCount = 0;
    int childCount = parent->childCount();
    for(int i=0; i<childCount; i++)
    {
        QTreeWidgetItem* childItem = parent->child(i);
        if(childItem->checkState(0) == Qt::Checked)
        {
            selectedCount++;
        }
        else
        {
            cfg_Page::runlist.removeOne(childItem->text(0));
        }
    }
    if(selectedCount <= 0)  //如果没有子项被选中，父项设置为未选中状态
    {
        parent->setCheckState(0,Qt::Unchecked);
    }
    else if(selectedCount>0 && selectedCount<childCount)    //如果有部分子项被选中，父项设置为部分选中状态，即用灰色显示
    {
        parent->setCheckState(0,Qt::PartiallyChecked);
    }
    else if(selectedCount == childCount)    //如果子项全部被选中，父项则设置为选中状态
    {
        parent->setCheckState(0,Qt::Checked);
    }
}
