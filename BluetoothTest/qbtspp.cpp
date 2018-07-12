#include "qbtspp.h"

QBTSPP::QBTSPP()
{

}

void QBTSPP::openConnection(QString portName, int baud){

}

void QBTSPP::writeStr(QString string){
    const QByteArray &arrayToSend = string.toLocal8Bit();
    this->write(arrayToSend);
}
