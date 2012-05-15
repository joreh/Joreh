/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Fri May 11 06:47:57 2012
**      by: Qt User Interface Compiler version 4.8.1
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
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "GUI/GraphicsView.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
    QAction *actionClear;
    QAction *actionExit;
    QAction *actionShow_Options;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    graphicsview *graphicsView;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QLabel *ipLable;
    QLineEdit *ipEdit;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_4;
    QPushButton *connectButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuOptions;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QString::fromUtf8("MainWindowClass"));
        MainWindowClass->resize(607, 537);
        MainWindowClass->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0.288991 rgba(179, 31, 0, 255), stop:1 rgba(255, 255, 255, 255));"));
        actionClear = new QAction(MainWindowClass);
        actionClear->setObjectName(QString::fromUtf8("actionClear"));
        actionExit = new QAction(MainWindowClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionShow_Options = new QAction(MainWindowClass);
        actionShow_Options->setObjectName(QString::fromUtf8("actionShow_Options"));
        actionShow_Options->setCheckable(true);
        actionShow_Options->setChecked(true);
        centralWidget = new QWidget(MainWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        graphicsView = new graphicsview(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        verticalLayout->addWidget(graphicsView);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setMinimumSize(QSize(0, 110));
        groupBox->setMaximumSize(QSize(16777215, 110));
        groupBox->setAlignment(Qt::AlignCenter);
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        frame = new QFrame(groupBox);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(100);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        ipLable = new QLabel(frame);
        ipLable->setObjectName(QString::fromUtf8("ipLable"));
        ipLable->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(ipLable);

        ipEdit = new QLineEdit(frame);
        ipEdit->setObjectName(QString::fromUtf8("ipEdit"));

        verticalLayout_3->addWidget(ipEdit);


        horizontalLayout->addWidget(frame);

        frame_2 = new QFrame(groupBox);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_4 = new QVBoxLayout(frame_2);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        connectButton = new QPushButton(frame_2);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));

        verticalLayout_4->addWidget(connectButton);


        horizontalLayout->addWidget(frame_2);


        verticalLayout->addWidget(groupBox);

        MainWindowClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 607, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        MainWindowClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindowClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuOptions->menuAction());
        menuFile->addAction(actionExit);
        menuOptions->addAction(actionShow_Options);

        retranslateUi(MainWindowClass);

        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "Swarming Monitor", 0, QApplication::UnicodeUTF8));
        actionClear->setText(QApplication::translate("MainWindowClass", "Clear", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindowClass", "Exit", 0, QApplication::UnicodeUTF8));
        actionShow_Options->setText(QApplication::translate("MainWindowClass", "Show Options", 0, QApplication::UnicodeUTF8));
        groupBox->setStyleSheet(QApplication::translate("MainWindowClass", "background-color: rgb(209, 0, 0);\n"
"background-color: rgb(255, 255, 255);", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindowClass", "Option", 0, QApplication::UnicodeUTF8));
        ipLable->setText(QApplication::translate("MainWindowClass", "IP and Port", 0, QApplication::UnicodeUTF8));
        ipEdit->setText(QApplication::translate("MainWindowClass", "127.0.0.1:6179", 0, QApplication::UnicodeUTF8));
        connectButton->setText(QApplication::translate("MainWindowClass", "Connect", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindowClass", "File", 0, QApplication::UnicodeUTF8));
        menuOptions->setTitle(QApplication::translate("MainWindowClass", "Window", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
