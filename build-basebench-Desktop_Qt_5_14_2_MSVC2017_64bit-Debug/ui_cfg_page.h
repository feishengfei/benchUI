/********************************************************************************
** Form generated from reading UI file 'cfg_page.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CFG_PAGE_H
#define UI_CFG_PAGE_H

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

class Ui_cfg_Page
{
public:
    QLabel *label_configOutform_4;
    QPushButton *cfgNextBtn;
    QComboBox *configOutformBox_5;
    QLabel *label_configOutform_2;
    QFrame *line;
    QLabel *label_configArch;
    QLabel *label;
    QComboBox *configOutformBox_4;
    QLabel *label_configOutform;
    QCheckBox *cfgSelfCheck;
    QCheckBox *configDumpBox;
    QComboBox *configOutformBox_2;
    QLineEdit *lineEdit;
    QComboBox *configOutformBox;
    QLabel *label_configLibpath;
    QComboBox *configArchBox;
    QLabel *label_configOutform_5;
    QPushButton *cfgExitBtn;
    QCheckBox *configGDBBox;
    QCheckBox *cfgAPICheck;

    void setupUi(QWidget *cfg_Page)
    {
        if (cfg_Page->objectName().isEmpty())
            cfg_Page->setObjectName(QString::fromUtf8("cfg_Page"));
        cfg_Page->resize(600, 400);
        label_configOutform_4 = new QLabel(cfg_Page);
        label_configOutform_4->setObjectName(QString::fromUtf8("label_configOutform_4"));
        label_configOutform_4->setGeometry(QRect(60, 250, 61, 21));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        label_configOutform_4->setFont(font);
        cfgNextBtn = new QPushButton(cfg_Page);
        cfgNextBtn->setObjectName(QString::fromUtf8("cfgNextBtn"));
        cfgNextBtn->setGeometry(QRect(440, 350, 81, 31));
        cfgNextBtn->setFont(font);
        configOutformBox_5 = new QComboBox(cfg_Page);
        configOutformBox_5->addItem(QString());
        configOutformBox_5->addItem(QString());
        configOutformBox_5->addItem(QString());
        configOutformBox_5->addItem(QString());
        configOutformBox_5->addItem(QString());
        configOutformBox_5->setObjectName(QString::fromUtf8("configOutformBox_5"));
        configOutformBox_5->setGeometry(QRect(130, 130, 121, 22));
        configOutformBox_5->setFont(font);
        label_configOutform_2 = new QLabel(cfg_Page);
        label_configOutform_2->setObjectName(QString::fromUtf8("label_configOutform_2"));
        label_configOutform_2->setGeometry(QRect(60, 210, 61, 21));
        label_configOutform_2->setFont(font);
        line = new QFrame(cfg_Page);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(40, 60, 521, 16));
        line->setFont(font);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        label_configArch = new QLabel(cfg_Page);
        label_configArch->setObjectName(QString::fromUtf8("label_configArch"));
        label_configArch->setGeometry(QRect(60, 90, 61, 21));
        label_configArch->setFont(font);
        label = new QLabel(cfg_Page);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(280, 30, 61, 21));
        label->setFont(font);
        configOutformBox_4 = new QComboBox(cfg_Page);
        configOutformBox_4->addItem(QString());
        configOutformBox_4->addItem(QString());
        configOutformBox_4->addItem(QString());
        configOutformBox_4->addItem(QString());
        configOutformBox_4->addItem(QString());
        configOutformBox_4->setObjectName(QString::fromUtf8("configOutformBox_4"));
        configOutformBox_4->setGeometry(QRect(130, 250, 121, 21));
        configOutformBox_4->setFont(font);
        label_configOutform = new QLabel(cfg_Page);
        label_configOutform->setObjectName(QString::fromUtf8("label_configOutform"));
        label_configOutform->setGeometry(QRect(60, 170, 61, 21));
        label_configOutform->setFont(font);
        cfgSelfCheck = new QCheckBox(cfg_Page);
        cfgSelfCheck->setObjectName(QString::fromUtf8("cfgSelfCheck"));
        cfgSelfCheck->setGeometry(QRect(340, 170, 121, 21));
        cfgSelfCheck->setFont(font);
        configDumpBox = new QCheckBox(cfg_Page);
        configDumpBox->setObjectName(QString::fromUtf8("configDumpBox"));
        configDumpBox->setGeometry(QRect(340, 90, 111, 21));
        configDumpBox->setFont(font);
        configOutformBox_2 = new QComboBox(cfg_Page);
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->addItem(QString());
        configOutformBox_2->setObjectName(QString::fromUtf8("configOutformBox_2"));
        configOutformBox_2->setGeometry(QRect(130, 210, 121, 22));
        configOutformBox_2->setFont(font);
        lineEdit = new QLineEdit(cfg_Page);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(100, 300, 441, 21));
        lineEdit->setFont(font);
        configOutformBox = new QComboBox(cfg_Page);
        configOutformBox->addItem(QString());
        configOutformBox->addItem(QString());
        configOutformBox->setObjectName(QString::fromUtf8("configOutformBox"));
        configOutformBox->setGeometry(QRect(130, 170, 121, 22));
        configOutformBox->setFont(font);
        label_configLibpath = new QLabel(cfg_Page);
        label_configLibpath->setObjectName(QString::fromUtf8("label_configLibpath"));
        label_configLibpath->setGeometry(QRect(50, 300, 41, 21));
        label_configLibpath->setFont(font);
        configArchBox = new QComboBox(cfg_Page);
        configArchBox->addItem(QString());
        configArchBox->addItem(QString());
        configArchBox->addItem(QString());
        configArchBox->setObjectName(QString::fromUtf8("configArchBox"));
        configArchBox->setGeometry(QRect(130, 90, 121, 22));
        configArchBox->setFont(font);
        label_configOutform_5 = new QLabel(cfg_Page);
        label_configOutform_5->setObjectName(QString::fromUtf8("label_configOutform_5"));
        label_configOutform_5->setGeometry(QRect(60, 130, 61, 21));
        label_configOutform_5->setFont(font);
        cfgExitBtn = new QPushButton(cfg_Page);
        cfgExitBtn->setObjectName(QString::fromUtf8("cfgExitBtn"));
        cfgExitBtn->setGeometry(QRect(70, 350, 81, 31));
        cfgExitBtn->setFont(font);
        configGDBBox = new QCheckBox(cfg_Page);
        configGDBBox->setObjectName(QString::fromUtf8("configGDBBox"));
        configGDBBox->setGeometry(QRect(340, 130, 91, 21));
        configGDBBox->setFont(font);
        cfgAPICheck = new QCheckBox(cfg_Page);
        cfgAPICheck->setObjectName(QString::fromUtf8("cfgAPICheck"));
        cfgAPICheck->setGeometry(QRect(340, 210, 121, 21));
        cfgAPICheck->setFont(font);

        retranslateUi(cfg_Page);

        QMetaObject::connectSlotsByName(cfg_Page);
    } // setupUi

    void retranslateUi(QWidget *cfg_Page)
    {
        cfg_Page->setWindowTitle(QCoreApplication::translate("cfg_Page", "Form", nullptr));
        label_configOutform_4->setText(QCoreApplication::translate("cfg_Page", "\346\250\241\345\235\227\351\200\211\346\213\251", nullptr));
        cfgNextBtn->setText(QCoreApplication::translate("cfg_Page", "Next", nullptr));
        configOutformBox_5->setItemText(0, QCoreApplication::translate("cfg_Page", "glut", nullptr));
        configOutformBox_5->setItemText(1, QCoreApplication::translate("cfg_Page", "glfw", nullptr));
        configOutformBox_5->setItemText(2, QCoreApplication::translate("cfg_Page", "egl", nullptr));
        configOutformBox_5->setItemText(3, QCoreApplication::translate("cfg_Page", "sdl", nullptr));
        configOutformBox_5->setItemText(4, QCoreApplication::translate("cfg_Page", "glx", nullptr));

        label_configOutform_2->setText(QCoreApplication::translate("cfg_Page", "API \347\211\210\346\234\254", nullptr));
        label_configArch->setText(QCoreApplication::translate("cfg_Page", "\347\241\254\344\273\266\345\271\263\345\217\260", nullptr));
        label->setText(QCoreApplication::translate("cfg_Page", "\351\205\215\347\275\256\351\200\211\346\213\251", nullptr));
        configOutformBox_4->setItemText(0, QCoreApplication::translate("cfg_Page", "coverage", nullptr));
        configOutformBox_4->setItemText(1, QCoreApplication::translate("cfg_Page", "function", nullptr));
        configOutformBox_4->setItemText(2, QCoreApplication::translate("cfg_Page", "error", nullptr));
        configOutformBox_4->setItemText(3, QCoreApplication::translate("cfg_Page", "limit", nullptr));
        configOutformBox_4->setItemText(4, QCoreApplication::translate("cfg_Page", "shader", nullptr));

        label_configOutform->setText(QCoreApplication::translate("cfg_Page", "\350\276\223\345\207\272\346\240\274\345\274\217", nullptr));
        cfgSelfCheck->setText(QCoreApplication::translate("cfg_Page", "\346\230\257\345\220\246\350\207\252\351\200\211\347\224\250\344\276\213", nullptr));
        configDumpBox->setText(QCoreApplication::translate("cfg_Page", "dump\350\276\223\345\207\272", nullptr));
        configOutformBox_2->setItemText(0, QCoreApplication::translate("cfg_Page", "All", nullptr));
        configOutformBox_2->setItemText(1, QCoreApplication::translate("cfg_Page", "OGL1.3", nullptr));
        configOutformBox_2->setItemText(2, QCoreApplication::translate("cfg_Page", "OGL1.4", nullptr));
        configOutformBox_2->setItemText(3, QCoreApplication::translate("cfg_Page", "OGL1.5", nullptr));
        configOutformBox_2->setItemText(4, QCoreApplication::translate("cfg_Page", "OGL2.0", nullptr));
        configOutformBox_2->setItemText(5, QCoreApplication::translate("cfg_Page", "OGL2.1", nullptr));
        configOutformBox_2->setItemText(6, QCoreApplication::translate("cfg_Page", "OGL2.2", nullptr));
        configOutformBox_2->setItemText(7, QCoreApplication::translate("cfg_Page", "OGL3.0", nullptr));
        configOutformBox_2->setItemText(8, QCoreApplication::translate("cfg_Page", "OGL3.1", nullptr));
        configOutformBox_2->setItemText(9, QCoreApplication::translate("cfg_Page", "OGL3.2", nullptr));
        configOutformBox_2->setItemText(10, QCoreApplication::translate("cfg_Page", "OGL3.3", nullptr));
        configOutformBox_2->setItemText(11, QCoreApplication::translate("cfg_Page", "OGL4.0", nullptr));
        configOutformBox_2->setItemText(12, QCoreApplication::translate("cfg_Page", "OGL4.1", nullptr));
        configOutformBox_2->setItemText(13, QCoreApplication::translate("cfg_Page", "OGL4.2", nullptr));
        configOutformBox_2->setItemText(14, QCoreApplication::translate("cfg_Page", "OGL4.3", nullptr));
        configOutformBox_2->setItemText(15, QCoreApplication::translate("cfg_Page", "OGL4.4", nullptr));
        configOutformBox_2->setItemText(16, QCoreApplication::translate("cfg_Page", "OGL4.5", nullptr));
        configOutformBox_2->setItemText(17, QCoreApplication::translate("cfg_Page", "OGL4.6", nullptr));
        configOutformBox_2->setItemText(18, QCoreApplication::translate("cfg_Page", "GLES1.1", nullptr));
        configOutformBox_2->setItemText(19, QCoreApplication::translate("cfg_Page", "GLES2.0", nullptr));
        configOutformBox_2->setItemText(20, QCoreApplication::translate("cfg_Page", "GLES3.0", nullptr));
        configOutformBox_2->setItemText(21, QCoreApplication::translate("cfg_Page", "GLES3.1", nullptr));
        configOutformBox_2->setItemText(22, QCoreApplication::translate("cfg_Page", "GLES3.2", nullptr));
        configOutformBox_2->setItemText(23, QCoreApplication::translate("cfg_Page", "GLES3.3", nullptr));

        lineEdit->setText(QCoreApplication::translate("cfg_Page", "\345\217\257\351\200\211\351\241\271", nullptr));
        configOutformBox->setItemText(0, QCoreApplication::translate("cfg_Page", "html", nullptr));
        configOutformBox->setItemText(1, QCoreApplication::translate("cfg_Page", "excel", nullptr));

        label_configLibpath->setText(QCoreApplication::translate("cfg_Page", "\345\272\223\350\267\257\345\276\204", nullptr));
        configArchBox->setItemText(0, QCoreApplication::translate("cfg_Page", "x86_64", nullptr));
        configArchBox->setItemText(1, QCoreApplication::translate("cfg_Page", "mips64", nullptr));
        configArchBox->setItemText(2, QCoreApplication::translate("cfg_Page", "armv8", nullptr));

        label_configOutform_5->setText(QCoreApplication::translate("cfg_Page", "\347\252\227\345\217\243\347\263\273\347\273\237", nullptr));
        cfgExitBtn->setText(QCoreApplication::translate("cfg_Page", "Exit", nullptr));
        configGDBBox->setText(QCoreApplication::translate("cfg_Page", "\345\274\200\345\220\257GDB", nullptr));
        cfgAPICheck->setText(QCoreApplication::translate("cfg_Page", "\346\214\211\347\205\247API\351\200\211\346\213\251", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cfg_Page: public Ui_cfg_Page {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CFG_PAGE_H
