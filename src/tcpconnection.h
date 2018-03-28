#ifndef TCPCONNECTION_H
#define TCPCONNECTION_H

#include <QThread>
#include <QObject>

class TCPConnection : public QThread{
	Q_OBJECT
	
	public:
		TCPConnection(int socketDescriptor, QObject *parent);
	

};

#endif
