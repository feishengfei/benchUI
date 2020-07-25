/********************************************************************************
** Form generated from reading UI file 'conformpage.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFORMPAGE_H
#define UI_CONFORMPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_conformPage
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QTextEdit *textEdit;
    QFrame *line;
    QLabel *label;

    void setupUi(QWidget *conformPage)
    {
        if (conformPage->objectName().isEmpty())
            conformPage->setObjectName(QString::fromUtf8("conformPage"));
        conformPage->resize(400, 300);
        pushButton = new QPushButton(conformPage);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 260, 80, 21));
        pushButton_2 = new QPushButton(conformPage);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(280, 260, 80, 21));
        textEdit = new QTextEdit(conformPage);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(40, 60, 321, 181));
        line = new QFrame(conformPage);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(30, 40, 341, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label = new QLabel(conformPage);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(180, 20, 61, 21));
        QFont font;
        font.setPointSize(8);
        label->setFont(font);

        retranslateUi(conformPage);

        QMetaObject::connectSlotsByName(conformPage);
    } // setupUi

    void retranslateUi(QWidget *conformPage)
    {
        conformPage->setWindowTitle(QCoreApplication::translate("conformPage", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("conformPage", "Back", nullptr));
        pushButton_2->setText(QCoreApplication::translate("conformPage", "Conform", nullptr));
        textEdit->setHtml(QCoreApplication::translate("conformPage", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:6pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\230\276\347\244\272\351\205\215\347\275\256\347\233\270\345\205\263\344\277\241\346\201\257\357\274\214\350\277\233\350\241\214\347\241\256\350\256\244</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\347\216\257\345\242\203\357\274\232</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\347\211\210\346\234\254\357\274\232</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-rig"
                        "ht:0px; -qt-block-indent:0; text-indent:0px;\">\347\261\273\345\236\213\357\274\232</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\345\272\223\357\274\232</p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("conformPage", "\344\277\241\346\201\257\347\241\256\350\256\244", nullptr));
    } // retranslateUi

};

namespace Ui {
    class conformPage: public Ui_conformPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFORMPAGE_H
