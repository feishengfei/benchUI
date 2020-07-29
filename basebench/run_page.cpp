#include "run_page.h"
#include "ui_run_page.h"
#include <QDesktopServices>
#include <QUrl>
#include <QProcess>
#include <QDebug>
#include <QFile>

run_Page::run_Page(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::run_Page)
{
    ui->setupUi(this);
}

run_Page::~run_Page()
{
    delete ui;
}

void run_Page::on_runFinishBtn_clicked()
{
    this->close();
}

void run_Page::on_runFolderBtn_clicked()
{
   //QDesktopServices::openUrl(QUrl("D:\\project\\test\\basebench\\result", QUrl::TolerantMode));
   QProcess::startDetached("explorer"+QString("D:\\project\\test\\basebench\\result"));
}

void run_Page::on_runSummaryBtn_clicked()
{
   // QString fileName("D:\\project\\test\\basebench\\result\\summary.xlsx");
    QString fileName("D:\\project\\test\\basebench\\result\\summary.html");
    QFile file(fileName);
    //QDesktopServices::openUrl(QUrl("http://www.baidu.com"));

    if (file.exists()) {
        QDesktopServices::openUrl(QUrl::fromLocalFile(fileName));
    }
}
