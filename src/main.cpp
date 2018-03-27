#include <QCoreApplication>
#include <QDebug>
#include <QNetworkInterface>
#include <QTcpServer>

#include "tcpsocket.h"

int main(int argc, char *argv[]){
	QCoreApplication app(argc, argv);

	QTcpServer *server = new QTcpServer();
	if(!server->listen()){
		qDebug() << "Cannot start server.";
	}
	else {
		qDebug() << "Started QTcpServer..";
	}

	QString ip;
	QList<QHostAddress> ipList = QNetworkInterface::allAddresses();

	TcpSocket *socket = new TcpSocket();

	return app.exec();
}
