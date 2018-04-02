#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <QString>

class Transaction{
	public:
		Transaction();
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
};

#endif
