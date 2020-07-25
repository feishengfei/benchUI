#ifndef SELECT_PAGE_H
#define SELECT_PAGE_H

#include <QWidget>

namespace Ui {
class select_Page;
}

class select_Page : public QWidget
{
    Q_OBJECT

public:
    explicit select_Page(QWidget *parent = nullptr);
    ~select_Page();

private slots:
    void on_selectOKBtn_clicked();

    void on_selectBackBtn_clicked();

private:
    Ui::select_Page *ui;
};

#endif // SELECT_PAGE_H
