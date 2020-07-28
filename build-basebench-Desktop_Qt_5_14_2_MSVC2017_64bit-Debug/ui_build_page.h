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
        build_Page->setAutoFillBackground(true);
        buildExitBtn = new QPushButton(build_Page);
        buildExitBtn->setObjectName(QString::fromUtf8("buildExitBtn"));
        buildExitBtn->setGeometry(QRect(460, 350, 91, 31));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(buildExitBtn->sizePolicy().hasHeightForWidth());
        buildExitBtn->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        buildExitBtn->setFont(font);
        buildExitBtn->setAutoFillBackground(true);
        textBrowser = new QTextBrowser(build_Page);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(50, 60, 501, 271));
        sizePolicy.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy);
        textBrowser->setFont(font);
        textBrowser->setAutoFillBackground(true);
        label = new QLabel(build_Page);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(290, 0, 91, 41));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(16);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        label->setAutoFillBackground(true);
        buildContinueBtn = new QPushButton(build_Page);
        buildContinueBtn->setObjectName(QString::fromUtf8("buildContinueBtn"));
        buildContinueBtn->setGeometry(QRect(250, 350, 91, 31));
        sizePolicy.setHeightForWidth(buildContinueBtn->sizePolicy().hasHeightForWidth());
        buildContinueBtn->setSizePolicy(sizePolicy);
        buildContinueBtn->setFont(font);
        buildContinueBtn->setAutoFillBackground(true);
        buildExportBtn = new QPushButton(build_Page);
        buildExportBtn->setObjectName(QString::fromUtf8("buildExportBtn"));
        buildExportBtn->setGeometry(QRect(50, 350, 91, 31));
        sizePolicy.setHeightForWidth(buildExportBtn->sizePolicy().hasHeightForWidth());
        buildExportBtn->setSizePolicy(sizePolicy);
        buildExportBtn->setFont(font);
        buildExportBtn->setAutoFillBackground(true);
        line = new QFrame(build_Page);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(40, 40, 521, 16));
        sizePolicy.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy);
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setPointSize(8);
        line->setFont(font2);
        line->setAutoFillBackground(true);
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
"</style></head><body style=\" font-family:'\345\276\256\350\275\257\351\233\205\351\273\221'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">\350\276\223\345\207\272\347\274\226\350\257\221\346\211\223\345\215\260\344\277\241\346\201\257\357\274\214\345\211\215\351\235\242\346\211\223\345\215\260\351\230\266\346\256\265</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">[15%]cmake configure</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-inden"
                        "t:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">[100%]make</span></p></body></html>", nullptr));
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
