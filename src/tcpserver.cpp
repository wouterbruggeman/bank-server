#include "tcpserver.h"

TCPServer::TCPServer(QObject *parent) : QTcpServer(parent){
}

void TCPServer::start(int port){
	this->listen(QHostAddress::Any, port);
}

void TCPServer::incomingConnection(qintptr socketDescriptor){

	qDebug() << "New connection!";
	/*
	TCPConnection *thread new TCPConnection(socketDescriptor, this);
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	thread->start();*/
}
