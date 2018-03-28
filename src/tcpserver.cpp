#include <QTcpSocket>

#include "tcpserver.h"
#include "tcpsocket.h"

TcpServer::TcpServer(QObject *parent) :
	QTcpServer(parent)
{
}

void TcpServer::start(int port){
#ifdef DEBUG
	if (this->listen(QHostAddress::Any, port)) {
		printf("Server started..\n");
	}
	else {
		printf("Server did not start..\n");
	}
#endif
}

void TcpServer::incomingConnection(qintptr descriptor) {
	TcpSocket *socket = new TcpSocket(this);
	socket->setSocket(descriptor);
}
