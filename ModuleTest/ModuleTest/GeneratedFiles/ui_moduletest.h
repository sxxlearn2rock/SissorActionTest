/********************************************************************************
** Form generated from reading UI file 'moduletest.ui'
**
** Created: Tue Oct 6 12:58:58 2015
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
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ModuleTestClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ModuleTestClass)
    {
        if (ModuleTestClass->objectName().isEmpty())
            ModuleTestClass->setObjectName(QString::fromUtf8("ModuleTestClass"));
        ModuleTestClass->resize(600, 400);
        menuBar = new QMenuBar(ModuleTestClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        ModuleTestClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ModuleTestClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ModuleTestClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(ModuleTestClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        ModuleTestClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ModuleTestClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ModuleTestClass->setStatusBar(statusBar);

        retranslateUi(ModuleTestClass);

        QMetaObject::connectSlotsByName(ModuleTestClass);
    } // setupUi

    void retranslateUi(QMainWindow *ModuleTestClass)
    {
        ModuleTestClass->setWindowTitle(QApplication::translate("ModuleTestClass", "ModuleTest", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ModuleTestClass: public Ui_ModuleTestClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODULETEST_H
