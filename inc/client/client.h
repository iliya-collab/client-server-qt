#ifndef _CLIENT_
#define _CLIENT_

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>


class Client : public QObject {
    Q_OBJECT

public:

    Client();
    ~Client();

    void setConnectAddress(const QString& _addrServer, quint16 _portServer = 1234) {
        addrServer = _addrServer;
        portServer = _portServer;
    }
    void connectToServer();
    void sendMessage(const QString &message);
    bool isConnected();

    void sendTestsMessages(const QString &message, int msec);

private:

    QTcpSocket* socket;
    quint16 portServer;
    QString addrServer;
    QTimer* _messageTimer;

signals:
    void connected();
    void disconnected();
    void messageReceived(const QString &message);
    void errorOccurred(const QString &error);

private slots:
    void onConnected();
    void onDisconnected();
    void onReadyRead();
    void onErrorOccurred(QAbstractSocket::SocketError error);


};

#endif