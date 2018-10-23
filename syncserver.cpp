#include "syncserver.h"
#include "syncthread.h"

SyncServer::SyncServer(QObject *parent) : QTcpServer(parent)
{

}

void SyncServer::incomingConnection(qintptr socketDescriptor) {
    thread = new SyncThread(socketDescriptor, this);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    thread->start();

    emit newConnectionIncoming();
}
