/********************************************************************************
** Form generated from reading UI file 'moduletest.ui'
**
** Created: Wed Oct 21 15:22:21 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODULETEST_H
#define UI_MODULETEST_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModuleTestClass
{
public:
    QWidget *centralWidget;
    QPushButton *btnShowDlg;
    QLabel *labeInfo;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ModuleTestClass)
    {
        if (ModuleTestClass->objectName().isEmpty())
            ModuleTestClass->setObjectName(QString::fromUtf8("ModuleTestClass"));
        ModuleTestClass->resize(600, 400);
        centralWidget = new QWidget(ModuleTestClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        btnShowDlg = new QPushButton(centralWidget);
        btnShowDlg->setObjectName(QString::fromUtf8("btnShowDlg"));
        btnShowDlg->setGeometry(QRect(230, 100, 101, 51));
        labeInfo = new QLabel(centralWidget);
        labeInfo->setObjectName(QString::fromUtf8("labeInfo"));
        labeInfo->setGeometry(QRect(230, 200, 101, 51));
        ModuleTestClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ModuleTestClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        ModuleTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ModuleTestClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ModuleTestClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ModuleTestClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ModuleTestClass->setStatusBar(statusBar);

        retranslateUi(ModuleTestClass);

        QMetaObject::connectSlotsByName(ModuleTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *ModuleTestClass)
    {
        ModuleTestClass->setWindowTitle(QApplication::translate("ModuleTestClass", "ModuleTest", 0, QApplication::UnicodeUTF8));
        btnShowDlg->setText(QApplication::translate("ModuleTestClass", "Show dialog", 0, QApplication::UnicodeUTF8));
        labeInfo->setText(QApplication::translate("ModuleTestClass", "\350\276\223\345\207\272", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ModuleTestClass: public Ui_ModuleTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODULETEST_H
