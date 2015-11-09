/********************************************************************************
** Form generated from reading UI file 'configdlg.ui'
**
** Created: Wed Oct 21 15:22:21 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGDLG_H
#define UI_CONFIGDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QSlider>

QT_BEGIN_NAMESPACE

class Ui_ConfigDlg
{
public:
    QSlider *horizontalSlider;

    void setupUi(QDialog *ConfigDlg)
    {
        if (ConfigDlg->objectName().isEmpty())
            ConfigDlg->setObjectName(QString::fromUtf8("ConfigDlg"));
        ConfigDlg->resize(400, 300);
        horizontalSlider = new QSlider(ConfigDlg);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(140, 160, 160, 19));
        horizontalSlider->setOrientation(Qt::Horizontal);

        retranslateUi(ConfigDlg);

        QMetaObject::connectSlotsByName(ConfigDlg);
    } // setupUi

    void retranslateUi(QDialog *ConfigDlg)
    {
        ConfigDlg->setWindowTitle(QApplication::translate("ConfigDlg", "ConfigDlg", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ConfigDlg: public Ui_ConfigDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGDLG_H
