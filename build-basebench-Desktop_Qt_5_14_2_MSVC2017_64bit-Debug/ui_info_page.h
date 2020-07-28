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
    QPushButton *descriptionStartButton;
    QFrame *line;

    void setupUi(QWidget *info_Page)
    {
        if (info_Page->objectName().isEmpty())
            info_Page->setObjectName(QString::fromUtf8("info_Page"));
        info_Page->resize(600, 400);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        info_Page->setFont(font);
        info_Page->setLayoutDirection(Qt::LeftToRight);
        textBrowser = new QTextBrowser(info_Page);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(50, 70, 491, 271));
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy);
        textBrowser->setFont(font);
        label = new QLabel(info_Page);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 10, 391, 41));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\273\221\344\275\223"));
        font1.setPointSize(18);
        font1.setBold(true);
        font1.setUnderline(false);
        font1.setWeight(75);
        label->setFont(font1);
        descriptionStartButton = new QPushButton(info_Page);
        descriptionStartButton->setObjectName(QString::fromUtf8("descriptionStartButton"));
        descriptionStartButton->setGeometry(QRect(230, 350, 91, 31));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(descriptionStartButton->sizePolicy().hasHeightForWidth());
        descriptionStartButton->setSizePolicy(sizePolicy1);
        descriptionStartButton->setFont(font);
        line = new QFrame(info_Page);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(20, 50, 551, 21));
        sizePolicy.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy);
        line->setFont(font);
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
"</style></head><body style=\" font-family:'\345\276\256\350\275\257\351\233\205\351\273\221','\345\276\256\350\275\257\351\233\205\351\273\221'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-weight:600;\">\350\275\257\344\273\266\344\273\213\347\273\215\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">    \350\277\233\350\241\214OpenGL\345\237\272\346\234\254\346\265\213\350\257\225\357\274\214\345\214\205\345\220\253</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; marg"
                        "in-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-weight:600;\">\347\211\210\346\235\203\345\243\260\346\230\216\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">    Copyright\343\200\202\343\200\202\343\200\202\343\200\202\343\200\202</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-weight:600;\">\344\275\234\350\200\205    \357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">    ogldisco</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimS"
                        "un'; font-weight:600;\">\347\211\210\346\234\254    \357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">    v2.0</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-weight:600;\">\344\277\256\346\224\271\346\227\266\351\227\264\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">    2020.7.22</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun'; font-weight:600;\">\344\275\277\347\224\250\346\226\271\346\263\225\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; ma"
                        "rgin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">    readme\357\274\214\351\234\200\350\246\201\351\205\215\347\275\256\345\222\214\345\207\206\345\244\207\347\232\204</span></p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px; font-family:'SimSun';\"><br /></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("info_Page", "Name Tile", nullptr));
        descriptionStartButton->setText(QCoreApplication::translate("info_Page", "Start", nullptr));
    } // retranslateUi

};

namespace Ui {
    class info_Page: public Ui_info_Page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFO_PAGE_H
