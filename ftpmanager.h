#ifndef FTPMANAGER_H
#define FTPMANAGER_H
#include <QDir>
#include <QListWidget>
#include <QLineEdit>
#include <QNetworkAccessManager>
#include <QMessageBox>
#include <QNetworkReply>
#include <QTimer>
#include "qmylistwidget.h"
#include <QRegularExpression>

struct fileSystem{
    QDir* currentDir;
    QMyListWidget* ui;
    QLineEdit* path;

    fileSystem(QString filePath, QMyListWidget* ui, QLineEdit* path)
        :ui(ui), path(path)
    {
        this->currentDir=new QDir(filePath);
        this->currentDir->setFilter(QDir::AllEntries | QDir::NoDot);
    }

    ~fileSystem()
    {
        delete currentDir;
    }
};


class ftpManager
{
public:
    ftpManager(QWidget *parent, QMyListWidget* local, QMyListWidget* target, QLineEdit* localPath, QLineEdit*targetPath);
    ~ftpManager();

    void showDirEntry(fileSystem* toshow);
    void bind(fileSystem* tobind);
    void setUrl(QString ip, QString user, QString password);
    bool connectUrl();

    void send(const QString localPath, const QString targetPath);
    void receive(const QString localPath, const QString targetPath);

private:
    fileSystem* local, *target;
    QNetworkAccessManager manager;
    QUrl pUrl;
    QWidget *parent;
};

#endif // FTPMANAGER_H
