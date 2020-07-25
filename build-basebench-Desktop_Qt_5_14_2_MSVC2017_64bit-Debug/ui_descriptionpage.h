/********************************************************************************
** Form generated from reading UI file 'descriptionpage.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DESCRIPTIONPAGE_H
#define UI_DESCRIPTIONPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QLabel *label;
    QTextBrowser *textBrowser;
    QFrame *line;
    QPushButton *descriptionStartButton;
    QPushButton *descriptionExitButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QString::fromUtf8("Widget"));
        Widget->resize(400, 300);
        Widget->setAutoFillBackground(false);
        Widget->setStyleSheet(QString::fromUtf8(""));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 161, 41));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\226\260\345\256\213\344\275\223"));
        font.setPointSize(23);
        font.setBold(true);
        font.setUnderline(false);
        font.setWeight(75);
        label->setFont(font);
        textBrowser = new QTextBrowser(Widget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(20, 70, 361, 191));
        line = new QFrame(Widget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(10, 50, 381, 21));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        descriptionStartButton = new QPushButton(Widget);
        descriptionStartButton->setObjectName(QString::fromUtf8("descriptionStartButton"));
        descriptionStartButton->setGeometry(QRect(40, 270, 80, 21));
        descriptionExitButton = new QPushButton(Widget);
        descriptionExitButton->setObjectName(QString::fromUtf8("descriptionExitButton"));
        descriptionExitButton->setGeometry(QRect(280, 270, 80, 21));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        label->setText(QCoreApplication::translate("Widget", "Name Tile", nullptr));
        textBrowser->setHtml(QCoreApplication::translate("Widget", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:6pt; font-weight:400; font-style:normal;\">\n"
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
        descriptionStartButton->setText(QCoreApplication::translate("Widget", "Start", nullptr));
        descriptionExitButton->setText(QCoreApplication::translate("Widget", "Exit", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DESCRIPTIONPAGE_H
