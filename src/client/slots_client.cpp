#include "client/client.h"

void Client::onConnected() {
    qDebug() << "Connected to server successfully!";
    emit connected();
}

void Client::onDisconnected() {
    qDebug() << "Disconnected from server";
    emit disconnected();
}

void Client::onReadyRead() {
    QByteArray data = socket->readAll();
    QString message = QString::fromUtf8(data);
    qDebug() << "Received message:" << message;
    emit messageReceived(message);
}

void Client::onErrorOccurred(QAbstractSocket::SocketError error) {
    QString errorString = socket->errorString();
    qDebug() << "Socket error:" << errorString;
    emit errorOccurred(errorString);
}

/*void MainWindow::pressConnectServer() {
    quint16 port = portString.toUShort();
    setupClient(addrString, port);
}

void MainWindow::getDataEditLine() {
    QString data = editLine->text();
    int pos = data.indexOf('/');
    addrString = data.mid(0, pos);
    portString = data.mid(pos+1);
}*/