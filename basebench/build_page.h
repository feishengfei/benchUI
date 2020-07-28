#ifndef BUILD_PAGE_H
#define BUILD_PAGE_H

#include <QWidget>
#include "run_page.h"

namespace Ui {
class build_Page;
}

class build_Page : public QWidget
{
    Q_OBJECT

public:
    explicit build_Page(QWidget *parent = nullptr);
    ~build_Page();

private slots:
    void on_buildExitBtn_clicked();

    void on_buildContinueBtn_clicked();

    void on_buildExportBtn_clicked();

private:
    Ui::build_Page *ui;
};

#endif // BUILD_PAGE_H
