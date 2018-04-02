#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QVariant>

class Config{
	public:
		Config();
		QVariant getValue(QString setting);
		void setValue(QString setting, QVariant value);
	private:
};

#endif
