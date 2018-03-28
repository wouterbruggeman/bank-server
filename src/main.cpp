#include <QCoreApplication>
#include <QDebug>

#include "tcpserver.h"
#include "tcpsocket.h"

int main(int argc, char *argv[]){
	QCoreApplication app(argc, argv);

	TcpServer *server = new TcpServer();
	server->start(1234);

	// TcpSocket *socket = new TcpSocket();


	/*Db *db = new Db();

	// Log *log = new Log();
	// log->newLog(Log::LOGIN, "test log", 1);

	// Iban *iban = new Iban();
	// printf("%d\n", iban->isValid("nl43 INGB 0756 7136 09"));
	// printf("%d\n", iban->calculateCheckDigit("nl", "INgb 0756 7136 09"));*/

	return app.exec();
}
