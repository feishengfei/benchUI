/********************************************************************************
** Form generated from reading UI file 'select_page.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SELECT_PAGE_H
#define UI_SELECT_PAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_select_Page
{
public:
    QPushButton *selectBackBtn;
    QFrame *line;
    QPushButton *selectOKBtn;
    QListWidget *listWidget;
    QLabel *label;

    void setupUi(QWidget *select_Page)
    {
        if (select_Page->objectName().isEmpty())
            select_Page->setObjectName(QString::fromUtf8("select_Page"));
        select_Page->resize(490, 751);
        selectBackBtn = new QPushButton(select_Page);
        selectBackBtn->setObjectName(QString::fromUtf8("selectBackBtn"));
        selectBackBtn->setGeometry(QRect(70, 710, 91, 31));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(selectBackBtn->sizePolicy().hasHeightForWidth());
        selectBackBtn->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        selectBackBtn->setFont(font);
        line = new QFrame(select_Page);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(40, 50, 411, 20));
        sizePolicy.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy);
        line->setFont(font);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        selectOKBtn = new QPushButton(select_Page);
        selectOKBtn->setObjectName(QString::fromUtf8("selectOKBtn"));
        selectOKBtn->setGeometry(QRect(330, 710, 91, 31));
        sizePolicy.setHeightForWidth(selectOKBtn->sizePolicy().hasHeightForWidth());
        selectOKBtn->setSizePolicy(sizePolicy);
        selectOKBtn->setFont(font);
        listWidget = new QListWidget(select_Page);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget);
        __qlistwidgetitem->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget);
        __qlistwidgetitem1->setCheckState(Qt::Checked);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(70, 70, 351, 631));
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);
        listWidget->setFont(font);
        label = new QLabel(select_Page);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(220, 0, 111, 31));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);

        retranslateUi(select_Page);

        QMetaObject::connectSlotsByName(select_Page);
    } // setupUi

    void retranslateUi(QWidget *select_Page)
    {
        select_Page->setWindowTitle(QCoreApplication::translate("select_Page", "Form", nullptr));
        selectBackBtn->setText(QCoreApplication::translate("select_Page", "Back", nullptr));
        selectOKBtn->setText(QCoreApplication::translate("select_Page", "OK", nullptr));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("select_Page", "gl20-basic", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("select_Page", "gl20-uniform", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled);

        label->setText(QCoreApplication::translate("select_Page", "\351\200\211\346\213\251\347\224\250\344\276\213", nullptr));
    } // retranslateUi

};

namespace Ui {
    class select_Page: public Ui_select_Page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELECT_PAGE_H
