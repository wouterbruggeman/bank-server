#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QVariant>

#include "db.h"

class Config{
	public:
		explicit Config(Db *databasePtr);
		QVariant getValue(QString setting);
		void setValue(QString setting, QVariant value);
	private:
		Db *database;
};

#endif
