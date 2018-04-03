#include <QThread>
#include <QTimer>

#include "tcpsocket.h"
#include "usersession.h"

UserSession::UserSession()
{
}

UserSession::~UserSession() {
	delete m_timer;
}

void UserSession::slotStart() {
	m_timer = new QTimer(this);
	m_timer->setInterval(1000);
	connect(m_timer, &QTimer::timeout, this, &UserSession::slotTimeout);
	m_timer->start();
}

void UserSession::slotReceiveData(QByteArray data) {
	// Restart timer
	m_timer->start();

#ifdef DEBUG
	printf("Received from client: %s\n", data.trimmed().data());
#endif

	// Example of writing data
	emit signalSendData(data);
}

void UserSession::slotTimeout() {
	m_timer->stop();
	emit signalTimeout();
}
