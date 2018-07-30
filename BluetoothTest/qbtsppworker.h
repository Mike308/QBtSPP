#ifndef QBTSPPWORKER_H
#define QBTSPPWORKER_H

#include <QObject>
#include <QSerialPort>
#include <QDebug>

#include "qbtspp.h"



class QBtSPPWorker : public QObject
{
    Q_OBJECT
public:

     QBtSPPWorker(QString portName, int baud);
     QBtSPPWorker();
     void setPortName(const QString &value);
     void setBaud(int value);
     void setEndOfString(const QString &value);

private:
     QString portName;
     int baud;
     QSerialPort *sp;
     QString endOfString;


signals:
    void connectionStatusChanged(bool status);
    void dataReceived(QString rxStr);
    void disconnected();

public slots:
    void onConnecting();
    void onWriteString(QString str);
    void onStringReceive();
    void onCloseConnection();


};

#endif // QBTSPPWORKER_H
