#include "build_page.h"
#include "ui_build_page.h"
#include <QFileDialog>
#include <QDebug>

build_Page::build_Page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::build_Page)
{
    ui->setupUi(this);
}

build_Page::~build_Page()
{
    delete ui;
}

void build_Page::on_buildExitBtn_clicked()
{
    this->close();
}

void build_Page::on_buildContinueBtn_clicked()
{
    this->close();
    runPage = new run_Page;
    runPage->show();
}

void build_Page::on_buildExportBtn_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Open Config"),
            "",
            tr("Config Files (*.txt)"));

        if (!fileName.isNull())
        {
            qDebug() << "------------------ Save File: " << fileName << endl;
        }
        else
        {
            qDebug() << "------------------ Cancel " << endl;
        }
}
