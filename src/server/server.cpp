#include "server/server.h"

void Server::start() {
    server = new QTcpServer(this);
    addrServer = getLocalIP();
    if (!server->listen(addrServer, portServer))
        qDebug() << "Server error:" << server->errorString();
    else {
        qDebug() << "Server started" << "with the IP address:" << addrServer.toString() << "on the Port:" << portServer;
    }
}

QHostAddress Server::getLocalIP() {
    QList<QHostAddress> listIPAddress = QNetworkInterface::allAddresses();
    for (const QHostAddress& addr : listIPAddress) {
        if (addr.protocol() == QAbstractSocket::IPv4Protocol && addr != QHostAddress(QHostAddress::LocalHost))
            return addr;
    }
    return QHostAddress(QHostAddress::LocalHost);
}

void Server::connectClient() {
    connect(server, &QTcpServer::newConnection, this, &Server::newConnection);
}