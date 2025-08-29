#include "mainwindow.h"

void MainWindow::handleModeChange(QAction *action) {
    mode = action->text();
    qDebug() << "Select mode:" << mode;
    if (mode == "Client") {
        setWindowTitle("Client");
        editIPAddress->setEnabled(true);
        btnStart->setText("Connect to server");

        QLayoutItem* item = mainLayout->itemAt(2);
        if (item && item->layout()) {
            QLayout* raw3 =  item->layout();
            QPushButton *button = new QPushButton("New Button");
            raw3->addWidget(button);
        }
    }
    else {
        setWindowTitle("Server");
        editIPAddress->setEnabled(false);
        btnStart->setText("Start the server");
    }
    editPort->setEnabled(true);
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
    qDebug() << "Start program";
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