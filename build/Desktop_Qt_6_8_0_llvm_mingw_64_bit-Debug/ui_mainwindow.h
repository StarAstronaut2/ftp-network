/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <qmylistwidget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *returnMain;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QStackedWidget *switchWidget;
    QWidget *login;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout;
    QLineEdit *ip;
    QLabel *label_2;
    QLineEdit *password;
    QLineEdit *user;
    QLabel *label_4;
    QLabel *label;
    QPushButton *connect;
    QWidget *transfer;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *transferLayout;
    QLineEdit *localPath;
    QMyListWidget *local;
    QLineEdit *targetPath;
    QMyListWidget *target;
    QMenuBar *menubar;
    QMenu *menu;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1200, 943);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1200, 900));
        MainWindow->setMaximumSize(QSize(1201, 943));
        returnMain = new QAction(MainWindow);
        returnMain->setObjectName("returnMain");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy1);
        centralwidget->setMinimumSize(QSize(1200, 950));
        centralwidget->setMaximumSize(QSize(1200, 950));
        centralwidget->setAutoFillBackground(false);
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName("gridLayout_2");
        switchWidget = new QStackedWidget(centralwidget);
        switchWidget->setObjectName("switchWidget");
        switchWidget->setMinimumSize(QSize(1100, 900));
        switchWidget->setSizeIncrement(QSize(0, 0));
        switchWidget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        switchWidget->setAutoFillBackground(false);
        login = new QWidget();
        login->setObjectName("login");
        sizePolicy1.setHeightForWidth(login->sizePolicy().hasHeightForWidth());
        login->setSizePolicy(sizePolicy1);
        login->setMinimumSize(QSize(1200, 900));
        login->setAutoFillBackground(false);
        layoutWidget = new QWidget(login);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(400, 230, 361, 281));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(6, 6, 6, 6);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(10);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(6, 6, 6, 6);
        ip = new QLineEdit(layoutWidget);
        ip->setObjectName("ip");
        ip->setMinimumSize(QSize(150, 25));

        gridLayout->addWidget(ip, 0, 1, 1, 1);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName("label_2");
        label_2->setMinimumSize(QSize(50, 30));
        label_2->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_2, 0, 0, 1, 1, Qt::AlignmentFlag::AlignLeft);

        password = new QLineEdit(layoutWidget);
        password->setObjectName("password");
        password->setMinimumSize(QSize(150, 25));

        gridLayout->addWidget(password, 2, 1, 1, 1);

        user = new QLineEdit(layoutWidget);
        user->setObjectName("user");
        user->setMinimumSize(QSize(150, 25));

        gridLayout->addWidget(user, 1, 1, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName("label_4");
        label_4->setMinimumSize(QSize(50, 30));
        label_4->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label_4, 1, 0, 1, 1, Qt::AlignmentFlag::AlignHCenter);

        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        label->setMinimumSize(QSize(50, 30));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label, 2, 0, 1, 1, Qt::AlignmentFlag::AlignHCenter);


        verticalLayout_3->addLayout(gridLayout);

        connect = new QPushButton(layoutWidget);
        connect->setObjectName("connect");
        connect->setMinimumSize(QSize(50, 0));
        connect->setSizeIncrement(QSize(0, 50));

        verticalLayout_3->addWidget(connect, 0, Qt::AlignmentFlag::AlignHCenter);

        switchWidget->addWidget(login);
        transfer = new QWidget();
        transfer->setObjectName("transfer");
        sizePolicy.setHeightForWidth(transfer->sizePolicy().hasHeightForWidth());
        transfer->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(transfer);
        verticalLayout_2->setObjectName("verticalLayout_2");
        transferLayout = new QGridLayout();
        transferLayout->setSpacing(0);
        transferLayout->setObjectName("transferLayout");
        transferLayout->setContentsMargins(0, 0, 0, 0);
        localPath = new QLineEdit(transfer);
        localPath->setObjectName("localPath");

        transferLayout->addWidget(localPath, 0, 0, 1, 1);

        local = new QMyListWidget(transfer);
        local->setObjectName("local");
        local->setMinimumSize(QSize(500, 0));

        transferLayout->addWidget(local, 1, 0, 1, 1);

        targetPath = new QLineEdit(transfer);
        targetPath->setObjectName("targetPath");

        transferLayout->addWidget(targetPath, 0, 1, 1, 1);

        target = new QMyListWidget(transfer);
        target->setObjectName("target");
        sizePolicy.setHeightForWidth(target->sizePolicy().hasHeightForWidth());
        target->setSizePolicy(sizePolicy);
        target->setMinimumSize(QSize(500, 0));

        transferLayout->addWidget(target, 1, 1, 1, 1);


        verticalLayout_2->addLayout(transferLayout);

        switchWidget->addWidget(transfer);

        gridLayout_2->addWidget(switchWidget, 0, 0, 1, 1, Qt::AlignmentFlag::AlignHCenter|Qt::AlignmentFlag::AlignVCenter);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1200, 18));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);
        QWidget::setTabOrder(ip, user);
        QWidget::setTabOrder(user, password);
        QWidget::setTabOrder(password, connect);
        QWidget::setTabOrder(connect, localPath);
        QWidget::setTabOrder(localPath, local);
        QWidget::setTabOrder(local, targetPath);
        QWidget::setTabOrder(targetPath, target);

        menubar->addAction(menu->menuAction());
        menu->addAction(returnMain);

        retranslateUi(MainWindow);

        switchWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "FTP", nullptr));
        returnMain->setText(QCoreApplication::translate("MainWindow", "\350\277\224\345\233\236", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "IP", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\347\224\250\346\210\267", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\257\206\347\240\201", nullptr));
        connect->setText(QCoreApplication::translate("MainWindow", "\350\277\236\346\216\245", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\350\217\234\345\215\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
