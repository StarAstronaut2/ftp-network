#include "ftpmanager.h"
#include <QDebug>
ftpManager::ftpManager(QWidget *parent, QMyListWidget* local, QMyListWidget* target, QLineEdit* localPath, QLineEdit* targetPath)
        :parent(parent)
{
    controlSocket = new QTcpSocket();

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
QString ftpManager::readResponse() {
    QString response;
    // 模拟读取服务器的所有响应
    while (true) {
        QString line = controlSocket->readLine();  // 假设你有一个套接字类实例 socket
        response += line;
        if (line.contains("\r\n")) {
            break;
        }
    }
    return response;
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

    controlSocket->abort(); // 取消原有连接
    controlSocket->connectToHost(pUrl.host(), 21); // 建立一个TCP连接
    if (!controlSocket->waitForConnected(10000)) // 等待连接成功，超时10000毫秒
    {
        QMessageBox::information(parent, "连接失败", "连接失败");
        qDebug() << "Failed to connect to host:" << pUrl.host();
        return false;
    }

    QString response;

    // 读取服务器欢迎信息
    if (controlSocket->waitForReadyRead(10000)) // 等待服务器响应
    {
        response = controlSocket->readAll();
        qDebug() << "Server response:" << response;
    }
    else
    {
        qDebug() << "Failed to read server response.";
        QMessageBox::information(parent, "连接失败", "读取服务器响应失败");
        return false;
    }

    sendCommand("USER " + pUrl.userName());
    if (controlSocket->waitForReadyRead(10000)) // 等待服务器响应
    {
        response = controlSocket->readAll();
        qDebug() << "USER response:" << response;
        if (!response.startsWith("331"))
        {
            QMessageBox::information(parent, "用户名无效", "用户名无效");
            controlSocket->close();
            return false;
        }
    }
    else
    {
        qDebug() << "Failed to read USER response.";
        QMessageBox::information(parent, "连接失败", "读取用户名响应失败");
        return false;
    }

    sendCommand("PASS " + pUrl.password());
    if (controlSocket->waitForReadyRead(10000)) // 等待服务器响应
    {
        response = controlSocket->readAll();
        qDebug() << "PASS response:" << response;
        if (!response.startsWith("230"))
        {
            QMessageBox::information(parent, "密码无效", "密码无效");
            controlSocket->close();
            return false;
        }
    }
    else
    {
        qDebug() << "Failed to read PASS response.";
        QMessageBox::information(parent, "连接失败", "读取密码响应失败");
        return false;
    }

    // 发送 SYST 命令以确保服务器进入正确模式
    sendCommand("SYST");
    if (controlSocket->waitForReadyRead(10000)) // 等待服务器响应
    {
        response = controlSocket->readAll();
        qDebug() << "SYST response:" << response;
    }
    else
    {
        qDebug() << "Failed to read SYST response.";
    }

    sendCommand("PWD");
    if (controlSocket->waitForReadyRead(10000)) // 等待服务器响应
    {
        QString pwdResponse = controlSocket->readAll();
        qDebug() << "PWD response:" << pwdResponse;
        QRegularExpression re("257 \"(.*)\"");

        auto match = re.match(pwdResponse);

        if (match.hasMatch()) {
            QString currentDir = match.captured(1);
            target->currentDir->setPath("\\\\" + pUrl.host() + currentDir);
            qDebug() << "Current directory set to:" << currentDir;
        } else {
            qDebug() << "Failed to parse PWD response:" << pwdResponse;
            // 如果无法解析 PWD 响应，使用根目录
            target->currentDir->setPath("\\\\" + pUrl.host() + "/");
        }
    }
    else
    {
        qDebug() << "Failed to read PWD response.";
        controlSocket->close();
        QMessageBox::information(parent, "连接失败", "读取当前目录失败");
        return false;
    }

    showDirEntry(target); // 刷新 target 目录显示
    this->target->path->setText(this->local->currentDir->path()); // 设置 target 的路径
    return true;
}
void ftpManager::sendCommand(const QString &command)
{
    controlSocket->write(command.toUtf8() + "\r\n");
    controlSocket->flush();

}
QTcpSocket* ftpManager::openDataConnection()
{
    sendCommand("PASV");
    if (!controlSocket->waitForReadyRead(5000)) {
        qDebug() << "Failed to enter passive mode";
        return nullptr;
    }

    QString response = controlSocket->readAll();
    QRegularExpression re("(\\d+,\\d+,\\d+,\\d+),(\\d+),(\\d+)");
    auto match = re.match(response);
    if (!match.hasMatch()) {
        qDebug() << "Failed to parse PASV response";
        return nullptr;
    }

    QStringList ip = match.captured(1).split(',');
    int port = match.captured(2).toInt() * 256 + match.captured(3).toInt();

    QString ipAddress = QString("%1.%2.%3.%4").arg(ip[0], ip[1], ip[2], ip[3]);

    QTcpSocket* dataSocket = new QTcpSocket();
    dataSocket->connectToHost(ipAddress, port);
    if (!dataSocket->waitForConnected(5000)) {
        qDebug() << "Failed to connect data socket";
        delete dataSocket;
        return nullptr;
    }

    return dataSocket;
}
void ftpManager::closeDataConnection(QTcpSocket* dataSocket)
{
    dataSocket->close();
    delete dataSocket;
}

void ftpManager::receive(const QString& localPath, const QString& remotePath)
{
    QFile localFile(localPath);
    if (!localFile.open(QIODevice::WriteOnly)) {
        qDebug() << "Failed to open local file for writing";
        return;
    }

    sendCommand("TYPE I");
    sendCommand("RETR " + remotePath);

    QTcpSocket* dataSocket = openDataConnection();
    if (!dataSocket) {
        localFile.close();
        return;
    }

    while (dataSocket->waitForReadyRead(5000)) {
        localFile.write(dataSocket->readAll());
    }

    localFile.close();
    closeDataConnection(dataSocket);

    if (!controlSocket->waitForReadyRead(5000)) {
        qDebug() << "Failed to get transfer complete response";
        return;
    }
    QString response = controlSocket->readAll();
    qDebug() << "Transfer complete:" << response;

    // Refresh the local file list
    showDirEntry(local);
}

void ftpManager::send(const QString& localPath, const QString& remotePath)
{
    QFile localFile(localPath);
    if (!localFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to open local file for reading";
        return;
    }

    sendCommand("TYPE I");
    sendCommand("STOR " + remotePath);

    QTcpSocket* dataSocket = openDataConnection();
    if (!dataSocket) {
        localFile.close();
        return;
    }

    while (!localFile.atEnd()) {
        dataSocket->write(localFile.read(8192));
    }

    localFile.close();
    closeDataConnection(dataSocket);

    if (!controlSocket->waitForReadyRead(5000)) {
        qDebug() << "Failed to get transfer complete response";
        return;
    }
    QString response = controlSocket->readAll();
    qDebug() << "Transfer complete:" << response;

    // Refresh the remote file list
    showDirEntry(target);
}
//void ftpManager::send(const QString localPath, const QString targetPath)
//{
//    qDebug()<<localPath<<endl<<targetPath<<endl;
//    // return;


//    pUrl.setPath(targetPath);
//    QNetworkRequest request(pUrl);
//    QFile file(localPath);
//    QNetworkReply *reply = manager.put(request, &file);
//    QObject::connect(reply, &QNetworkReply::uploadProgress, [](qint64 bytesSent, qint64 bytesTotal) {
//        qDebug() << "Progress:" << bytesSent << "/" << bytesTotal;
//    });

//    QObject::connect(reply, &QNetworkReply::finished, [&]() {
//        if (reply->error() == QNetworkReply::NoError) {
//               QMessageBox::information(parent,"上传成功","上传成功");
//           } else {
//               QMessageBox::information(parent,"上传失败","上传失败");
//           }
//           file.close();
//           reply->deleteLater();
//    });
//}

//void ftpManager::receive(const QString localPath, const QString targetPath)
//{
//    qDebug()<<localPath<<endl<<targetPath<<endl;
//    // return;

//    //判断路径是文件还是文件夹
//    //下载前判断是否是断点续传
//    //传输成功调用showDirEntry刷新显示目录

//    pUrl.setPath(targetPath);
//    QNetworkRequest request(pUrl);
//    QNetworkReply *reply = manager.get(request);
//    QObject::connect(reply, &QNetworkReply::downloadProgress, [](qint64 bytesReceived, qint64 bytesTotal) {
//        qDebug() << "Progress:" << bytesReceived << "/" << bytesTotal;
//    });

//    QObject::connect(reply, &QNetworkReply::finished, [&]() {
//        if (reply->error() == QNetworkReply::NoError) {
//            QFile file(localPath);
//            if (file.open(QIODevice::WriteOnly)) {
//                file.write(reply->readAll());
//                file.close();
//                QMessageBox::information(parent,"下载成功","下载成功");
//            } else {
//                QMessageBox::information(parent,"下载失败","下载失败");
//            }
//        } else {
//            QMessageBox::information(parent,"Error",reply->errorString());
//        }
//    });
//}

ftpManager::~ftpManager()
{
    delete local;
    delete target;
}
