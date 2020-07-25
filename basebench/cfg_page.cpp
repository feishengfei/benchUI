#include "cfg_page.h"
#include "ui_cfg_page.h"

cfg_Page::cfg_Page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cfg_Page)
{
    ui->setupUi(this);
}

cfg_Page::~cfg_Page()
{
    delete ui;
}

void cfg_Page::on_cfgExitBtn_clicked()
{
    this->close();
}

void cfg_Page::on_cfgNextBtn_clicked()
{
    cfmPage = new conform_Page;
    //connect(cfmPage, SIGNAL(sendsignal()),this,SLOT(reshow()));
    cfmPage->show();
    this->hide();
}

void cfg_Page::on_cfgSelfCheck_clicked()
{
    if(ui->cfgSelfCheck->isChecked()) {
        selectPage = new select_Page;
        selectPage->show();
    }
}

void cfg_Page::on_cfgAPICheck_clicked()
{
    if(ui->cfgAPICheck->isChecked()) {
        selectPage = new select_Page;
        selectPage->show();
    }
}

void cfg_Page::reshow()
{
    this->show();
}
