#include "main.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    infoPage = new info_Page;

    infoPage->show();

    int ret = a.exec();
    qDebug() << "App exec result: " << ret << endl;

    delete infoPage;
}
