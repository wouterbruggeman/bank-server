#include <QCoreApplication>

#include "db.h"

int main(int argc, char *argv[]){
	QCoreApplication app(argc, argv);

	Db *db = new Db();

	return app.exec();
}
