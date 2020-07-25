#include "conform_page.h"
#include "ui_conform_page.h"
#include <QDebug>

conform_Page::conform_Page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::conform_Page)
{
    ui->setupUi(this);
}

conform_Page::~conform_Page()
{
    delete ui;
}

void conform_Page::on_cfmPageBtn_clicked()
{
    this->close();
    buildPage = new build_Page;
    buildPage->show();
    qDebug() << "============ write configure info into run_params" << endl;
}

void conform_Page::on_cfmBackBtn_clicked()
{
    qDebug() << "============ back to set run params" << endl;
    emit sindsignal();
    //this->parentWidget()->show();
    this->close();
}
