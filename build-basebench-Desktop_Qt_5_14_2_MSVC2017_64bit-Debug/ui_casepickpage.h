/********************************************************************************
** Form generated from reading UI file 'casepickpage.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CASEPICKPAGE_H
#define UI_CASEPICKPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_casepickPage
{
public:
    QListWidget *listWidget;
    QLabel *label;
    QFrame *line;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *casepickPage)
    {
        if (casepickPage->objectName().isEmpty())
            casepickPage->setObjectName(QString::fromUtf8("casepickPage"));
        casepickPage->resize(400, 300);
        listWidget = new QListWidget(casepickPage);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget);
        __qlistwidgetitem->setCheckState(Qt::Checked);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget);
        __qlistwidgetitem1->setCheckState(Qt::Checked);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(70, 60, 261, 192));
        label = new QLabel(casepickPage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(170, 20, 61, 21));
        QFont font;
        font.setPointSize(8);
        label->setFont(font);
        line = new QFrame(casepickPage);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(30, 40, 331, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        pushButton = new QPushButton(casepickPage);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(70, 260, 80, 21));
        pushButton_2 = new QPushButton(casepickPage);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(250, 260, 80, 21));

        retranslateUi(casepickPage);

        QMetaObject::connectSlotsByName(casepickPage);
    } // setupUi

    void retranslateUi(QWidget *casepickPage)
    {
        casepickPage->setWindowTitle(QCoreApplication::translate("casepickPage", "Form", nullptr));

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("casepickPage", "gl20-basic", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("casepickPage", "gl20-uniform", nullptr));
        listWidget->setSortingEnabled(__sortingEnabled);

        label->setText(QCoreApplication::translate("casepickPage", "\351\200\211\346\213\251\347\224\250\344\276\213", nullptr));
        pushButton->setText(QCoreApplication::translate("casepickPage", "Back", nullptr));
        pushButton_2->setText(QCoreApplication::translate("casepickPage", "Next", nullptr));
    } // retranslateUi

};

namespace Ui {
    class casepickPage: public Ui_casepickPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CASEPICKPAGE_H
