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

private slots:
    void on_cfgExitBtn_clicked();

    void on_cfgNextBtn_clicked();

    void on_cfgSelfCheck_clicked();

    void on_cfgAPICheck_clicked();

    void on_cfgLib_toolBtn_clicked();

private:
    Ui::cfg_Page *ui;
    select_Page *selectPage;

};

#endif // CFG_PAGE_H
