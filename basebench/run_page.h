#ifndef RUN_PAGE_H
#define RUN_PAGE_H

#include <QWidget>

namespace Ui {
class run_Page;
}

class run_Page : public QWidget
{
    Q_OBJECT

public:
    explicit run_Page(QWidget *parent = nullptr);
    ~run_Page();

private slots:
    void on_runFinishBtn_clicked();

    void on_runFolderBtn_clicked();

    void on_runSummaryBtn_clicked();

private:
    Ui::run_Page *ui;
};

#endif // RUN_PAGE_H
