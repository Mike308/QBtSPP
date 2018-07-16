#ifndef QBTSPP_H
#define QBTSPP_H

#include <QObject>
#include <QSerialPort>
#include <QThread>
#include <QDebug>

#include "qbtsppworker.h"
class QBtSPPWorker;
class QBTSPP : public QObject
{
    Q_OBJECT
public:
    QBTSPP();
    ~QBTSPP();
    void openConnection(QString portName, int baud);
    void closeConnection();


private:
    QThread *workerThread;
    QBtSPPWorker *worker;
    QBTSPP *btNew;

public slots:
    void onConnectionStatusChanged(bool status);
    void writeString(QString string);

signals:
    void writedString(QString const &txStr);






};

#endif // QBTSPP_H
