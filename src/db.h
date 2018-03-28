#ifndef DB_H
#define DB_H

#include <QtSql>

class Db
{

public:
	Db();
	~Db();

	static QSqlQuery q(QString query, QVector<QVariant> vector);
	static void printRecord(QSqlQuery query, bool printColumn = false);
	static void printQuery(QSqlQuery query, bool addBindValue = true);

	QSqlError initDb();

	bool getConnected();

private:
	bool m_connected;
	QSqlDatabase m_db;

};

#endif
