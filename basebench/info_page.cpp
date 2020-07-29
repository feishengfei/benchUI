#include "main.h"
#include "ui_info_page.h"
#include <QGraphicsDropShadowEffect>

info_Page::info_Page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::info_Page)
{
    ui->setupUi(this);
    /*QGraphicsDropShadowEffect *effect = new QGraphicsDropShadowEffect;
    effect->setBlurRadius(8);        // 阴影圆角的大小
    effect->setColor(Qt::gray);      //阴影的颜色
    effect->setOffset(5,5);          //阴影的偏移量*/
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
