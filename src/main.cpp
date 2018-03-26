#include <QCoreApplication>

#include "db.h"
#include "log.h"

int main(int argc, char *argv[]){
	QCoreApplication app(argc, argv);

	Db *db = new Db();

	// Log *log = new Log();
	// log->newLog(Log::LOGIN, "test log", 1);

	return app.exec();
}
