#ifndef SYNCSERVER_H
#define SYNCSERVER_H

#include <QTcpServer>

class SyncThread;

class SyncServer : public QTcpServer
{
    Q_OBJECT

public:
    SyncServer(QObject *parent = 0);

protected:
    void incomingConnection(qintptr socketDescriptor) override;

signals:
    void newConnectionIncoming();

private:
    SyncThread *thread;
};

#endif // SYNCSERVER_H
