#include "qbtsppworker.h"


QBtSPPWorker::QBtSPPWorker(QString portName, int baud){
    this->portName = portName;
    this->baud = baud;
}

void QBtSPPWorker::onConnecting(){
    sp = new QSerialPort();
    sp->setPortName(portName);
    sp->setBaudRate(baud);
    sp->setFlowControl(QSerialPort::NoFlowControl);
    sp->setDataBits(QSerialPort::Data8);
    sp->setStopBits(QSerialPort::OneStop);
    emit connectionStatusChanged(false);
    sp->open(QIODevice::ReadWrite);
    emit connectionStatusChanged(true);
    connect(sp, SIGNAL(readyRead()), this, SLOT(onStringReceive()));
}

void QBtSPPWorker::onWriteString(const QString &str){
    const QByteArray &arrayToSend = str.toLocal8Bit();
    sp->write(arrayToSend);
}

void QBtSPPWorker::onStringReceive(){
    if (sp->canReadLine()){
        emit dataReceived(QString::fromLatin1(sp->readAll()));
    }
}








