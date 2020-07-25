/********************************************************************************
** Form generated from reading UI file 'build_page.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUILD_PAGE_H
#define UI_BUILD_PAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_build_Page
{
public:
    QPushButton *buildExitBtn;
    QTextBrowser *textBrowser;
    QLabel *label;
    QPushButton *buildContinueBtn;
    QPushButton *buildExportBtn;
    QFrame *line;

    void setupUi(QWidget *build_Page)
    {
        if (build_Page->objectName().isEmpty())
            build_Page->setObjectName(QString::fromUtf8("build_Page"));
        build_Page->resize(600, 400);
        buildExitBtn = new QPushButton(build_Page);
        buildExitBtn->setObjectName(QString::fromUtf8("buildExitBtn"));
        buildExitBtn->setGeometry(QRect(370, 350, 80, 21));
        QFont font;
        font.setPointSize(10);
        buildExitBtn->setFont(font);
        textBrowser = new QTextBrowser(build_Page);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(50, 60, 501, 271));
        label = new QLabel(build_Page);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(290, 10, 41, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(11);
        font1.setBold(false);
        font1.setWeight(50);
        label->setFont(font1);
        buildContinueBtn = new QPushButton(build_Page);
        buildContinueBtn->setObjectName(QString::fromUtf8("buildContinueBtn"));
        buildContinueBtn->setGeometry(QRect(250, 350, 80, 21));
        buildContinueBtn->setFont(font);
        buildExportBtn = new QPushButton(build_Page);
        buildExportBtn->setObjectName(QString::fromUtf8("buildExportBtn"));
        buildExportBtn->setGeometry(QRect(130, 350, 80, 21));
        buildExportBtn->setFont(font);
        line = new QFrame(build_Page);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(40, 40, 521, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        retranslateUi(build_Page);

        QMetaObject::connectSlotsByName(build_Page);
    } // setupUi

    void retranslateUi(QWidget *build_Page)
    {
        build_Page->setWindowTitle(QCoreApplication::translate("build_Page", "Form", nullptr));
        buildExitBtn->setText(QCoreApplication::translate("build_Page", "Exit", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("build_Page", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:6pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">\350\276\223\345\207\272\347\274\226\350\257\221\346\211\223\345\215\260\344\277\241\346\201\257\357\274\214\345\211\215\351\235\242\346\211\223\345\215\260\351\230\266\346\256\265</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\">[15%]cmake configure</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:10pt;\""
                        ">[100%]make</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("build_Page", "\347\274\226\350\257\221", nullptr));
        buildContinueBtn->setText(QCoreApplication::translate("build_Page", "Conitnue", nullptr));
        buildExportBtn->setText(QCoreApplication::translate("build_Page", "Export log", nullptr));
    } // retranslateUi

};

namespace Ui {
    class build_Page: public Ui_build_Page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUILD_PAGE_H
