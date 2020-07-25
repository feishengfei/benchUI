/********************************************************************************
** Form generated from reading UI file 'conform_page.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFORM_PAGE_H
#define UI_CONFORM_PAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_conform_Page
{
public:
    QPushButton *cfmPageBtn;
    QPushButton *cfmBackBtn;
    QFrame *line;
    QTextEdit *textEdit;
    QLabel *label;

    void setupUi(QWidget *conform_Page)
    {
        if (conform_Page->objectName().isEmpty())
            conform_Page->setObjectName(QString::fromUtf8("conform_Page"));
        conform_Page->resize(600, 400);
        cfmPageBtn = new QPushButton(conform_Page);
        cfmPageBtn->setObjectName(QString::fromUtf8("cfmPageBtn"));
        cfmPageBtn->setGeometry(QRect(439, 350, 91, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        cfmPageBtn->setFont(font);
        cfmBackBtn = new QPushButton(conform_Page);
        cfmBackBtn->setObjectName(QString::fromUtf8("cfmBackBtn"));
        cfmBackBtn->setGeometry(QRect(60, 350, 91, 31));
        cfmBackBtn->setFont(font);
        line = new QFrame(conform_Page);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(30, 40, 531, 16));
        line->setFont(font);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        textEdit = new QTextEdit(conform_Page);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(50, 60, 491, 281));
        textEdit->setFont(font);
        label = new QLabel(conform_Page);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(270, 10, 91, 31));
        label->setFont(font);

        retranslateUi(conform_Page);

        QMetaObject::connectSlotsByName(conform_Page);
    } // setupUi

    void retranslateUi(QWidget *conform_Page)
    {
        conform_Page->setWindowTitle(QCoreApplication::translate("conform_Page", "Form", nullptr));
        cfmPageBtn->setText(QCoreApplication::translate("conform_Page", "Conform", nullptr));
        cfmBackBtn->setText(QCoreApplication::translate("conform_Page", "Back", nullptr));
        textEdit->setHtml(QCoreApplication::translate("conform_Page", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\276\256\350\275\257\351\233\205\351\273\221'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">\346\230\276\347\244\272\351\205\215\347\275\256\347\233\270\345\205\263\344\277\241\346\201\257\357\274\214\350\277\233\350\241\214\347\241\256\350\256\244</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">\347\216\257\345\242\203\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; tex"
                        "t-indent:0px;\"><span style=\" font-family:'SimSun';\">\347\211\210\346\234\254\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">\347\261\273\345\236\213\357\274\232</span></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'SimSun';\">\345\272\223\357\274\232</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("conform_Page", "\344\277\241\346\201\257\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class conform_Page: public Ui_conform_Page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFORM_PAGE_H
