#include "config.h"
#include "db.h"

Config::Config(){
}

QVariant Config::getValue(QString setting){
	QSqlQuery query = Db::q("SELECT value FROM config WHERE setting = ?",{setting});
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

	QSqlQuery query = Db::q(sql, {value, setting});
	query.exec();
}
