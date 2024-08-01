#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置整个窗口的背景颜色
    QPalette palette = this->palette();
    palette.setColor(QPalette::Window, QColor(230, 230, 250)); // 设置背景颜色为浅紫色
    this->setPalette(palette);

    // 设置各个控件的字体大小和样式
    QFont font;
    font.setPointSize(16);
    ui->ip->setFont(font);
    ui->user->setFont(font);
    ui->password->setFont(font);

    // 设置标签的字体
    QFont labelFont;
    labelFont.setPointSize(16);

    ui->label->setFont(labelFont);
    ui->label_2->setFont(labelFont);
    ui->label_4->setFont(labelFont);

    // 设置按钮样式
    ui->connect->setFont(font);
    ui->connect->setStyleSheet("QPushButton { background-color: lightblue; padding: 10px; border-radius: 5px; }");

    // 设置 QLineEdit 样式
    ui->ip->setStyleSheet("QLineEdit { padding: 5px; border: 1px solid gray; border-radius: 5px; }");
    ui->user->setStyleSheet("QLineEdit { padding: 5px; border: 1px solid gray; border-radius: 5px; }");
    ui->password->setStyleSheet("QLineEdit { padding: 5px; border: 1px solid gray; border-radius: 5px; }");

    // 设置菜单栏和菜单项的样式，包括圆角效果
    ui->menubar->setStyleSheet(
        "QMenuBar { background-color: #9370DB; color: white; font-size:16px;font-weight: bold;}"
        "QMenuBar::item { background-color: #9370DB; color: white; padding: 5px 10px; }"
        "QMenuBar::item:selected { background-color: #B19CD9; }"
        "QMenu { background-color: #9370DB; color: white; border: 1px solid #9370DB; }"
        "QMenu::item { background-color: #9370DB; color: white; padding: 5px 10px;font-size:16px;font-weight: bold;}"
        "QMenu::item:selected { background-color: #B19CD9; }");

    // 连接信号和槽
    connect(ui->returnMain, &QAction::triggered, [=]()
            { ui->switchWidget->setCurrentIndex(0); });

    ftp = new ftpManager(this, ui->local, ui->target, ui->localPath, ui->targetPath);
    connect(ui->connect, &QPushButton::clicked, [=]()
            {
        ftp->setUrl(ui->ip->text(), ui->user->text(), ui->password->text());
        if (ftp->connectUrl())
            ui->switchWidget->setCurrentIndex(1); });
}

MainWindow::~MainWindow()
{
    delete ftp;
    delete ui;
}
