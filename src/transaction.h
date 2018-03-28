#ifndef TRANSACTION_H
#define TRANSACTION_H 

#include "db.h"
#include <QString>

class Transaction{
	public:
		explicit Transaction(Db *databasePtr);
		bool setToIban(QString iban);
		bool setFromIban(QString iban);
		bool setUserId(int id);
		bool setAmount(int amount);

		bool accountHasEnoughBalance();
		bool accountsEqual();
		bool addPending();

	private:
		bool validate();
		int userId;
		QString toIban;
		QString fromIban;
		int amount = 0;
		bool submitted = false;

		Db *database;
};

#endif
