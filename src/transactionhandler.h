#ifndef TRANSACTIONHANDLER_H
#define TRANSACTIONHANDLER_H

#include <QObject>
#include <QTimer>
#include "db.h"

class TransactionHandler : public QObject{
	Q_OBJECT

	public:
		TransactionHandler(Db *databasePtr);

	public slots:
		void handlePending();
		
	private:
		QTimer *timer;	
		Db *database;
};
#endif
