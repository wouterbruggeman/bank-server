#include "transaction.h"

#include <QSqlQuery>
#include "iban.h"

Transaction::Transaction(Db *databasePtr){
	database = databasePtr;
}

bool Transaction::setToIban(QString iban){
	Iban *validator = new Iban();
	
	validator->format(iban);
	if(validator->isValid(iban)){
		this->toIban = iban;
		return true;
	}
	return false;
}

bool Transaction::setFromIban(QString iban){
	Iban *validator = new Iban();
	validator->format(iban);

	if(validator->isValid(iban)){
		this->fromIban = iban;
		return true;
	}
	return false;
}

bool Transaction::setUserId(int id){
	QSqlQuery query = database->q("SELECT COUNT(id) FROM user WHERE id = ?",
			{this->userId});
	if(!query.isActive()){
		return false;
	}
	if(!query.first()){
		return false;
	}
	if(query.value(0) == 0){
		return false;
	}
	this->userId = id;
	return true;
}

bool Transaction::setAmount(int amount){
	if(this->amount <= 0){
		return false;
	}
	this->amount = amount;
	return true;
}

bool Transaction::accountHasEnoughBalance(){
	QSqlQuery query = database->q("SELECT balance FROM account WHERE iban = ?",
			{this->fromIban});
	if(!query.isActive()){
		return false;
	}
	if(!query.first()){
		return false;
	}
	//If there is not enough money for the transaction.	
	if(query.value(0) < amount){
		return false;
	}
	return true;
}

bool Transaction::accountsEqual(){
	if(this->fromIban == this->toIban){
		return true;
	}
	return false;
}

bool Transaction::validate(){
	if(this->accountsEqual()){
		return false;		
	}

	if(!this->accountHasEnoughBalance()){
		return false;
	}

	return true;
}

bool Transaction::addPending(){
	//It is not possible to submit the same transaction twice.
	if(this->submitted){
		return false;
	}

	//Validate the transaction.
	if(!validate()){
		return false;
	}


	
	QString sql = "INSERT INTO transaction (from_iban, to_iban, amount, \
		status, date_time, user_id) VALUES (?,?,?,0,NOW(),?)";

	QSqlQuery query = database->q(sql, {this->fromIban, this->toIban, this->amount,
			this->userId});
	query.exec();

	//Return true and save the state.
	this->submitted = true;
	return true;
}
