#ifndef _MAIN_WINDOW_
#define _MAIN_WINDOW_

#include <QApplication>
#include <QMainWindow>

#include <QObject>
#include <QBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QAction>
#include <QActionGroup>

#include "server/server.h"
#include "client/client.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    QWidget* mainWindow;
    QVBoxLayout* mainLayout;

    QActionGroup *modeGroup;
    QLineEdit* editIPAddress;
    QLineEdit* editPort;
    QPushButton* btnStart;
    QPushButton* btnStop;

    QString mode;
    QString dataEditPort;
    QString dataEditIPAddress;

    Server _server;
    Client _client;
    
    void setupUI();
    void setupServer(quint16 port);
    void setupClient(const QString &address, quint16 port);
    void connectionSignals();


private slots:

    void handleModeChange(QAction *action);
    void handleEditIPAddress();
    void handleEditPort();
    void handleClickedPushButtonStart();

};



#endif