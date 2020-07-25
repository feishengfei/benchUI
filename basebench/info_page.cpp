#include "info_page.h"
#include "ui_info_page.h"

info_Page::info_Page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::info_Page)
{
    ui->setupUi(this);
}

info_Page::~info_Page()
{
    delete ui;
}

void info_Page::on_descriptionStartButton_clicked()
{
    cfg = new cfg_Page;
    cfg->show();
    this->close();
}
