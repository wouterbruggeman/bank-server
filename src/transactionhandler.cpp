#include <QDebug>

#include "config.h"
#include "db.h"
#include "transactionhandler.h"

TransactionHandler::TransactionHandler(QObject *parent) :
	QObject(parent)
{
	//Create a timer
	timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, &TransactionHandler::cycle);

	//Set the timer
	Config c;
	int timerDelay = c.getValue("transaction_delay").toInt();
	timer->start(timerDelay);

	//Set own iban prefix
	ibanPrefix = c.getValue("iban_prefix").toString();

	receiveServerList();
}

void TransactionHandler::cycle(){
	//handle transactions for the selected server.
	handleTransactions(serverList.at(serverIterator));

	serverIterator++;
	if(serverIterator == serverList.size()){
		serverIterator = 0;

		//Reload the server list.
		receiveServerList();

		//Handle transactions for our own server.
		server s;
		s.prefix = ibanPrefix;
		handleTransactions(s);
	}
}

void TransactionHandler::receiveServerList(){
	//Clear the server list
	serverList.clear();

	//Receive the server list
	QString sql = "SELECT * from iban_ip_link";
	QSqlQuery query = Db::q(sql, {});
	query.exec();
	if(!query.isActive()){
		return;
	}

	//Loop through all received data
	while(query.next()){
		server s;
		s.prefix = query.value(0).toString();
		s.ip = query.value(1).toString();
		s.portnr = query.value(2).toInt();

		//Add server struct to the QVector
		serverList.append(s);
	}
}

bool TransactionHandler::pingServer(QString ip){
	if(ip == ""){
		return false;
	}

	//Method below works, but spams the console.
	/*QStringList parameters;
	#if defined(WIN32)
		parameters << "-n" << "1";
	#else
		parameters << "-c 1";
	#endif
	parameters << ip;
	int exitCode = QProcess::execute("ping", parameters);
	return !exitCode;*/

	//TODO: Implement a better way.
	return true;
}

void TransactionHandler::handleTransactions(server s){
	bool isOwnServer = (s.prefix == ibanPrefix);
	bool serverIsOnline = pingServer(s.ip);

	//If the server is not our own and is offline, return;
	if(!serverIsOnline && !isOwnServer){
		return;
	}

	//cycle through all transactions where the status is not accepted for the specified bank.
	QString sql = "SELECT * FROM transactions WHERE to_iban LIKE '%?%' AND status <> ?";
	QSqlQuery query = Db::q(sql, {s.prefix, STATUS_DONE});
	query.exec();
	while(query.next()){
		//Internal transaction.
		if(query.value(1) == query.value(2)){
			internalTransfer(query.value(1).toString(),
					query.value(2).toString(), query.value(3).toInt());
			setTransactionStatus(query.value(0).toInt(), STATUS_DONE);
		}else{
			//TODO: Implement external transaction system.
		}
	}
}

void TransactionHandler::internalTransfer(QString from_iban, QString to_iban, int amount){
	//If the account has enough balance
	QString sql = "SELECT balance FROM account WHERE iban = ?";
	QSqlQuery query = Db::q(sql, {from_iban});
	query.exec();
	if(!query.isActive()){
		return;
	}
	if(!query.first()){
		return;
	}

	if(query.value(0) >= amount){
		//Transfer the money
		QString sql = "UPDATE account SET balance = (balance - ?) WHERE iban = ?;\
			       UPDATE account SET balance = (balance + ?) WHERE iban = ?;";
		QSqlQuery query = Db::q(sql, {amount, from_iban, amount, to_iban});
		query.exec();
	}
	return;
}

void TransactionHandler::setTransactionStatus(int transaction, int status){
	QString sql = "UPDATE transaction SET status = ? WHERE id = ?";
	QSqlQuery query = Db::q(sql, {status, transaction});
	query.exec();
}
