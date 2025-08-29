#ifndef _SERVER_
#define _SERVER_

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QNetworkInterface>
#include <QDateTime>
#include <QUuid>
#include <QMap>

typedef struct {
    QString id;
    QString name;
    QHostAddress address;
    quint16 port;
    QDateTime connectedTime;
} ClientInfo;

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
    QMap<QTcpSocket*, ClientInfo> clients;

    quint16 portServer = 1234;
    QHostAddress addrServer;

    QHostAddress getLocalIP();

public slots:
    void disconnectCurrentClient();
    void disconnectAllClients();

private slots:

    void newConnection();
    void readData();
    void deleteLater();

};

#endif