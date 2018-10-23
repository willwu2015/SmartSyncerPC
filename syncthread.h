#ifndef SYNCTHREAD_H
#define SYNCTHREAD_H

#include <QThread>
#include <QTcpSocket>

class SyncThread : public QThread
{
    Q_OBJECT

public:
    SyncThread(int socketDescriptor, QObject *parent);

    void run() override;

signals:
    void error(QTcpSocket::SocketError socketError);

private:
    int socketDescriptor;
};

#endif // SYNCTHREAD_H
