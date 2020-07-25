#include "info_page.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    info_Page w;
    w.show();
    return a.exec();
}
