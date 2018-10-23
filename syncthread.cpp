#include "syncthread.h"

SyncThread::SyncThread(int socketDescriptor, QObject *parent)
    : QThread(parent), socketDescriptor(socketDescriptor)
{

}

void SyncThread::run()
{
    QTcpSocket tcpSocket;
    if (!tcpSocket.setSocketDescriptor(socketDescriptor)) {
        emit error(tcpSocket.error());
        return;
    }

    tcpSocket.disconnectFromHost();
    tcpSocket.waitForDisconnected();
    qDebug() << "Tcp Socket is disconnected";
}
