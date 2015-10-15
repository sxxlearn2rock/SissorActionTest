/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu Oct 15 21:03:04 2015
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
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *acReadVideo;
    QAction *acExit;
    QWidget *centralWidget;
    QLabel *label;
    QLabel *labelInputFrame;
    QFrame *frameInputBox;
    QPushButton *btnStartDetect;
    QLabel *labelOutputFrame;
    QFrame *frameOutputBox;
    QLabel *label_2;
    QLabel *labelSegmentFrame;
    QLabel *label_3;
    QFrame *frameSegmentBox;
    QLabel *labelDenoiseFrame;
    QLabel *label_4;
    QFrame *frameDenoiseBox;
    QComboBox *comboDenoise;
    QMenuBar *menuBar;
    QMenu *menu_F;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(960, 641);
        acReadVideo = new QAction(MainWindowClass);
        acReadVideo->setObjectName(QString::fromUtf8("acReadVideo"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Resources/open_video.png"), QSize(), QIcon::Normal, QIcon::Off);
        acReadVideo->setIcon(icon);
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
        labelInputFrame->setGeometry(QRect(20, 40, 321, 241));
        labelInputFrame->setLayoutDirection(Qt::LeftToRight);
        frameInputBox = new QFrame(centralWidget);
        frameInputBox->setObjectName(QString::fromUtf8("frameInputBox"));
        frameInputBox->setGeometry(QRect(20, 40, 320, 240));
        frameInputBox->setFrameShape(QFrame::Panel);
        frameInputBox->setFrameShadow(QFrame::Sunken);
        frameInputBox->setLineWidth(3);
        frameInputBox->setMidLineWidth(1);
        btnStartDetect = new QPushButton(centralWidget);
        btnStartDetect->setObjectName(QString::fromUtf8("btnStartDetect"));
        btnStartDetect->setGeometry(QRect(340, 130, 101, 61));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Resources/start_detect.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnStartDetect->setIcon(icon2);
        btnStartDetect->setIconSize(QSize(32, 32));
        labelOutputFrame = new QLabel(centralWidget);
        labelOutputFrame->setObjectName(QString::fromUtf8("labelOutputFrame"));
        labelOutputFrame->setGeometry(QRect(440, 40, 321, 241));
        frameOutputBox = new QFrame(centralWidget);
        frameOutputBox->setObjectName(QString::fromUtf8("frameOutputBox"));
        frameOutputBox->setGeometry(QRect(440, 40, 320, 240));
        frameOutputBox->setFrameShape(QFrame::Panel);
        frameOutputBox->setFrameShadow(QFrame::Sunken);
        frameOutputBox->setLineWidth(3);
        frameOutputBox->setMidLineWidth(1);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(440, 20, 81, 16));
        label_2->setFont(font);
        labelSegmentFrame = new QLabel(centralWidget);
        labelSegmentFrame->setObjectName(QString::fromUtf8("labelSegmentFrame"));
        labelSegmentFrame->setGeometry(QRect(440, 330, 321, 241));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(440, 310, 81, 16));
        label_3->setFont(font);
        frameSegmentBox = new QFrame(centralWidget);
        frameSegmentBox->setObjectName(QString::fromUtf8("frameSegmentBox"));
        frameSegmentBox->setGeometry(QRect(440, 330, 320, 240));
        frameSegmentBox->setFrameShape(QFrame::Panel);
        frameSegmentBox->setFrameShadow(QFrame::Sunken);
        frameSegmentBox->setLineWidth(3);
        frameSegmentBox->setMidLineWidth(1);
        labelDenoiseFrame = new QLabel(centralWidget);
        labelDenoiseFrame->setObjectName(QString::fromUtf8("labelDenoiseFrame"));
        labelDenoiseFrame->setGeometry(QRect(20, 330, 321, 241));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 310, 131, 16));
        label_4->setFont(font);
        frameDenoiseBox = new QFrame(centralWidget);
        frameDenoiseBox->setObjectName(QString::fromUtf8("frameDenoiseBox"));
        frameDenoiseBox->setGeometry(QRect(20, 330, 320, 240));
        frameDenoiseBox->setFrameShape(QFrame::Panel);
        frameDenoiseBox->setFrameShadow(QFrame::Sunken);
        frameDenoiseBox->setLineWidth(3);
        frameDenoiseBox->setMidLineWidth(1);
        comboDenoise = new QComboBox(centralWidget);
        comboDenoise->setObjectName(QString::fromUtf8("comboDenoise"));
        comboDenoise->setGeometry(QRect(200, 300, 141, 22));
        MainWindowClass->setCentralWidget(centralWidget);
        labelDenoiseFrame->raise();
        frameDenoiseBox->raise();
        frameSegmentBox->raise();
        label->raise();
        labelInputFrame->raise();
        frameInputBox->raise();
        btnStartDetect->raise();
        labelOutputFrame->raise();
        frameOutputBox->raise();
        label_2->raise();
        labelSegmentFrame->raise();
        label_3->raise();
        label_4->raise();
        comboDenoise->raise();
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
        menu_F->addAction(acReadVideo);
        menu_F->addSeparator();
        menu_F->addAction(acExit);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", 0, QApplication::UnicodeUTF8));
        acReadVideo->setText(QApplication::translate("MainWindowClass", "\350\257\273\345\217\226\350\247\206\351\242\221(&R)", 0, QApplication::UnicodeUTF8));
        acReadVideo->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        acExit->setText(QApplication::translate("MainWindowClass", "\351\200\200\345\207\272\347\250\213\345\272\217", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindowClass", "\345\216\237\345\247\213\350\247\206\351\242\221\357\274\232", 0, QApplication::UnicodeUTF8));
        labelInputFrame->setText(QApplication::translate("MainWindowClass", "                     \345\216\237\345\247\213\350\247\206\351\242\221\345\270\247", 0, QApplication::UnicodeUTF8));
        btnStartDetect->setText(QApplication::translate("MainWindowClass", "\345\274\200\345\247\213\346\243\200\346\265\213", 0, QApplication::UnicodeUTF8));
        labelOutputFrame->setText(QApplication::translate("MainWindowClass", "                     \350\276\223\345\207\272\350\247\206\351\242\221\345\270\247", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindowClass", "\346\243\200\346\265\213\347\273\223\346\236\234\357\274\232", 0, QApplication::UnicodeUTF8));
        labelSegmentFrame->setText(QApplication::translate("MainWindowClass", "                     \345\210\206\345\211\262\345\220\216\346\225\210\346\236\234\345\270\247", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindowClass", "\345\210\206\345\211\262\347\273\223\346\236\234\357\274\232", 0, QApplication::UnicodeUTF8));
        labelDenoiseFrame->setText(QApplication::translate("MainWindowClass", "                  \350\203\214\346\231\257\346\212\221\345\210\266\345\220\216\346\225\210\346\236\234\345\270\247", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindowClass", "\350\203\214\346\231\257\346\212\221\345\210\266\347\273\223\346\236\234\357\274\232", 0, QApplication::UnicodeUTF8));
        comboDenoise->clear();
        comboDenoise->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "\351\273\230\350\256\244\345\216\273\345\231\252\347\256\227\346\263\225", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\346\265\213\350\257\225\345\216\273\345\231\252\347\256\227\346\263\2251", 0, QApplication::UnicodeUTF8)
        );
        menu_F->setTitle(QApplication::translate("MainWindowClass", "\346\226\207\344\273\266(&F)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
