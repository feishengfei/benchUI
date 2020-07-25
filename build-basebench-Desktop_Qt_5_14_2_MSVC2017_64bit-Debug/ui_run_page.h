/********************************************************************************
** Form generated from reading UI file 'run_page.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RUN_PAGE_H
#define UI_RUN_PAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_run_Page
{
public:
    QTextBrowser *textBrowser;
    QFrame *line;
    QLabel *label;
    QPushButton *runFinishBtn;
    QPushButton *runSummaryBtn;
    QPushButton *runFolderBtn;

    void setupUi(QWidget *run_Page)
    {
        if (run_Page->objectName().isEmpty())
            run_Page->setObjectName(QString::fromUtf8("run_Page"));
        run_Page->resize(600, 400);
        textBrowser = new QTextBrowser(run_Page);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(40, 60, 521, 291));
        QFont font;
        font.setPointSize(10);
        textBrowser->setFont(font);
        line = new QFrame(run_Page);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(30, 40, 541, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label = new QLabel(run_Page);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(270, 10, 51, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        label->setFont(font1);
        runFinishBtn = new QPushButton(run_Page);
        runFinishBtn->setObjectName(QString::fromUtf8("runFinishBtn"));
        runFinishBtn->setGeometry(QRect(470, 360, 91, 31));
        runFinishBtn->setFont(font);
        runSummaryBtn = new QPushButton(run_Page);
        runSummaryBtn->setObjectName(QString::fromUtf8("runSummaryBtn"));
        runSummaryBtn->setGeometry(QRect(40, 360, 101, 31));
        runSummaryBtn->setFont(font);
        runFolderBtn = new QPushButton(run_Page);
        runFolderBtn->setObjectName(QString::fromUtf8("runFolderBtn"));
        runFolderBtn->setGeometry(QRect(250, 360, 101, 31));
        runFolderBtn->setFont(font);

        retranslateUi(run_Page);

        QMetaObject::connectSlotsByName(run_Page);
    } // setupUi

    void retranslateUi(QWidget *run_Page)
    {
        run_Page->setWindowTitle(QCoreApplication::translate("run_Page", "Form", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("run_Page", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\277\220\350\241\214\350\277\207\347\250\213\345\222\214\347\273\223\346\236\234\345\261\225\347\244\272</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\230\276\347\244\272\346\210\220\350\241\250\346\240\274\345\222\214\345\210\227\350\241\250\345\275\242\345\274\217\357\274\214\347\224\250\344\276\213/API\345\220\216\351\235\242\345\270\246\344\270\212\350\266\205\351\223\276\346\216\245</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0p"
                        "x; -qt-block-indent:0; text-indent:0px;\">\346\234\200\345\220\216\345\212\240\344\270\212\346\200\273\347\273\223\351\200\232\350\277\207\347\216\207</p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("run_Page", "\350\277\220\350\241\214", nullptr));
        runFinishBtn->setText(QCoreApplication::translate("run_Page", "Finish", nullptr));
        runSummaryBtn->setText(QCoreApplication::translate("run_Page", "View Summary", nullptr));
        runFolderBtn->setText(QCoreApplication::translate("run_Page", "Open Folder", nullptr));
    } // retranslateUi

};

namespace Ui {
    class run_Page: public Ui_run_Page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RUN_PAGE_H
