#include <QCoreApplication>

#include "db.h"
#include "iban.h"
#include "log.h"

int main(int argc, char *argv[]){
	QCoreApplication app(argc, argv);

	Db *db = new Db();

	// Log *log = new Log();
	// log->newLog(Log::LOGIN, "test log", 1);

	// Iban *iban = new Iban();
	// printf("%d\n", iban->isValid("nl43 INGB 0756 7136 09"));
	// printf("%d\n", iban->calculateCheckDigit("nl", "INgb 0756 7136 09"));

	return app.exec();
}
