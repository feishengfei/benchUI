/********************************************************************************
** Form generated from reading UI file 'buildpage.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BUILDPAGE_H
#define UI_BUILDPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_buildPage
{
public:
    QLabel *label;
    QFrame *line;
    QProgressBar *progressBar;
    QTextBrowser *textBrowser;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QWidget *buildPage)
    {
        if (buildPage->objectName().isEmpty())
            buildPage->setObjectName(QString::fromUtf8("buildPage"));
        buildPage->resize(400, 300);
        label = new QLabel(buildPage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 20, 31, 21));
        QFont font;
        font.setPointSize(8);
        label->setFont(font);
        line = new QFrame(buildPage);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(30, 40, 341, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        progressBar = new QProgressBar(buildPage);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(40, 220, 321, 23));
        progressBar->setValue(24);
        textBrowser = new QTextBrowser(buildPage);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(40, 60, 321, 151));
        pushButton = new QPushButton(buildPage);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 260, 80, 21));
        pushButton_2 = new QPushButton(buildPage);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(160, 260, 80, 21));
        pushButton_3 = new QPushButton(buildPage);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(280, 260, 80, 21));

        retranslateUi(buildPage);

        QMetaObject::connectSlotsByName(buildPage);
    } // setupUi

    void retranslateUi(QWidget *buildPage)
    {
        buildPage->setWindowTitle(QCoreApplication::translate("buildPage", "Form", nullptr));
        label->setText(QCoreApplication::translate("buildPage", "\347\274\226\350\257\221", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("buildPage", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:6pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\347\274\226\350\257\221\344\277\241\346\201\257\350\276\223\345\207\272\357\274\232</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\344\277\241\346\201\257\351\234\200\350\246\201\346\210\252\345\217\226\350\276\223\345\207\272</p></body></html>", nullptr));
        pushButton->setText(QCoreApplication::translate("buildPage", "Export log", nullptr));
        pushButton_2->setText(QCoreApplication::translate("buildPage", "Conitnue", nullptr));
        pushButton_3->setText(QCoreApplication::translate("buildPage", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class buildPage: public Ui_buildPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BUILDPAGE_H
