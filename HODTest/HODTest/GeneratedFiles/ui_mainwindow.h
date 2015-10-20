/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Oct 20 14:52:05 2015
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
#include <QtGui/QHBoxLayout>
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
    QAction *acStartDetect;
    QWidget *centralWidget;
    QLabel *label;
    QLabel *labelInputFrame;
    QFrame *frameInputBox;
    QLabel *labelOutputFrame;
    QFrame *frameOutputBox;
    QLabel *label_2;
    QLabel *labelSegmentFrame;
    QLabel *label_3;
    QFrame *frameSegmentBox;
    QLabel *labelDenoiseFrame;
    QLabel *label_4;
    QFrame *frameDenoiseBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *comboSegment;
    QPushButton *btnConfigSeg;
    QLabel *label_5;
    QFrame *frameRecog;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *comboRecog;
    QPushButton *btnConfigRecog;
    QLabel *labelRecog;
    QLabel *label_6;
    QLabel *labelMorphFrame;
    QFrame *frameMorphBox;
    QPushButton *btnConfigMorph;
    QComboBox *comboDenoise;
    QPushButton *btnConfigDenoise;
    QMenuBar *menuBar;
    QMenu *menu_F;
    QMenu *menu_R;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(1083, 622);
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
        acStartDetect = new QAction(MainWindowClass);
        acStartDetect->setObjectName(QString::fromUtf8("acStartDetect"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Resources/start_detect.png"), QSize(), QIcon::Normal, QIcon::Off);
        acStartDetect->setIcon(icon2);
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
        labelOutputFrame = new QLabel(centralWidget);
        labelOutputFrame->setObjectName(QString::fromUtf8("labelOutputFrame"));
        labelOutputFrame->setGeometry(QRect(740, 310, 321, 241));
        frameOutputBox = new QFrame(centralWidget);
        frameOutputBox->setObjectName(QString::fromUtf8("frameOutputBox"));
        frameOutputBox->setGeometry(QRect(740, 310, 320, 240));
        frameOutputBox->setFrameShape(QFrame::Panel);
        frameOutputBox->setFrameShadow(QFrame::Sunken);
        frameOutputBox->setLineWidth(3);
        frameOutputBox->setMidLineWidth(1);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(740, 290, 121, 16));
        label_2->setFont(font);
        labelSegmentFrame = new QLabel(centralWidget);
        labelSegmentFrame->setObjectName(QString::fromUtf8("labelSegmentFrame"));
        labelSegmentFrame->setGeometry(QRect(740, 40, 321, 241));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(740, 20, 81, 16));
        label_3->setFont(font);
        frameSegmentBox = new QFrame(centralWidget);
        frameSegmentBox->setObjectName(QString::fromUtf8("frameSegmentBox"));
        frameSegmentBox->setGeometry(QRect(740, 40, 320, 240));
        frameSegmentBox->setFrameShape(QFrame::Panel);
        frameSegmentBox->setFrameShadow(QFrame::Sunken);
        frameSegmentBox->setLineWidth(3);
        frameSegmentBox->setMidLineWidth(1);
        labelDenoiseFrame = new QLabel(centralWidget);
        labelDenoiseFrame->setObjectName(QString::fromUtf8("labelDenoiseFrame"));
        labelDenoiseFrame->setGeometry(QRect(380, 40, 321, 241));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(380, 20, 131, 16));
        label_4->setFont(font);
        frameDenoiseBox = new QFrame(centralWidget);
        frameDenoiseBox->setObjectName(QString::fromUtf8("frameDenoiseBox"));
        frameDenoiseBox->setGeometry(QRect(380, 40, 320, 240));
        frameDenoiseBox->setFrameShape(QFrame::Panel);
        frameDenoiseBox->setFrameShadow(QFrame::Sunken);
        frameDenoiseBox->setLineWidth(3);
        frameDenoiseBox->setMidLineWidth(1);
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(870, 10, 186, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        comboSegment = new QComboBox(layoutWidget);
        comboSegment->setObjectName(QString::fromUtf8("comboSegment"));

        horizontalLayout_2->addWidget(comboSegment);

        btnConfigSeg = new QPushButton(layoutWidget);
        btnConfigSeg->setObjectName(QString::fromUtf8("btnConfigSeg"));

        horizontalLayout_2->addWidget(btnConfigSeg);

        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(380, 290, 131, 16));
        label_5->setFont(font);
        frameRecog = new QFrame(centralWidget);
        frameRecog->setObjectName(QString::fromUtf8("frameRecog"));
        frameRecog->setGeometry(QRect(380, 310, 320, 240));
        frameRecog->setFrameShape(QFrame::Panel);
        frameRecog->setFrameShadow(QFrame::Sunken);
        frameRecog->setLineWidth(3);
        frameRecog->setMidLineWidth(1);
        layoutWidget_2 = new QWidget(centralWidget);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(510, 280, 187, 25));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        comboRecog = new QComboBox(layoutWidget_2);
        comboRecog->setObjectName(QString::fromUtf8("comboRecog"));

        horizontalLayout_3->addWidget(comboRecog);

        btnConfigRecog = new QPushButton(layoutWidget_2);
        btnConfigRecog->setObjectName(QString::fromUtf8("btnConfigRecog"));

        horizontalLayout_3->addWidget(btnConfigRecog);

        labelRecog = new QLabel(centralWidget);
        labelRecog->setObjectName(QString::fromUtf8("labelRecog"));
        labelRecog->setGeometry(QRect(380, 310, 321, 241));
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 290, 131, 16));
        label_6->setFont(font);
        labelMorphFrame = new QLabel(centralWidget);
        labelMorphFrame->setObjectName(QString::fromUtf8("labelMorphFrame"));
        labelMorphFrame->setGeometry(QRect(20, 310, 321, 241));
        frameMorphBox = new QFrame(centralWidget);
        frameMorphBox->setObjectName(QString::fromUtf8("frameMorphBox"));
        frameMorphBox->setGeometry(QRect(20, 310, 320, 240));
        frameMorphBox->setFrameShape(QFrame::Panel);
        frameMorphBox->setFrameShadow(QFrame::Sunken);
        frameMorphBox->setLineWidth(3);
        frameMorphBox->setMidLineWidth(1);
        btnConfigMorph = new QPushButton(centralWidget);
        btnConfigMorph->setObjectName(QString::fromUtf8("btnConfigMorph"));
        btnConfigMorph->setGeometry(QRect(260, 280, 75, 23));
        comboDenoise = new QComboBox(centralWidget);
        comboDenoise->setObjectName(QString::fromUtf8("comboDenoise"));
        comboDenoise->setGeometry(QRect(490, 14, 161, 20));
        btnConfigDenoise = new QPushButton(centralWidget);
        btnConfigDenoise->setObjectName(QString::fromUtf8("btnConfigDenoise"));
        btnConfigDenoise->setGeometry(QRect(652, 13, 51, 23));
        MainWindowClass->setCentralWidget(centralWidget);
        comboDenoise->raise();
        btnConfigDenoise->raise();
        btnConfigMorph->raise();
        frameMorphBox->raise();
        labelRecog->raise();
        labelMorphFrame->raise();
        frameOutputBox->raise();
        frameDenoiseBox->raise();
        frameRecog->raise();
        layoutWidget->raise();
        labelDenoiseFrame->raise();
        frameSegmentBox->raise();
        label->raise();
        labelInputFrame->raise();
        frameInputBox->raise();
        labelOutputFrame->raise();
        label_2->raise();
        labelSegmentFrame->raise();
        label_3->raise();
        label_4->raise();
        label_5->raise();
        layoutWidget_2->raise();
        label_6->raise();
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1083, 23));
        menu_F = new QMenu(menuBar);
        menu_F->setObjectName(QString::fromUtf8("menu_F"));
        menu_R = new QMenu(menuBar);
        menu_R->setObjectName(QString::fromUtf8("menu_R"));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menu_F->menuAction());
        menuBar->addAction(menu_R->menuAction());
        menu_F->addAction(acReadVideo);
        menu_F->addSeparator();
        menu_F->addAction(acExit);
        menu_R->addAction(acStartDetect);
        mainToolBar->addSeparator();

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", 0, QApplication::UnicodeUTF8));
        acReadVideo->setText(QApplication::translate("MainWindowClass", "\350\257\273\345\217\226\350\247\206\351\242\221(&R)", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        acReadVideo->setToolTip(QApplication::translate("MainWindowClass", "\350\257\273\345\217\226\350\247\206\351\242\221\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        acReadVideo->setShortcut(QApplication::translate("MainWindowClass", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        acExit->setText(QApplication::translate("MainWindowClass", "\351\200\200\345\207\272\347\250\213\345\272\217", 0, QApplication::UnicodeUTF8));
        acStartDetect->setText(QApplication::translate("MainWindowClass", "\345\274\200\345\247\213\346\243\200\346\265\213", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindowClass", "\345\216\237\345\247\213\350\247\206\351\242\221:", 0, QApplication::UnicodeUTF8));
        labelInputFrame->setText(QApplication::translate("MainWindowClass", "                     \345\216\237\345\247\213\350\247\206\351\242\221\345\270\247", 0, QApplication::UnicodeUTF8));
        labelOutputFrame->setText(QString());
        label_2->setText(QApplication::translate("MainWindowClass", "\350\236\215\345\220\210\350\276\223\345\207\272\347\273\223\346\236\234:", 0, QApplication::UnicodeUTF8));
        labelSegmentFrame->setText(QString());
        label_3->setText(QApplication::translate("MainWindowClass", "\345\210\206\345\211\262\347\273\223\346\236\234:", 0, QApplication::UnicodeUTF8));
        labelDenoiseFrame->setText(QString());
        label_4->setText(QApplication::translate("MainWindowClass", "\350\203\214\346\231\257\346\212\221\345\210\266\347\273\223\346\236\234:", 0, QApplication::UnicodeUTF8));
        comboSegment->clear();
        comboSegment->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "\351\273\230\350\256\244\345\210\206\345\211\262\347\256\227\346\263\225", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "OtsuSegment", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "KswSegment", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "Ksw2dSegment", 0, QApplication::UnicodeUTF8)
        );
        btnConfigSeg->setText(QApplication::translate("MainWindowClass", "\351\205\215\347\275\256\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindowClass", "\350\257\206\345\210\253\347\273\223\346\236\234:", 0, QApplication::UnicodeUTF8));
        comboRecog->clear();
        comboRecog->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "\351\273\230\350\256\244\350\257\206\345\210\253\347\256\227\346\263\225", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\346\265\213\350\257\225\350\257\206\345\210\253\347\256\227\346\263\2251", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\346\265\213\350\257\225\350\257\206\345\210\253\347\256\227\346\263\2252", 0, QApplication::UnicodeUTF8)
        );
        btnConfigRecog->setText(QApplication::translate("MainWindowClass", "\351\205\215\347\275\256\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        labelRecog->setText(QString());
        label_6->setText(QApplication::translate("MainWindowClass", "\345\275\242\346\200\201\345\255\246\346\273\244\346\263\242\347\273\223\346\236\234:", 0, QApplication::UnicodeUTF8));
        labelMorphFrame->setText(QString());
        btnConfigMorph->setText(QApplication::translate("MainWindowClass", "\351\205\215\347\275\256\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        comboDenoise->clear();
        comboDenoise->insertItems(0, QStringList()
         << QApplication::translate("MainWindowClass", "\351\273\230\350\256\244(\344\273\205\347\201\260\345\272\246\345\214\226)", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\344\276\247\346\212\221\345\210\266\347\275\221\347\273\234\345\242\236\345\274\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\347\233\264\346\226\271\345\233\276\345\217\214\345\220\221\345\242\236\345\274\272", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\345\210\206\345\275\242\347\256\227\346\263\225", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\346\234\200\345\244\247\344\270\255\345\200\274\346\273\244\346\263\242\350\203\214\346\231\257\346\212\221\345\210\266", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\345\233\272\345\256\232\346\235\203\345\200\274\350\203\214\346\231\257\351\242\204\346\265\213", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\350\207\252\351\200\202\345\272\224\346\235\203\345\200\274\350\203\214\346\231\257\351\242\204\346\265\213", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\345\214\272\345\237\237\346\234\200\345\244\247\345\214\226\350\203\214\346\231\257\351\242\204\346\265\213", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\345\261\200\351\203\250\345\235\207\345\200\274\345\257\271\346\257\224\345\272\246\350\203\214\346\231\257\346\212\221\345\210\266", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\345\261\200\351\203\250\347\206\265\350\203\214\346\231\257\346\212\221\345\210\266", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\345\261\200\351\203\250\346\226\271\345\267\256\350\203\214\346\231\257\346\212\221\345\210\266", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\344\270\200\347\273\264\345\220\204\351\241\271\345\274\202\346\200\247\346\273\244\346\263\242", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\344\272\214\347\273\264\345\220\204\345\220\221\345\274\202\346\200\247\346\273\244\346\263\242", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindowClass", "\346\224\271\350\277\233\345\236\213\345\220\204\351\241\271\345\274\202\346\200\247\346\273\244\346\263\242", 0, QApplication::UnicodeUTF8)
        );
        btnConfigDenoise->setText(QApplication::translate("MainWindowClass", "config", 0, QApplication::UnicodeUTF8));
        menu_F->setTitle(QApplication::translate("MainWindowClass", "\346\226\207\344\273\266(&F)", 0, QApplication::UnicodeUTF8));
        menu_R->setTitle(QApplication::translate("MainWindowClass", "\350\277\220\350\241\214(&R)", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
