#include <QThread>

#include "usersession.h"

UserSession::UserSession(QObject *parent) :
	QObject(parent)
{
}

UserSession::~UserSession() {
}

void UserSession::slotReceiveData(QByteArray data) {
	printf("Received data:\n%s\n", data.data());
}
