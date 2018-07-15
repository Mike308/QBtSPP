#ifndef QBTSPPWORKER_H
#define QBTSPPWORKER_H

#include <QObject>
#include "qbtspp.h"
#include <QDebug>

class QBTSPP;

class QBtSPPWorker : public QObject
{
    Q_OBJECT
public:

    QBtSPPWorker(QBTSPP *bt);

private:
    QBTSPP *bt;

signals:
    void connectioStatusChanged(bool status);
    void dataReceived(QString rxStr);

public slots:
    void onConnecting();
    void onWriteString(QString const &str);
    void onStringReceive();


};

#endif // QBTSPPWORKER_H
