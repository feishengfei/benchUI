#ifndef CONFORM_PAGE_H
#define CONFORM_PAGE_H

#include <QWidget>
#include "build_page.h"

namespace Ui {
class conform_Page;
}

class conform_Page : public QWidget
{
    Q_OBJECT

public:
    explicit conform_Page(QWidget *parent = nullptr);
    ~conform_Page();

private slots:
    void on_cfmPageBtn_clicked();

    void on_cfmBackBtn_clicked();

private:
    Ui::conform_Page *ui;

};

#endif // CONFORM_PAGE_H
