#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QVariant>

class Config{
	public:
		Config();
		static QVariant getValue(QString setting);
		static void setValue(QString setting, QVariant value);
	private:
};

#endif
