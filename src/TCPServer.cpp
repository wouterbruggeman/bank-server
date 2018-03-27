#include "TCPServer.h"

TCPServer::TCPServer(QObject *parent) : QTcpServer(parent){
	
}

void TCPServer::incomingConnection(qintptr socketDescriptor){
	TCPConnection *thread new TCPConnection(socketDescriptor, this);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();
}
