/********************************************************************************
** Form generated from reading UI file 'info_page.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFO_PAGE_H
#define UI_INFO_PAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_info_Page
{
public:
    QTextBrowser *textBrowser;
    QLabel *label;
    QPushButton *descriptionExitButton;
    QPushButton *descriptionStartButton;
    QFrame *line;

    void setupUi(QWidget *info_Page)
    {
        if (info_Page->objectName().isEmpty())
            info_Page->setObjectName(QString::fromUtf8("info_Page"));
        info_Page->resize(600, 400);
        textBrowser = new QTextBrowser(info_Page);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(50, 70, 491, 281));
        QFont font;
        font.setPointSize(10);
        textBrowser->setFont(font);
        label = new QLabel(info_Page);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 161, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\226\260\345\256\213\344\275\223"));
        font1.setPointSize(23);
        font1.setBold(true);
        font1.setUnderline(false);
        font1.setWeight(75);
        label->setFont(font1);
        descriptionExitButton = new QPushButton(info_Page);
        descriptionExitButton->setObjectName(QString::fromUtf8("descriptionExitButton"));
        descriptionExitButton->setGeometry(QRect(50, 360, 91, 31));
        descriptionExitButton->setFont(font);
        descriptionStartButton = new QPushButton(info_Page);
        descriptionStartButton->setObjectName(QString::fromUtf8("descriptionStartButton"));
        descriptionStartButton->setGeometry(QRect(449, 360, 91, 31));
        descriptionStartButton->setFont(font);
        line = new QFrame(info_Page);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(20, 50, 551, 21));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        retranslateUi(info_Page);

        QMetaObject::connectSlotsByName(info_Page);
    } // setupUi

    void retranslateUi(QWidget *info_Page)
    {
        info_Page->setWindowTitle(QCoreApplication::translate("info_Page", "Form", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("info_Page", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">\350\275\257\344\273\266\344\273\213\347\273\215\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">    \350\277\233\350\241\214OpenGL\345\237\272\346\234\254\346\265\213\350\257\225\357\274\214\345\214\205\345\220\253</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">\347\211\210\346\235\203\345\243\260\346\230\216\357\274\232"
                        "</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">    Copyright\343\200\202\343\200\202\343\200\202\343\200\202\343\200\202</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">\344\275\234\350\200\205    \357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">    ogldisco</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">\347\211\210\346\234\254    \357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">    v2.0</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; te"
                        "xt-indent:0px;\"><span style=\" font-weight:600;\">\344\277\256\346\224\271\346\227\266\351\227\264\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">    2020.7.22</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-weight:600;\">\344\275\277\347\224\250\346\226\271\346\263\225\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">    readme\357\274\214\351\234\200\350\246\201\351\205\215\347\275\256\345\222\214\345\207\206\345\244\207\347\232\204</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("info_Page", "Name Tile", nullptr));
        descriptionExitButton->setText(QCoreApplication::translate("info_Page", "Exit", nullptr));
        descriptionStartButton->setText(QCoreApplication::translate("info_Page", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class info_Page: public Ui_info_Page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFO_PAGE_H
