#include "card.h"
#include "db.h"

//#include <QVariant>

Card::Card(){

}

void Card::setPincode(QByteArray pincode){
	this->pincode = pincode;
}

void Card::setUid(QByteArray uid){
	this->uid = uid;
}

bool Card::authenticate(){
	if(this->uid.isEmpty() || this->pincode.isEmpty()){
		return false;
	}
	QSqlQuery query = Db::q("SELECT * FROM card WHERE uid = ? AND password = ?",
			{this->uid, this->pincode});
	query.exec();
	if(!query.isActive()){
		return false;
	}
	if(!query.first()){
		incrementFailedLoginAttempts();
		return false;
	}
	//Receive the data and fill the variables
	this->failedLoginAttempts = query.value(2).toInt();
	this->userId = query.value(3).toInt();

	//Check if the card isn't blocked.
	if(failedLoginAttempts == MAX_FAILED_ATTEMPTS){
		return false;
	}

	//User has access.
	this->accessGranted = true;
	//Remove all failed attempts
	clearFailedLoginAttempts();

	return true;
}

bool Card::hasAccess(){
	return this->accessGranted;
}

/*User Card::getOwner(){

}*/

void Card::setFailedLoginAttempts(char amount){
	QSqlQuery query = Db::q("UPDATE card SET failed_login_attempts = ? WHERE uid = ?",
			{amount, this->uid});
	query.exec();
}

void Card::clearFailedLoginAttempts(){
	this->failedLoginAttempts = 0;
	setFailedLoginAttempts(0);
}

void Card::incrementFailedLoginAttempts(){
	if(this->failedLoginAttempts != MAX_FAILED_ATTEMPTS){
		//Update local
		this->failedLoginAttempts++;

		//Update the database
		setFailedLoginAttempts(this->failedLoginAttempts);
	}
}
