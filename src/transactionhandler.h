#ifndef TRANSACTIONHANDLER_H
#define TRANSACTIONHANDLER_H

#include <QObject>
#include <QString>
#include <QTimer>
#include <QVector>

#define STATUS_PENDING 0
#define STATUS_DONE 1

struct server{
	QString prefix;
	QString ip;
	int portnr;
};

class TransactionHandler : public QObject{
	Q_OBJECT

	public:
		explicit TransactionHandler(QObject *parent = 0);

	public slots:
		void cycle();

	private:
		//Functions
		void receiveServerList();
		bool pingServer(QString ip);
		void handleTransactions(server s);
		void internalTransfer(QString from_iban, QString to_iban, int amount);
		void setTransactionStatus(int transaction, int status);

		//Variables
		QVector<server> serverList;
		int serverIterator = 0;
		QString ibanPrefix;
		QTimer *timer;
};
#endif
