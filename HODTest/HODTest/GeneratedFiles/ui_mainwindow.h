/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Sep 29 13:54:35 2015
**      by: Qt User Interface Compiler version 4.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *acOpenVideo;
    QAction *acExit;
    QWidget *centralWidget;
    QLabel *label;
    QLabel *labelInputFrame;
    QFrame *frameInputBox;
    QMenuBar *menuBar;
    QMenu *menu_F;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(960, 624);
        acOpenVideo = new QAction(MainWindowClass);
        acOpenVideo->setObjectName(QString::fromUtf8("acOpenVideo"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/open_video.png"), QSize(), QIcon::Normal, QIcon::Off);
        acOpenVideo->setIcon(icon);
        acExit = new QAction(MainWindowClass);
        acExit->setObjectName(QString::fromUtf8("acExit"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Resources/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        acExit->setIcon(icon1);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 81, 16));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        label->setFont(font);
        labelInputFrame = new QLabel(centralWidget);
        labelInputFrame->setObjectName(QString::fromUtf8("labelInputFrame"));
        labelInputFrame->setGeometry(QRect(20, 40, 71, 16));
        frameInputBox = new QFrame(centralWidget);
        frameInputBox->setObjectName(QString::fromUtf8("frameInputBox"));
        frameInputBox->setGeometry(QRect(20, 40, 320, 240));
        frameInputBox->setFrameShape(QFrame::Panel);
        frameInputBox->setFrameShadow(QFrame::Sunken);
        frameInputBox->setLineWidth(3);
        frameInputBox->setMidLineWidth(1);
        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 960, 23));
        menu_F = new QMenu(menuBar);
        menu_F->setObjectName(QString::fromUtf8("menu_F"));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menu_F->menuAction());
        menu_F->addAction(acOpenVideo);
        menu_F->addSeparator();
        menu_F->addAction(acExit);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", 0, QApplication::UnicodeUTF8));
        acOpenVideo->setText(QApplication::translate("MainWindowClass", "\346\211\223\345\274\200\350\247\206\351\242\221(&O)", 0, QApplication::UnicodeUTF8));
        acOpenVideo->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        acExit->setText(QApplication::translate("MainWindowClass", "\351\200\200\345\207\272\347\250\213\345\272\217", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindowClass", "\345\216\237\345\247\213\350\247\206\351\242\221\357\274\232", 0, QApplication::UnicodeUTF8));
        labelInputFrame->setText(QApplication::translate("MainWindowClass", "\345\216\237\345\247\213\350\247\206\351\242\221\345\270\247", 0, QApplication::UnicodeUTF8));
        menu_F->setTitle(QApplication::translate("MainWindowClass", "\346\226\207\344\273\266(&F)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
