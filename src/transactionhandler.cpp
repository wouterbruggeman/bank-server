#include "transactionHandler.h"

TransactionHandler::TransactionHandler(Db *databasePtr){
	database = databasePtr;
}

void TransactionHandler::handlePending(){
	handleExternal
}
