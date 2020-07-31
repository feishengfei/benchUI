#include "main.h"
#include "cfg_page.h"
#include "ui_cfg_page.h"
#include <QDir>
#include <QFileDialog>

cfg_Page::cfg_Page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::cfg_Page)
{
    apiversion = QString("gl43");
    module = QString("coverage");

    ui->setupUi(this);
    ui->lineEdit->setText(GB_CFG::libpath);
    GB_CFG::en_gdb ? ui->cfgGdbBox->setCheckState(Qt::Checked) : ui->cfgGdbBox->setCheckState(Qt::Unchecked);
    GB_CFG::en_dump ? ui->cfgDumpBox->setCheckState(Qt::Checked) : ui->cfgDumpBox->setCheckState(Qt::Unchecked);
    ui->configArchBox->setCurrentText(GB_CFG::arch);
    ui->configOutformBox->setCurrentText(GB_CFG::outformat);
    ui->cfgApiverBox->setCurrentText(apiversion);
    ui->cfgModelBox->setCurrentText(module);
    ui->cfgWinsysBox->setCurrentText(GB_CFG::winsys);

    updateCaselist();
}

cfg_Page::~cfg_Page()
{
    delete ui;
}

void cfg_Page::updateCaselist()
{
    // 直接用version和module
    QString dir = "D:\\project\\test\\basebench\\samples\\" + module;
    QDir qd(dir);

    runlist.clear();
    //GB_CFG::runlist.append(runlist);

    //QString s=ui->tableWidget->item(j,0)->text();//取出字符串
    QString verstr("gl14,gl15,gl20,gl21,gl22,gl30,gl31,gl32,gl33,gl40,gl41,gl42,gl43,gl45,gl46");
    QStringList versionlist = verstr.split(",");
    QString modulestr("coverage,limit,function,storage,shader,error");
    QStringList modulelist = verstr.split(",");

    for(auto iter = versionlist.begin(); iter != versionlist.end(); ++iter)
    {
        runlist.insert(*iter, QStringList());
        if(*iter == apiversion) break;
    }
    //加载目录下所有文件，可以添加过滤
    QFileInfoList subfilelist = qd.entryInfoList(QDir::Files | QDir::CaseSensitive);

    for (int i = 0;i < subfilelist.size(); i++)
    {
        QString suffix = subfilelist[i].suffix();
        if (suffix.compare("cpp") == 0)
        {
            QString qs;
            qs.append(qPrintable(subfilelist[i].baseName()));
            qs.remove("\n");
            QString prefix = qs.split("-")[0];
            if(runlist.contains(prefix)) {
                runlist[prefix].append(qs);
            }
//            if(qs.startsWith(prefix,Qt::CaseSensitive)){
//                //GB_CFG::runlist.append(qs);
//                runlist << qs;
//            }
        }
    }
}

void cfg_Page::on_cfgExitBtn_clicked()
{
    this->close();
}

void cfg_Page::on_cfgNextBtn_clicked()
{
    GB_CFG::libpath = ui->lineEdit->text();
    GB_CFG::en_gdb = ui->cfgGdbBox->isChecked();  // ture / false
    GB_CFG::en_dump = ui->cfgDumpBox->isChecked();
    GB_CFG::arch = ui->configArchBox->currentText();
    GB_CFG::outformat = ui->configOutformBox->currentText();
    GB_CFG::winsys = ui->cfgWinsysBox->currentText();
    apiversion = ui->cfgApiverBox->currentText();
    module = ui->cfgModelBox->currentText();

    cfmPage = new conform_Page;
    cfmPage->show();
    this->hide();
}

void cfg_Page::on_cfgSelfCheck_clicked()
{
    selectPage = new select_Page(QString("select testcase"));
    selectPage->show();
}

void cfg_Page::on_cfgAPICheck_clicked()
{
    selectPage = new select_Page(QString("select API"));
    selectPage->show();
}

void cfg_Page::on_cfgLib_toolBtn_clicked()
{
    QString directory = QDir::toNativeSeparators(QFileDialog::getExistingDirectory(this,tr("save path"),QDir::currentPath()));
    if(!directory.isEmpty())
    {
        ui->lineEdit->setText(directory);
    }
}

void cfg_Page::on_cfgApiverBox_currentTextChanged(const QString &arg1)
{
    apiversion = arg1;
    updateCaselist();
}

void cfg_Page::on_cfgModelBox_currentTextChanged(const QString &arg1)
{
    module = arg1;
    updateCaselist();
}
