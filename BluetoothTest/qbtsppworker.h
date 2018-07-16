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

private:
    QString portName;
    int baud;
    QSerialPort *sp;


signals:
    void connectionStatusChanged(bool status);
    void dataReceived(QString rxStr);

public slots:
    void onConnecting();
    void onWriteString(QString const &str);
    void onStringReceive();


};

#endif // QBTSPPWORKER_H
