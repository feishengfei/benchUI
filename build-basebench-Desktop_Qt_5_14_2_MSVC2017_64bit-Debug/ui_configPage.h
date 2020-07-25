/********************************************************************************
** Form generated from reading UI file 'configPage.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGPAGE_H
#define UI_CONFIGPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_configPage1
{
public:
    QComboBox *configOSBox;
    QLabel *label_configOS;
    QLabel *label_configArch;
    QLabel *label_configLibpath;
    QLabel *label_configOutform;
    QComboBox *configArchBox;
    QComboBox *configOutformBox;
    QCheckBox *configGDBBox;
    QCheckBox *configDumpBox;
    QLineEdit *lineEdit;
    QLabel *label_configOutform_2;
    QComboBox *configOutformBox_2;
    QLabel *label_configOutform_3;
    QComboBox *configOutformBox_3;
    QLabel *label_configOutform_4;
    QComboBox *configOutformBox_4;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label_configOutform_5;
    QComboBox *configOutformBox_5;
    QCheckBox *configGDBBox_2;
    QFrame *line;
    QLabel *label;

    void setupUi(QWidget *configPage1)
    {
        if (configPage1->objectName().isEmpty())
            configPage1->setObjectName(QString::fromUtf8("configPage1"));
        configPage1->resize(400, 300);
        configOSBox = new QComboBox(configPage1);
        configOSBox->addItem(QString());
        configOSBox->addItem(QString());
        configOSBox->setObjectName(QString::fromUtf8("configOSBox"));
        configOSBox->setGeometry(QRect(80, 60, 71, 22));
        QFont font;
        font.setPointSize(8);
        configOSBox->setFont(font);
        label_configOS = new QLabel(configPage1);
        label_configOS->setObjectName(QString::fromUtf8("label_configOS"));
        label_configOS->setGeometry(QRect(30, 60, 51, 21));
        label_configOS->setFont(font);
        label_configArch = new QLabel(configPage1);
        label_configArch->setObjectName(QString::fromUtf8("label_configArch"));
        label_configArch->setGeometry(QRect(30, 90, 51, 21));
        label_configArch->setFont(font);
        label_configLibpath = new QLabel(configPage1);
        label_configLibpath->setObjectName(QString::fromUtf8("label_configLibpath"));
        label_configLibpath->setGeometry(QRect(30, 220, 41, 21));
        label_configLibpath->setFont(font);
        label_configOutform = new QLabel(configPage1);
        label_configOutform->setObjectName(QString::fromUtf8("label_configOutform"));
        label_configOutform->setGeometry(QRect(30, 120, 51, 21));
        label_configOutform->setFont(font);
        configArchBox = new QComboBox(configPage1);
        configArchBox->addItem(QString());
        configArchBox->addItem(QString());
        configArchBox->addItem(QString());
        configArchBox->setObjectName(QString::fromUtf8("configArchBox"));
        configArchBox->setGeometry(QRect(80, 90, 71, 22));
        configArchBox->setFont(font);
        configOutformBox = new QComboBox(configPage1);
        configOutformBox->addItem(QString());
        configOutformBox->addItem(QString());
        configOutformBox->setObjectName(QString::fromUtf8("configOutformBox"));
        configOutformBox->setGeometry(QRect(80, 120, 71, 22));
        configOutformBox->setFont(font);
        configGDBBox = new QCheckBox(configPage1);
        configGDBBox->setObjectName(QString::fromUtf8("configGDBBox"));
        configGDBBox->setGeometry(QRect(260, 90, 71, 21));
        configDumpBox = new QCheckBox(configPage1);
        configDumpBox->setObjectName(QString::fromUtf8("configDumpBox"));
        configDumpBox->setGeometry(QRect(260, 60, 71, 21));
        lineEdit = new QLineEdit(configPage1);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(70, 220, 301, 21));
        label_configOutform_2 = new QLabel(configPage1);
        label_configOutform_2->setObjectName(QString::fromUtf8("label_configOutform_2"));
        label_configOutform_2->setGeometry(QRect(30, 150, 51, 21));
        label_configOutform_2->setFont(font);
        configOutformBox_2 = new QComboBox(configPage1);
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->setObjectName(QString::fromUtf8("configOutformBox_2"));
        configOutformBox_2->setGeometry(QRect(80, 150, 71, 22));
        configOutformBox_2->setFont(font);
        label_configOutform_3 = new QLabel(configPage1);
        label_configOutform_3->setObjectName(QString::fromUtf8("label_configOutform_3"));
        label_configOutform_3->setGeometry(QRect(220, 150, 51, 21));
        label_configOutform_3->setFont(font);
        configOutformBox_3 = new QComboBox(configPage1);
        configOutformBox_3->addItem(QString());
        configOutformBox_3->addItem(QString());
        configOutformBox_3->addItem(QString());
        configOutformBox_3->addItem(QString());
        configOutformBox_3->addItem(QString());
        configOutformBox_3->addItem(QString());
        configOutformBox_3->addItem(QString());
        configOutformBox_3->addItem(QString());
        configOutformBox_3->addItem(QString());
        configOutformBox_3->addItem(QString());
        configOutformBox_3->addItem(QString());
        configOutformBox_3->addItem(QString());
        configOutformBox_3->addItem(QString());
        configOutformBox_3->addItem(QString());
        configOutformBox_3->addItem(QString());
        configOutformBox_3->addItem(QString());
        configOutformBox_3->addItem(QString());
        configOutformBox_3->addItem(QString());
        configOutformBox_3->addItem(QString());
        configOutformBox_3->setObjectName(QString::fromUtf8("configOutformBox_3"));
        configOutformBox_3->setGeometry(QRect(270, 150, 71, 22));
        configOutformBox_3->setFont(font);
        label_configOutform_4 = new QLabel(configPage1);
        label_configOutform_4->setObjectName(QString::fromUtf8("label_configOutform_4"));
        label_configOutform_4->setGeometry(QRect(30, 180, 51, 21));
        label_configOutform_4->setFont(font);
        configOutformBox_4 = new QComboBox(configPage1);
        configOutformBox_4->addItem(QString());
        configOutformBox_4->addItem(QString());
        configOutformBox_4->addItem(QString());
        configOutformBox_4->addItem(QString());
        configOutformBox_4->addItem(QString());
        configOutformBox_4->setObjectName(QString::fromUtf8("configOutformBox_4"));
        configOutformBox_4->setGeometry(QRect(80, 180, 71, 22));
        configOutformBox_4->setFont(font);
        pushButton = new QPushButton(configPage1);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(290, 260, 71, 21));
        pushButton_2 = new QPushButton(configPage1);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(40, 260, 71, 21));
        label_configOutform_5 = new QLabel(configPage1);
        label_configOutform_5->setObjectName(QString::fromUtf8("label_configOutform_5"));
        label_configOutform_5->setGeometry(QRect(220, 180, 51, 21));
        label_configOutform_5->setFont(font);
        configOutformBox_5 = new QComboBox(configPage1);
        configOutformBox_5->addItem(QString());
        configOutformBox_5->addItem(QString());
        configOutformBox_5->addItem(QString());
        configOutformBox_5->addItem(QString());
        configOutformBox_5->addItem(QString());
        configOutformBox_5->setObjectName(QString::fromUtf8("configOutformBox_5"));
        configOutformBox_5->setGeometry(QRect(270, 180, 71, 22));
        configOutformBox_5->setFont(font);
        configGDBBox_2 = new QCheckBox(configPage1);
        configGDBBox_2->setObjectName(QString::fromUtf8("configGDBBox_2"));
        configGDBBox_2->setGeometry(QRect(260, 120, 71, 21));
        line = new QFrame(configPage1);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(20, 40, 361, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label = new QLabel(configPage1);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(170, 20, 61, 21));
        QFont font1;
        font1.setPointSize(11);
        label->setFont(font1);

        retranslateUi(configPage1);

        QMetaObject::connectSlotsByName(configPage1);
    } // setupUi

    void retranslateUi(QWidget *configPage1)
    {
        configPage1->setWindowTitle(QCoreApplication::translate("configPage1", "Form", nullptr));
        configOSBox->setItemText(0, QCoreApplication::translate("configPage1", "Linux", nullptr));
        configOSBox->setItemText(1, QCoreApplication::translate("configPage1", "Windows", nullptr));

        label_configOS->setText(QCoreApplication::translate("configPage1", "\346\223\215\344\275\234\347\263\273\347\273\237", nullptr));
        label_configArch->setText(QCoreApplication::translate("configPage1", "\347\241\254\344\273\266\345\271\263\345\217\260", nullptr));
        label_configLibpath->setText(QCoreApplication::translate("configPage1", "\345\272\223\350\267\257\345\276\204", nullptr));
        label_configOutform->setText(QCoreApplication::translate("configPage1", "\350\276\223\345\207\272\346\240\274\345\274\217", nullptr));
        configArchBox->setItemText(0, QCoreApplication::translate("configPage1", "x86_64", nullptr));
        configArchBox->setItemText(1, QCoreApplication::translate("configPage1", "mips64", nullptr));
        configArchBox->setItemText(2, QCoreApplication::translate("configPage1", "armv8", nullptr));

        configOutformBox->setItemText(0, QCoreApplication::translate("configPage1", "html", nullptr));
        configOutformBox->setItemText(1, QCoreApplication::translate("configPage1", "excel", nullptr));

        configGDBBox->setText(QCoreApplication::translate("configPage1", "\345\274\200\345\220\257GDB", nullptr));
        configDumpBox->setText(QCoreApplication::translate("configPage1", "dump\350\276\223\345\207\272", nullptr));
        label_configOutform_2->setText(QCoreApplication::translate("configPage1", "API \347\261\273\345\236\213", nullptr));
        configOutformBox_2->setItemText(0, QCoreApplication::translate("configPage1", "OpenGL", nullptr));
        configOutformBox_2->setItemText(1, QCoreApplication::translate("configPage1", "OpenGL ES", nullptr));

        label_configOutform_3->setText(QCoreApplication::translate("configPage1", "API \347\211\210\346\234\254", nullptr));
        configOutformBox_3->setItemText(0, QCoreApplication::translate("configPage1", "1.1", nullptr));
        configOutformBox_3->setItemText(1, QCoreApplication::translate("configPage1", "2.0", nullptr));
        configOutformBox_3->setItemText(2, QCoreApplication::translate("configPage1", "3.0", nullptr));
        configOutformBox_3->setItemText(3, QCoreApplication::translate("configPage1", "3.1", nullptr));
        configOutformBox_3->setItemText(4, QCoreApplication::translate("configPage1", "3.2", nullptr));
        configOutformBox_3->setItemText(5, QCoreApplication::translate("configPage1", "3.3", nullptr));
        configOutformBox_3->setItemText(6, QCoreApplication::translate("configPage1", "1.3", nullptr));
        configOutformBox_3->setItemText(7, QCoreApplication::translate("configPage1", "1.4", nullptr));
        configOutformBox_3->setItemText(8, QCoreApplication::translate("configPage1", "1.5", nullptr));
        configOutformBox_3->setItemText(9, QCoreApplication::translate("configPage1", "2.1", nullptr));
        configOutformBox_3->setItemText(10, QCoreApplication::translate("configPage1", "2.2", nullptr));
        configOutformBox_3->setItemText(11, QCoreApplication::translate("configPage1", "3.3", nullptr));
        configOutformBox_3->setItemText(12, QCoreApplication::translate("configPage1", "4.0", nullptr));
        configOutformBox_3->setItemText(13, QCoreApplication::translate("configPage1", "4.1", nullptr));
        configOutformBox_3->setItemText(14, QCoreApplication::translate("configPage1", "4.2", nullptr));
        configOutformBox_3->setItemText(15, QCoreApplication::translate("configPage1", "4.3", nullptr));
        configOutformBox_3->setItemText(16, QCoreApplication::translate("configPage1", "4.4", nullptr));
        configOutformBox_3->setItemText(17, QCoreApplication::translate("configPage1", "4.5", nullptr));
        configOutformBox_3->setItemText(18, QCoreApplication::translate("configPage1", "4.6", nullptr));

        label_configOutform_4->setText(QCoreApplication::translate("configPage1", "\346\250\241\345\235\227\351\200\211\346\213\251", nullptr));
        configOutformBox_4->setItemText(0, QCoreApplication::translate("configPage1", "coverage", nullptr));
        configOutformBox_4->setItemText(1, QCoreApplication::translate("configPage1", "function", nullptr));
        configOutformBox_4->setItemText(2, QCoreApplication::translate("configPage1", "error", nullptr));
        configOutformBox_4->setItemText(3, QCoreApplication::translate("configPage1", "limit", nullptr));
        configOutformBox_4->setItemText(4, QCoreApplication::translate("configPage1", "shader", nullptr));

        pushButton->setText(QCoreApplication::translate("configPage1", "Next", nullptr));
        pushButton_2->setText(QCoreApplication::translate("configPage1", "Back", nullptr));
        label_configOutform_5->setText(QCoreApplication::translate("configPage1", "\347\252\227\345\217\243\347\263\273\347\273\237", nullptr));
        configOutformBox_5->setItemText(0, QCoreApplication::translate("configPage1", "glut", nullptr));
        configOutformBox_5->setItemText(1, QCoreApplication::translate("configPage1", "glfw", nullptr));
        configOutformBox_5->setItemText(2, QCoreApplication::translate("configPage1", "egl", nullptr));
        configOutformBox_5->setItemText(3, QCoreApplication::translate("configPage1", "sdl", nullptr));
        configOutformBox_5->setItemText(4, QCoreApplication::translate("configPage1", "glx", nullptr));

        configGDBBox_2->setText(QCoreApplication::translate("configPage1", "\346\230\257\345\220\246\350\207\252\351\200\211\347\224\250\344\276\213", nullptr));
        label->setText(QCoreApplication::translate("configPage1", "\351\205\215\347\275\256\351\200\211\346\213\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class configPage1: public Ui_configPage1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGPAGE_H
