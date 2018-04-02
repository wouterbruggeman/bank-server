#include <QThread>

#include "usersession.h"

UserSession::UserSession(QObject *parent) :
	QObject(parent)
{
}

UserSession::~UserSession() {
}

void UserSession::slotReceiveData(QByteArray data) {
	printf("Received from client: %s\n", data.trimmed().data());

	emit signalSendData(data);
}
