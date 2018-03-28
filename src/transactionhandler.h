#ifndef TRANSACTIONHANDLER_H
#define TRANSACTIONHANDLER_H

#include "db.h"

class TransactionHandler{
	public:
		explicit TransactionHandler(Db *databasePtr);
		void handlePending();
		
	private:
		Db *database;

#endif
