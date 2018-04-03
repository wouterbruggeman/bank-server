#include <QThread>
#include <QTimer>

#include "config.h"
#include "packethandler.h"
#include "tcpsocket.h"

PacketHandler::PacketHandler()
{
}

PacketHandler::~PacketHandler() {
	delete m_timer;
}

void PacketHandler::slotStart() {
	m_timer = new QTimer(this);
	m_timer->setInterval(Config::getValue("session_timeout").toInt());
	connect(m_timer, &QTimer::timeout, this, &PacketHandler::slotTimeout);
	m_timer->start();
}

void PacketHandler::slotReceiveData(QByteArray data) {
	// Restart timer
	m_timer->start();

#ifdef DEBUG
	printf("Received from client: %s\n", data.trimmed().data());
#endif

	// Example of writing data
	emit signalSendData(data);
}

void PacketHandler::slotTimeout() {
	m_timer->stop();
	emit signalTimeout();
}
