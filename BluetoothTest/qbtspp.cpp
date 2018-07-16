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

    worker = new QBtSPPWorker(portName, baud);
    workerThread = new QThread();
    worker->moveToThread(workerThread);
    connect(workerThread, SIGNAL(started()), worker, SLOT(onConnecting()));
    connect(workerThread, SIGNAL(finished()), worker, SLOT(deleteLater()));
    connect(worker, SIGNAL(connectionStatusChanged(bool)),this, SLOT(onConnectionStatusChanged(bool)), Qt::DirectConnection);
    connect(this, SIGNAL(writedString(QString)),worker, SLOT(onWriteString(QString)));
    workerThread->start();
}

void QBTSPP::closeConnection(){
    workerThread->requestInterruption();
}

void QBTSPP::writeString(QString string){
    emit writedString(string);
}

void QBTSPP::onConnectionStatusChanged(bool status){
    qDebug () << "Status: " << status;
}


