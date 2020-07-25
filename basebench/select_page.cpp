#include "select_page.h"
#include "ui_select_page.h"
#include <QDebug>

select_Page::select_Page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::select_Page)
{
    ui->setupUi(this);
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
