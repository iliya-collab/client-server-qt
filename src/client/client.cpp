#include "client/client.h"

Client::Client() {
    socket = new QTcpSocket(this);
    connect(socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::errorOccurred, this, &Client::onErrorOccurred);
}

Client::~Client() {

}

void Client::sendTestsMessages(const QString &message, int msec) {
    _messageTimer = new QTimer(this);
    connect(_messageTimer, &QTimer::timeout, [this, message]() {
        if (isConnected())
            sendMessage(message);
    });
    _messageTimer->start(msec);
}

void Client::connectToServer() {
    qDebug() << "Connecting to server:" << addrServer << "port:" << portServer;
    socket->connectToHost(addrServer, portServer);
}

void Client::sendMessage(const QString &message) {
    if (isConnected()) {
        QByteArray data = message.toUtf8();
        socket->write(data);
        socket->flush();
        qDebug() << "Message sent:" << message;
    } else
        qDebug() << "Not connected to server!";
}

bool Client::isConnected() {
    if (socket->state() == QAbstractSocket::ConnectedState)
        return true;
    return false;
}