#include "ftpmanager.h"
#include <QDebug>
ftpManager::ftpManager(QWidget *parent, QMyListWidget* local, QMyListWidget* target, QLineEdit* localPath, QLineEdit* targetPath)
        :parent(parent)
{
    this->local = new fileSystem(QDir::rootPath(), local, localPath);
    this->target = new fileSystem("", target, targetPath);

    this->local->ui->setMenu("上传");
    this->target->ui->setMenu("下载");

    QObject::connect(this->local->ui,&QMyListWidget::load,[=](QString selectedItem){
        QString path=this->local->currentDir->path();
        if(path[path.size()-1]=='/')path.remove(path.size()-1,1);
        send(path+selectedItem,this->target->currentDir->path());
    });

    QObject::connect(this->target->ui,&QMyListWidget::load,[=](QString selectedItem){
        QString path=this->target->currentDir->path();
        if(path[path.size()-1]=='/')path.remove(path.size()-1,1);
        receive(this->local->currentDir->path(),path+selectedItem);
    });

    this->local->path->setText(this->local->currentDir->path());
    showDirEntry(this->local);

    bind(this->local);
    bind(this->target);

    pUrl.setScheme("ftp");
    pUrl.setPort(21);
}

void ftpManager::showDirEntry(fileSystem* toshow)
{
    toshow->ui->clear();
    for(auto& filename:toshow->currentDir->entryList())
    {
        toshow->ui->addItem(filename);
    }
}

void ftpManager::bind(fileSystem* tobind)
{
    QObject::connect(tobind->ui, &QListWidget::itemDoubleClicked,
                      [=](QListWidgetItem* clickedItem){
        tobind->currentDir->cd(clickedItem->text());
        tobind->path->setText(tobind->currentDir->path());
        showDirEntry(tobind);
    });
    QObject::connect(tobind->path, &QLineEdit::returnPressed,
                      [=](){
        if(QDir(tobind->path->text()).exists())
        {
            if(tobind->path->text() != tobind->currentDir->path())
            {
                tobind->currentDir->setPath(tobind->path->text());
                showDirEntry(tobind);
            }
        }
        else
        {
            QMessageBox::information(parent,"目录不存在","目录不存在");
            tobind->path->setText(tobind->currentDir->path());
        }
    });
}

void ftpManager::setUrl(QString ip, QString user, QString password)
{
    pUrl.setHost(ip);
    pUrl.setUserName(user);
    pUrl.setPassword(password);
    //qDebug()<<pUrl.toString()<<endl;
}
bool ftpManager::connectUrl()
{
    if (!pUrl.isValid())
    {
        QMessageBox::information(parent, "链接无效", "链接无效");
        return false;
    }

    pUrl.setPath("/");
    target->currentDir->setPath("\\\\" + pUrl.host() + '/');

    QTcpSocket socket;
    socket.abort(); // 取消原有连接
    socket.connectToHost(pUrl.host(), 21); // 建立一个TCP连接
    if (!socket.waitForConnected(10000)) // 等待连接成功，超时10000毫秒
    {
        QMessageBox::information(parent, "连接失败", "连接失败");
        qDebug() << "Failed to connect to host:" << pUrl.host();
        return false;
    }

    QTextStream stream(&socket);
    QString response;

    // 读取服务器欢迎信息
    if (socket.waitForReadyRead(10000)) // 等待服务器响应
    {
        response = socket.readAll();
        qDebug() << "Server response:" << response;
    }
    else
    {
        qDebug() << "Failed to read server response.";
        QMessageBox::information(parent, "连接失败", "读取服务器响应失败");
        return false;
    }

    // 发送用户名
    stream << "USER " << pUrl.userName() << "\r\n";
    stream.flush();
    if (socket.waitForReadyRead(10000)) // 等待服务器响应
    {
        response = socket.readAll();
        qDebug() << "USER response:" << response;
        if (!response.startsWith("331"))
        {
            QMessageBox::information(parent, "用户名无效", "用户名无效");
            socket.close();
            return false;
        }
    }
    else
    {
        qDebug() << "Failed to read USER response.";
        QMessageBox::information(parent, "连接失败", "读取用户名响应失败");
        return false;
    }

    // 发送密码
    stream << "PASS " << pUrl.password() << "\r\n";
    stream.flush();
    if (socket.waitForReadyRead(10000)) // 等待服务器响应
    {
        response = socket.readAll();
        qDebug() << "PASS response:" << response;
        if (!response.startsWith("230"))
        {
            QMessageBox::information(parent, "密码无效", "密码无效");
            socket.close();
            return false;
        }
    }
    else
    {
        qDebug() << "Failed to read PASS response.";
        QMessageBox::information(parent, "连接失败", "读取密码响应失败");
        return false;
    }

    stream << "PWD\r\n";
    stream.flush();
    if (socket.waitForReadyRead(10000)) // 等待服务器响应
    {
        response = socket.readAll();
        qDebug() << "PWD response:" << response;
        // 提取路径
        QRegularExpression re("\"([^\"]*)\"");
        QRegularExpressionMatch match = re.match(response);
        if (match.hasMatch()) {
            QString currentDir = match.captured(1);
            target->currentDir->setPath("\\\\" + pUrl.host() + currentDir);
            qDebug() << "Current directory set to:" << currentDir;
        }
    }
    else
    {
        qDebug() << "Failed to read PWD response.";
        socket.close();
        QMessageBox::information(parent, "连接失败", "读取当前目录失败");
        return false;
    }

    socket.close(); // 连接成功后关闭套接字
    showDirEntry(target); // 刷新 target 目录显示
    this->target->path->setText(this->local->currentDir->path()); // 设置 target 的路径
    return true;
}

void ftpManager::send(const QString localPath, const QString targetPath)
{
    qDebug()<<localPath<<Qt::endl<<targetPath<<Qt::endl;
    // return;


    pUrl.setPath(targetPath);
    QNetworkRequest request(pUrl);
    QFile file(localPath);
    QNetworkReply *reply = manager.put(request, &file);
    QObject::connect(reply, &QNetworkReply::uploadProgress, [](qint64 bytesSent, qint64 bytesTotal) {
        qDebug() << "Progress:" << bytesSent << "/" << bytesTotal;
    });

    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        if (reply->error() == QNetworkReply::NoError) {
               QMessageBox::information(parent,"上传成功","上传成功");
           } else {
               QMessageBox::information(parent,"上传失败","上传失败");
           }
           file.close();
           reply->deleteLater();
    });
}

void ftpManager::receive(const QString localPath, const QString targetPath)
{
    qDebug()<<localPath<<Qt::endl<<targetPath<<Qt::endl;
    // return;

    //判断路径是文件还是文件夹
    //下载前判断是否是断点续传
    //传输成功调用showDirEntry刷新显示目录

    pUrl.setPath(targetPath);
    QNetworkRequest request(pUrl);
    QNetworkReply *reply = manager.get(request);
    QObject::connect(reply, &QNetworkReply::downloadProgress, [](qint64 bytesReceived, qint64 bytesTotal) {
        qDebug() << "Progress:" << bytesReceived << "/" << bytesTotal;
    });

    QObject::connect(reply, &QNetworkReply::finished, [&]() {
        if (reply->error() == QNetworkReply::NoError) {
            QFile file(localPath);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(reply->readAll());
                file.close();
                QMessageBox::information(parent,"下载成功","下载成功");
            } else {
                QMessageBox::information(parent,"下载失败","下载失败");
            }
        } else {
            QMessageBox::information(parent,"Error",reply->errorString());
        }
    });
}

ftpManager::~ftpManager()
{
    delete local;
    delete target;
}
