#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>


class TCPServer : public QTcpServer{
	Q_OBJECT

	public:
		TCPServer(QObject *parent = 0);
		void start(int port);

	protected:
		void incomingConnection(qintptr socketDescriptor) override;
};

#endif
