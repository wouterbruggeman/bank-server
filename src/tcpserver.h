#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QTcpServer>

class TcpServer : public QTcpServer
{
	Q_OBJECT

public:
	TcpServer(QObject *parent = 0);
	void start(int port);

protected:
	void incomingConnection(qintptr descriptor) override;

};

#endif
