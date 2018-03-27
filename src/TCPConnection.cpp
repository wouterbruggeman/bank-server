#include "TCPConnection.h"

#include <QNetwork>

TCPConnection::TCPConnection(int socketDescriptor, QObject *parent) 
	: QThread(parent), socketDescriptor(socketDescriptor){
}

void TCPConnection::run(){
	QTcpSocket tcpSocket;
	if(!tcpSocket.setSocketDescriptor(socketDescriptor)){
		emit error(tcpSocket.error());
		return;
	}
	
	//Some test data to find out if we are able to send something
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_0);

	tcpSocket.write(block);
	tcpSocket.disconnectFromHost();
	tcpSocket.waitForDisconnect();
}
