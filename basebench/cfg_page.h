#ifndef CFG_PAGE_H
#define CFG_PAGE_H

#include <QWidget>
#include "select_page.h"

namespace Ui {
class cfg_Page;
}

class cfg_Page : public QWidget
{
    Q_OBJECT

public:
    explicit cfg_Page(QWidget *parent = nullptr);
    ~cfg_Page();
    //QStringList caselist;

    //static QString libpath;
    //static QString arch;
    //static QString outformat;
    //static QString winsys;
    QString apiversion;
    QString module;

    //static bool en_gdb;
    //static bool en_dump;

    //static QStringList runlist;
    static QMap<QString,QStringList> runlist;

private slots:
    void on_cfgExitBtn_clicked();

    void on_cfgNextBtn_clicked();

    void on_cfgSelfCheck_clicked();

    void on_cfgAPICheck_clicked();

    void on_cfgLib_toolBtn_clicked();

    void on_cfgApiverBox_currentTextChanged(const QString &arg1);

    void on_cfgModelBox_currentTextChanged(const QString &arg1);

private:
    Ui::cfg_Page *ui;
   // QString version;
    //QString module;
    void updateCaselist();
};

#endif // CFG_PAGE_H
