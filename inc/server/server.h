#ifndef _SERVER_
#define _SERVER_

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QList>

class Server : public QObject {
    Q_OBJECT

public:
    
    void start();
    void connectClient();

    void setPortServer(quint16 port) {
        portServer = port;
    }

private:

    QTcpServer* server = nullptr;
    QList<QTcpSocket*> clients;

    quint16 portServer = 1234;
    QHostAddress addrServer;

    QHostAddress getLocalIP();


private slots:

    void newConnection();
    void readData();
    void deleteLater();

};

#endif