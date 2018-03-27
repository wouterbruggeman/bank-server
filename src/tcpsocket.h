#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>

class TcpSocket : public QObject
{
	Q_OBJECT

public:
	explicit TcpSocket(QObject *parent = 0);
	~TcpSocket();

public slots:
	void connected();
	void disconnected();
	void bytesWritten(qint64);
	void readyRead();

protected:
	QTcpSocket *m_socket;

};

#endif
