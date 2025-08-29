#include "mainwindow.h"

void MainWindow::handleModeChange(QAction *action) {
    mode = action->text();
    qDebug() << "Select mode:" << mode;
    if (mode == "Client") {
        setWindowTitle("Client");
        editIPAddress->setEnabled(true);
        btnStart->setText("Connect to server");
        btnStop->setText("Disconnect to server");
        connect(btnStop, &QPushButton::clicked, &_server, &Server::disconnectCurrentClient);
    }
    else {
        setWindowTitle("Server");
        editIPAddress->setEnabled(false);
        btnStart->setText("Start the server");
        btnStop->setText("Stop the server");
        connect(btnStop, &QPushButton::clicked, &_server, &Server::disconnectAllClients);
    }
    editPort->setEnabled(true);
    btnStop->setEnabled(true);
    btnStart->setEnabled(true);
}

void MainWindow::handleEditIPAddress() {
    dataEditIPAddress = editIPAddress->text();
    qDebug() << "EditLineIPAddress:" << dataEditIPAddress;
}

void MainWindow::handleEditPort() {
    dataEditPort = editPort->text();
    qDebug() << "EditLinePort:" << dataEditPort;
}

void MainWindow::handleClickedPushButtonStart() {
    quint16 port;
    if (dataEditPort == "")
        port = 1234; 
    else 
        port = dataEditPort.toUShort();
    if (mode == "Client")
        setupClient(dataEditIPAddress, port);
    else
        setupServer(port);
}