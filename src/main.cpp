#include <QCoreApplication>
#include <QDebug>
#include <QThread>

#include "tcpserver.h"
#include "tcpsocket.h"

int main(int argc, char *argv[]){
	QCoreApplication app(argc, argv);

#ifdef DEBUG
	printf("Main thread: %p\n", QThread::currentThreadId());
#endif

	TcpServer *server = new TcpServer();
	server->start(1234);

	/*Db *db = new Db();

	// Log *log = new Log();
	// log->newLog(Log::LOGIN, "test log", 1);

	// Iban *iban = new Iban();
	// printf("%d\n", iban->isValid("nl43 INGB 0756 7136 09"));
	// printf("%d\n", iban->calculateCheckDigit("nl", "INgb 0756 7136 09"));*/

	return app.exec();
}
