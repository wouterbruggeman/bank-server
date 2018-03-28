#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QTcpSocket>
#include <QObject>

class TCPSocket : public QTcpSocket{

	public:
		explicit TCPSocket(QObject *parent = 0);
		~TCPSocket();

	public slots:
		void connected();
		void disconnected();
		void bytesWritten(qint64);
		void readyRead();

};

#endif
