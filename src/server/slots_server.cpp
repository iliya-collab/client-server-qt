#include "server/server.h"

void Server::newConnection() {
    QTcpSocket* client_socket = server->nextPendingConnection();
    if (client_socket) {
        qDebug() << "New client connection:" << client_socket->peerAddress().toString();
        connect(client_socket, &QTcpSocket::readyRead, this, &Server::readData);
        connect(client_socket, &QTcpSocket::disconnected, this, &Server::deleteLater);
        clients.push_back(client_socket);
    }
}

void Server::readData() {
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (socket) {
        QByteArray data = socket->readAll();
        qDebug() << "Received:" << data;
        socket->write("Echo: " + data);
    }
}

void Server::deleteLater() {
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (socket) {
        qDebug() << "Client disconnected:" << socket->peerAddress().toString();
        clients.removeAll(socket);
        socket->deleteLater();
    }
}

/*void MainWindow::getDataEditPort() {
    port = editPort->text().toUShort();
}

void MainWindow::pressStartButton() {
    setupServer(port);
}*/