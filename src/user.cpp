#include "user.h"
#include "db.h"

//#include <QVariant>

User::User(int userId){
	//Get user information from the database.
	QSqlQuery query = Db::q("SELECT * FROM user WHERE id = ?", {userId});
	query.exec();

	if(!query.isActive()){
		return;
	}

	if(!query.first()){
		return;
	}

	this->firstName = query.value(1).toString();
	this->lastName = query.value(2).toString();
	this->birthDate = query.value(3).toDate();
	this->userId = userId;
}

QString User::getFirstName(){
	return this->firstName;
}

QString User::getLastName(){
	return this->lastName;
}

QDate User::getBirthDate(){
	return this->birthDate;
}

int User::getUserId(){
	return this->userId;
}
