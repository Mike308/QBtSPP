#ifndef QBTSPP_H
#define QBTSPP_H

#include <QObject>
#include <QSerialPort>

class QBTSPP : public QSerialPort
{
public:
    QBTSPP();
    void openConnection(QString portName, int baud);
    void writeStr(QString string);



};

#endif // QBTSPP_H
