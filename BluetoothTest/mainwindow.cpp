#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->bt = new QBTSPP();
    ui->portsList->addItems(bt->getPortsList());
    statusLabel = new QLabel("");
    connectionProgress = new QProgressBar();
    connectionProgress->setValue(0);
    ui->statusBar->addWidget(statusLabel);
    ui->statusBar->addWidget(connectionProgress);
    connect(bt, SIGNAL(connectionStatusChanged(bool)), this, SLOT(onConnectionStatusChanged(bool)));
    connect(bt, SIGNAL(connectionErrorNotified()), this, SLOT(onConnectioErrorNotified()));
    ui->animationsList->addItem("HSV Rotation");
    ui->animationsList->addItem("HSV Spectrum");
    ui->animationsList->addItem("Value rotation");
    ui->verticalWidget_2->setHidden(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete bt;
}

void MainWindow::on_connectBtn_clicked()
{
    if (!connectionStatus){
        bt->openConnection(ui->portsList->currentText(), 9600, "\r\n");
        ui->connectBtn->setText("Disconnect");
    }else{
        ui->connectBtn->setText("Connect");
        this->statusLabel->setText("Disconnected");
        bt->closeConnection();
        connectionStatus = false;

    }
}

void MainWindow::on_pushButton_clicked()
{
    int index = ui->animationsList->currentIndex();
    if (index == 0){
        ui->verticalWidget_2->setHidden(true);
        bt->writeString("AT+HSVROT="+ui->speedOne->text()+","+ui->speedTwo->text());
    }else if (index == 1){
        ui->verticalWidget_2->setHidden(true);
        bt->writeString("AT+HSVSPEC="+ui->speedOne->text()+","+ui->speedTwo->text());
    }else if (index == 2){
        ui->verticalWidget_2->setHidden(false);
        bt->writeString("AT+VALROT="+ui->speedOne->text()+","+ui->speedTwo->text());
    }
}

void MainWindow::onConnectionStatusChanged(bool status){
    connectionStatus = status;
    statusLabel->setStyleSheet("QLabel { color : blue;"
                               "         font-weight: bold}");
    if (status){
        statusLabel->setText("Connected");
    }else{
        statusLabel->setText("Connecting...");
    }
}

void MainWindow::onConnectioErrorNotified(){
    statusLabel->setStyleSheet("QLabel { color : red;"
                               "         font-weight: bold}");
    statusLabel->setText("Connection error...");
}

void MainWindow::on_animationsList_currentIndexChanged(int index)
{
    if (index == 0){
        ui->verticalWidget_2->setHidden(true);
    }else if (index == 1){
        ui->verticalWidget_2->setHidden(true);
    }else if (index == 2){
        ui->verticalWidget_2->setHidden(false);
    }
}


