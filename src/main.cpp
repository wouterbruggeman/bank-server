#include <QCoreApplication>
#include <QDebug>


int main(int argc, char *argv[]){
	QCoreApplication app(argc, argv);
	
	QTcpServer *server = new QTcpServer();
	if(!server->listen()){
		qDebug() << "Cannot start server.";
	}

	QString ip;
	QList<QHostAddress> ipList = QNetworkInterface::allAddresses();
	1

	return app.exec();
}
