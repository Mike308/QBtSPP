#ifndef QBTSPP_H
#define QBTSPP_H

#include <QObject>
#include <QSerialPort>
#include <QThread>
#include <QDebug>
#include <QSerialPortInfo>
#include <QStringList>

#include "qbtsppworker.h"
class QBtSPPWorker;
class QBTSPP : public QObject
{
    Q_OBJECT
public:
    QBTSPP();
    ~QBTSPP();
    void openConnection(QString portName, int baud);
    void openConnection(QString portName, int baud, QString endOfString);
    void closeConnection();
    QStringList getPortsList();


private:
    QThread *workerThread;
    QBtSPPWorker *worker;
    QBTSPP *btNew;


public slots:
    void onConnectionStatusChanged(bool status);
    void writeString(QString string);

private slots:
    void onDisconnected();

signals:
    void writedString(QString const &txStr);
    void connectionStatusChanged(bool status);
    void closedConnection();






};

#endif // QBTSPP_H
