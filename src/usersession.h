#ifndef USERSESSION_H
#define USERSESSION_H

#include <QObject>

class QTimer;

class TcpSocket;

class UserSession : public QObject
{
	Q_OBJECT

public:
	explicit UserSession();
	~UserSession();

signals:
	void signalSendData(QByteArray);
	void signalTimeout();

public slots:
	void slotStart();
	void slotReceiveData(QByteArray);
	void slotTimeout();

protected:
	TcpSocket *m_tcpSocket;
	QTimer *m_timer;

};

#endif

