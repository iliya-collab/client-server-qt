#include "server/server.h"

void Server::newConnection() {
    
    QTcpSocket* client_socket = server->nextPendingConnection();

    if (client_socket) {

        QString clientId = QUuid::createUuid().toString(QUuid::WithoutBraces);
        ClientInfo info;
        info.id = clientId;
        info.address = client_socket->peerAddress();
        info.port = client_socket->peerPort();
        info.connectedTime = QDateTime::currentDateTime();
        info.name = QString("Client_%1").arg(clients.size() + 1);
        
        clients.insert(client_socket, info);
        
        connect(client_socket, &QTcpSocket::readyRead, this, &Server::readData);
        connect(client_socket, &QTcpSocket::disconnected, this, &Server::deleteLater);

        qDebug() << "Client connected:" << info.name << info.address.toString() << info.id;

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
    ClientInfo info = (*clients.find(socket));
    if (socket) {
        qDebug() << "Client disconnected:" << info.name << info.address.toString() << info.id;
        clients.remove(socket);
        socket->deleteLater();
    }
}

void Server::disconnectCurrentClient() {
    if (!clients.isEmpty()) {
        auto it = clients.begin();
        QTcpSocket *client = it.key();
        ClientInfo info = it.value();

        clients.erase(it);
        
        client->disconnectFromHost();
        client->deleteLater();
        
        qDebug() << "Client disconnected:" << info.name;
    }
}

void Server::disconnectAllClients() {
    for (auto [client, info] : clients.asKeyValueRange()) {
        qDebug() << "Client:" << info.name << "Socket:" << client;
        client->disconnectFromHost();
        client->deleteLater();
    }
    clients.clear();
    qDebug() << "All clients are disconnected";
}


/*void MainWindow::getDataEditPort() {
    port = editPort->text().toUShort();
}

void MainWindow::pressStartButton() {
    setupServer(port);
}*/