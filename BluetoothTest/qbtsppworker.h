#ifndef QBTSPPWORKER_H
#define QBTSPPWORKER_H

#include <QObject>

class QBtSPPWorker : public QObject
{
    Q_OBJECT
public:
    explicit QBtSPPWorker(QObject *parent = nullptr);

signals:

public slots:
};

#endif // QBTSPPWORKER_H