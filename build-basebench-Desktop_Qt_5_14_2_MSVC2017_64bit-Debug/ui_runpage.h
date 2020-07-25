/********************************************************************************
** Form generated from reading UI file 'runpage.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RUNPAGE_H
#define UI_RUNPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_runPage
{
public:
    QPushButton *pushButton_3;
    QTextBrowser *textBrowser;
    QLabel *label;
    QProgressBar *progressBar;
    QPushButton *pushButton;
    QFrame *line;

    void setupUi(QWidget *runPage)
    {
        if (runPage->objectName().isEmpty())
            runPage->setObjectName(QString::fromUtf8("runPage"));
        runPage->resize(400, 300);
        pushButton_3 = new QPushButton(runPage);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(280, 260, 80, 21));
        textBrowser = new QTextBrowser(runPage);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(40, 60, 321, 151));
        label = new QLabel(runPage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 20, 31, 21));
        QFont font;
        font.setPointSize(8);
        label->setFont(font);
        progressBar = new QProgressBar(runPage);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(40, 220, 321, 23));
        progressBar->setValue(24);
        pushButton = new QPushButton(runPage);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 260, 80, 21));
        line = new QFrame(runPage);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(30, 40, 341, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        retranslateUi(runPage);

        QMetaObject::connectSlotsByName(runPage);
    } // setupUi

    void retranslateUi(QWidget *runPage)
    {
        runPage->setWindowTitle(QCoreApplication::translate("runPage", "Form", nullptr));
        pushButton_3->setText(QCoreApplication::translate("runPage", "Exit", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("runPage", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:6pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\277\220\350\241\214\350\277\207\347\250\213\345\222\214\347\273\223\346\236\234\345\261\225\347\244\272</p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("runPage", "\350\277\220\350\241\214", nullptr));
        pushButton->setText(QCoreApplication::translate("runPage", "Result", nullptr));
    } // retranslateUi

};

namespace Ui {
    class runPage: public Ui_runPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RUNPAGE_H
