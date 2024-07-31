#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>
#include <QUrl>
#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QPushButton>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->returnMain,&QAction::triggered,[=](){
        ui->switchWidget->setCurrentIndex(0);
    });


    ftp = new ftpManager(this, ui->local, ui->target, ui->localPath, ui->targetPath);
    connect(ui->connect,&QPushButton::clicked,[=](){
        ftp->setUrl(ui->ip->text(), ui->user->text(), ui->password->text());
        if(ftp->connectUrl())
            ui->switchWidget->setCurrentIndex(1);
    });
}

MainWindow::~MainWindow()
{
    delete ftp;
    delete ui;
}

