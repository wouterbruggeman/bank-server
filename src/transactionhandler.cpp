#include "transactionhandler.h"
#include "config.h"
#include <QDebug>

TransactionHandler::TransactionHandler(Db *databasePtr){
	database = databasePtr;

	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(handlePending()));
	
	Config c(databasePtr);
	int timerDelay = c.getValue("transaction_delay").toInt();

	timer->start(timerDelay);
}

void TransactionHandler::handlePending(){
	qDebug() << "Timer test";
}
