#include "qbtspp.h"
QBTSPP::QBTSPP()
{
    this->btNew = this;

}

QBTSPP::~QBTSPP(){
    workerThread->quit();
    workerThread->wait();
    qDebug () << "Destroying object...";
}

void QBTSPP::openConnection(QString portName, int baud){
    worker = new QBtSPPWorker();
    workerThread = new QThread();
    worker->setPortName(portName);
    worker->setBaud(baud);
    worker->moveToThread(workerThread);
    connect(workerThread, SIGNAL(started()), worker, SLOT(onConnecting()));
    connect(workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(worker, SIGNAL(connectionStatusChanged(bool)),this, SLOT(onConnectionStatusChanged(bool)), Qt::DirectConnection);
    connect(worker, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(this, SIGNAL(writedString(QString)),worker, SLOT(onWriteString(QString)));
    connect(this, SIGNAL(closedConnection()), worker, SLOT(onCloseConnection()));
    workerThread->start();
}

void QBTSPP::openConnection(QString portName, int baud, QString endOfString){
    worker = new QBtSPPWorker();
    workerThread = new QThread();
    worker->setPortName(portName);
    worker->setBaud(baud);
    worker->setEndOfString(endOfString);
    worker->moveToThread(workerThread);
    connect(workerThread, SIGNAL(started()), worker, SLOT(onConnecting()));
    connect(workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(worker, SIGNAL(connectionStatusChanged(bool)),this, SLOT(onConnectionStatusChanged(bool)), Qt::DirectConnection);
    connect(worker, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(this, SIGNAL(writedString(QString)),worker, SLOT(onWriteString(QString)));
    connect(this, SIGNAL(closedConnection()), worker, SLOT(onCloseConnection()));
    workerThread->start();
}

void QBTSPP::closeConnection(){
    emit closedConnection();
    workerThread->requestInterruption();
}

void QBTSPP::writeString(QString string){
    emit writedString(string);
}

void QBTSPP::onConnectionStatusChanged(bool status){
    qDebug () << "Status: " << status;
    emit connectionStatusChanged(status);
}

QStringList QBTSPP::getPortsList(){
    QSerialPortInfo serialPortInfo;
    QList<QSerialPortInfo> portsList = serialPortInfo.availablePorts();
    QStringList portsNamesList;
    foreach (QSerialPortInfo info, portsList) {
        portsNamesList.append(info.portName());
    }
    return portsNamesList;
}

void QBTSPP::onDisconnected(){
    qDebug () << "Disconnected received";
    delete worker;
}




