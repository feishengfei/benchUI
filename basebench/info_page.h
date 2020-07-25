#ifndef INFO_PAGE_H
#define INFO_PAGE_H

#include <QWidget>
#include "cfg_page.h"

namespace Ui {
class info_Page;
}

class info_Page : public QWidget
{
    Q_OBJECT

public:
    explicit info_Page(QWidget *parent = nullptr);
    ~info_Page();

private slots:
    void on_descriptionStartButton_clicked();

private:
    Ui::info_Page *ui;
    cfg_Page *cfg;
};

#endif // INFO_PAGE_H
