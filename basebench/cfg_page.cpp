#include "main.h"
#include "cfg_page.h"
#include "ui_cfg_page.h"
#include <QDir>
#include <QFileDialog>

cfg_Page::cfg_Page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cfg_Page)
{
    ui->setupUi(this);
    ui->lineEdit->setText(libpath);
    en_gdb ? ui->cfgGdbBox->setCheckState(Qt::Checked) : ui->cfgGdbBox->setCheckState(Qt::Unchecked);
    en_dump ? ui->cfgDumpBox->setCheckState(Qt::Checked) : ui->cfgDumpBox->setCheckState(Qt::Unchecked);
    ui->configArchBox->setCurrentText(arch);
    ui->configOutformBox->setCurrentText(outformat);
    ui->cfgApiverBox->setCurrentText(apiversion);
    ui->cfgModelBox->setCurrentText(module);
    ui->cfgWinsysBox->setCurrentText(winsys);
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
    libpath = ui->lineEdit->text();
    en_gdb = ui->cfgGdbBox->isChecked();  // ture / false
    en_dump = ui->cfgDumpBox->isChecked();
    arch = ui->configArchBox->currentText();
    outformat = ui->configOutformBox->currentText();
    winsys = ui->cfgWinsysBox->currentText();
    apiversion = ui->cfgApiverBox->currentText();
    module = ui->cfgModelBox->currentText();
    cfmPage = new conform_Page;
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

void cfg_Page::on_cfgLib_toolBtn_clicked()
{
    QString directory = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this,tr("save path"),QDir::currentPath()));
    if(!directory.isEmpty())
    {
        ui->lineEdit->setText(directory);
    }
}
