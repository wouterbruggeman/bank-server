#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>

class UserSession;

class TcpSocket : public QObject
{
	Q_OBJECT

public:
	explicit TcpSocket(QObject *parent = 0);
	~TcpSocket();
	void setSocket(qintptr descriptor);

signals:
	void signalSendData(QByteArray);

public slots:
	void disconnected();
	void readyRead();

private:
	QTcpSocket *m_socket;
	UserSession *m_userSession;

	static QThread *m_thread;

};

#endif
