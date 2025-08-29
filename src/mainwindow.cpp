#include "mainwindow.h"
#include <QLabel>
#include <QMenu>
#include <QMenuBar>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    connectionSignals();
}

MainWindow::~MainWindow() {
}

void MainWindow::setupUI() {
    setWindowTitle("Client-Server");
    resize(400, 100);
    setMaximumSize({400, 100});

    QWidget* mainWindow = new QWidget(this);
    setCentralWidget(mainWindow);

    QMenuBar* menuBar = this->menuBar();

    modeGroup = new QActionGroup(mainWindow);
    modeGroup->setExclusive(true);

    QAction *clientAction = new QAction("Client", mainWindow);
    clientAction->setCheckable(true);

    QAction *serverAction = new QAction("Server", mainWindow);
    serverAction->setCheckable(true);

    modeGroup->addAction(clientAction);
    modeGroup->addAction(serverAction);

    QMenu *modeMenu = menuBar->addMenu("Modes");
    modeMenu->addAction(clientAction);
    modeMenu->addAction(serverAction);

    QLabel* labelIP = new QLabel("Enter the IP address");
    editIPAddress = new QLineEdit(mainWindow);
    editIPAddress->setInputMask("000.000.000.000");
    editIPAddress->setMaxLength(15);
    editIPAddress->setEnabled(false);
    QHBoxLayout* raw1 = new QHBoxLayout;
    raw1->addWidget(labelIP);
    raw1->addWidget(editIPAddress);
    
    QLabel* labelPort = new QLabel("Enter the port");
    editPort = new QLineEdit(mainWindow);
    editPort->setMaxLength(5);
    editPort->setEnabled(false);
    QHBoxLayout* raw2 = new QHBoxLayout;
    raw2->addWidget(labelPort);
    raw2->addWidget(editPort);

    btnStart = new QPushButton("Start");
    btnStart->setEnabled(false);
    btnStop = new QPushButton("Stop");
    btnStop->setEnabled(false);
    QHBoxLayout* raw3 = new QHBoxLayout;
    raw3->addWidget(btnStart);
    raw3->addWidget(btnStop);

    mainLayout = new QVBoxLayout(mainWindow);
    mainLayout->addLayout(raw1);
    mainLayout->addLayout(raw2);
    mainLayout->addLayout(raw3);
}

void MainWindow::connectionSignals() {
    connect(modeGroup, &QActionGroup::triggered, this, &MainWindow::handleModeChange);
    connect(editIPAddress, &QLineEdit::editingFinished, this, &MainWindow::handleEditIPAddress);
    connect(editPort, &QLineEdit::editingFinished, this, &MainWindow::handleEditPort);
    connect(btnStart, &QPushButton::clicked, this, &MainWindow::handleClickedPushButtonStart);
}

void MainWindow::setupServer(quint16 port) {
    _server.setPortServer(port);
    _server.start();
    _server.connectClient();
}

void MainWindow::setupClient(const QString &address, quint16 port) {
    _client.setConnectAddress(address, port);
    _client.connectToServer();
}