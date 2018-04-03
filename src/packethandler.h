#ifndef PACKETHANDLER_H
#define PACKETHANDLER_H

#include <QObject>

class QTimer;

class TcpSocket;

class PacketHandler : public QObject
{
	Q_OBJECT

public:
	explicit PacketHandler();
	~PacketHandler();

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

