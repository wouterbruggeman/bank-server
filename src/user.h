#ifndef USER_H
#define USER_H

#include <QByteArray>
#include <QString>
#include <QDate>

class User{
	public:
		explicit User(int userId);
		QString getFirstName();
		QString getLastName();
		QDate getBirthDate();
		int getUserId();
		//QVector<
	private:
		int userId;
		QString firstName;
		QString lastName;
		QDate birthDate;
};
#endif
