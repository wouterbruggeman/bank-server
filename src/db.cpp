#include "db.h"

Db::Db() :
	m_connected(false)
{
	QSqlError err = initDb();
	if (err.type() == QSqlError::NoError) {
		m_connected = true;
#ifdef DEBUG
		printf("Db, connected to the database..\n");
#endif
	}
#ifdef DEBUG
	else {
		printf("Db, could not load database!\n");
		printf("%s\n", err.text().toUtf8().data());
		printf("%d\n", err.type());
	}
#endif
}

Db::~Db() {
#ifdef DEBUG
	printf("Db, closing database..\n");
#endif
	m_db.close();
}

QSqlQuery Db::q(QString queryStr, QVector<QVariant> vector) {
	QSqlQuery query;

	if (queryStr.count('?') == vector.size()) {
		query.prepare(queryStr);
		for (int i = 0; i < vector.size(); i++) {
			query.addBindValue(vector.value(i));
		}
	}
	else {
#ifdef DEBUG
		printf("Db, create query: parameter size does not match\n");
#endif
	}

	return query;
}

void Db::printRecord(QSqlQuery query, bool printColumn) {
#ifdef DEBUG
	if (query.isValid()) {
		int count = query.record().count();
		if (printColumn) {
			printf("Db, | ");
			for (int i = 0; i < count; i++) {
				printf("%s | ", query.record().fieldName(i).toUtf8().data());
			}
			printf("\n");
		}

		printf("Db, | ");
		for (int i = 0; i < count; i++) {
			printf("%s | ", query.value(i).toByteArray().data());
		}
		printf("\n");
	}
#endif
}

void Db::printQuery(QSqlQuery query, bool addBindValue) {
#ifdef DEBUG
    QString str = query.lastQuery();
    QMapIterator<QString, QVariant> it(query.boundValues());

    while (it.hasNext()) {
        it.next();

        if (addBindValue) {
            str.replace(str.indexOf("?"), 1, it.value().toString());
        }
        else {
            str.replace(it.key(), it.value().toString());
        }
    }

    printf("Db, query: %s\n", str.toUtf8().data());
#endif
}

QSqlError Db::initDb() {

	if (!QSqlDatabase::drivers().contains("QMYSQL")) {
#ifdef DEBUG
		printf("Db, could not load driver!\n");
#endif
		return QSqlError();
	}

	m_db = QSqlDatabase::addDatabase("QMYSQL");
	m_db.setHostName("localhost");
	m_db.setPort(3306);
	m_db.setDatabaseName("bank_server");
	m_db.setUserName("root");
	m_db.setPassword("");

    if (!m_db.open()) {
        return m_db.lastError();
	}

	return QSqlError();
}

bool Db::getConnected() {
	return m_connected;
}
