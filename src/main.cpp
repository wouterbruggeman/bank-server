#include <QCoreApplication>
#include <QDebug>
#include "tcpserver.h"
#include "tcpsocket.h"
#include "transactionhandler.h"
#include "config.h"

int main(int argc, char *argv[]){
	QCoreApplication app(argc, argv);

	TCPServer *server = new TCPServer();
	server->start(1234);
	if(!server->isListening()){
		qDebug() << "Server not started..";
	}else{
		qDebug() << "Server started.";
	}

	TcpSocket *socket = new TcpSocket();
	
	Db *db = new Db();
	TransactionHandler t(db);

	//Config c(db);
	//c.setValue("settingname", 25);
	//qDebug() << "Value: " << c.getValue("settingname");

	// Log *log = new Log();
	// log->newLog(Log::LOGIN, "test log", 1);

	// Iban *iban = new Iban();
	// printf("%d\n", iban->isValid("nl43 INGB 0756 7136 09"));
	// printf("%d\n", iban->calculateCheckDigit("nl", "INgb 0756 7136 09"));

	return app.exec();
}
