#include "qbtsppworker.h"


QBtSPPWorker::QBtSPPWorker(){
    //    this->portName = portName;
    //    this->baud = baud;

}

void QBtSPPWorker::setPortName(const QString &value)
{
    portName = value;
}

void QBtSPPWorker::setBaud(int value)
{
    baud = value;
}

void QBtSPPWorker::setEndOfString(const QString &value)
{
    endOfString = value;
}

void QBtSPPWorker::onConnecting(){
    sp = new QSerialPort();
    connect(sp, SIGNAL(readyRead()), this, SLOT(onStringReceive()));
    connect(sp, SIGNAL(error(QSerialPort::SerialPortError)), SLOT(onError(QSerialPort::SerialPortError)));
    sp->setPortName(portName);
    sp->setBaudRate(baud);
    sp->setFlowControl(QSerialPort::NoFlowControl);
    sp->setDataBits(QSerialPort::Data8);
    sp->setStopBits(QSerialPort::OneStop);
    emit connectionStatusChanged(false);
    sp->open(QIODevice::ReadWrite);
    if (sp->isOpen()){
        emit connectionStatusChanged(true);
    }else{
        emit connectionErrorNotified();
    }

}

void QBtSPPWorker::onWriteString(QString str){
    if (this->endOfString.isEmpty() || this->endOfString == NULL){
        const QByteArray &arrayToSend = str.toLocal8Bit();
        qDebug () << "Send one: " << str;
        sp->write(arrayToSend);
    }else{
        QString stringToSend = str.append(endOfString);
        const QByteArray &arrayToSend = stringToSend.toLocal8Bit();
        qDebug () << "Send second: " << stringToSend;
        sp->write(arrayToSend);
    }
}

void QBtSPPWorker::onStringReceive(){
    if (sp->canReadLine()){
        emit dataReceived(QString::fromLatin1(sp->readAll()));
    }
}

void QBtSPPWorker::onCloseConnection(){
    sp->close();
    qDebug () << "Disconnected...";
    emit disconnected();
}

void QBtSPPWorker::onError(QSerialPort::SerialPortError errorVal){
    qDebug () << "Error: " << errorVal;
}








