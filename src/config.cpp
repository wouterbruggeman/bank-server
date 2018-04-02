#include "config.h"

Config::Config(Db *databasePtr){
	this->database = databasePtr;
}

QVariant Config::getValue(QString setting){
	QSqlQuery query = database->q("SELECT value FROM config WHERE setting = ?",{setting});
	query.exec();
	if(!query.isActive()){
		return "";
	}
	if(!query.first()){
		return "";
	}
	return query.value(0);
}


void Config::setValue(QString setting, QVariant value){
	QString sql = "UPDATE config SET value = ? WHERE setting = ?";

	QSqlQuery query = database->q(sql, {value, setting});
	query.exec();
}
