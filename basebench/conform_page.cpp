#include "main.h"
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
    this->close();
    qDebug() << "============ back to set run params" << endl;
    cfg = new cfg_Page;
    cfg->show();
    //this->parentWidget()->show();
}
