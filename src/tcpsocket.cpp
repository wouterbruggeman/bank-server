#include <QThread>

#include "tcpsocket.h"
#include "usersession.h"

QThread *TcpSocket::m_thread = new QThread;

TcpSocket::TcpSocket(QObject *parent) :
	QObject(parent)
{
	m_thread->start();
}

TcpSocket::~TcpSocket() {
	delete m_socket;
	delete m_userSession;
}

void TcpSocket::setSocket(qintptr descriptor) {
	m_socket = new QTcpSocket(this);

	connect(m_socket, &QTcpSocket::disconnected, this, &TcpSocket::disconnected);
	connect(m_socket, &QTcpSocket::readyRead, this, &TcpSocket::readyRead);

	m_socket->setSocketDescriptor(descriptor);

	m_userSession = new UserSession();
	connect(this, &TcpSocket::signalSendData, m_userSession, &UserSession::slotReceiveData);
	m_userSession->moveToThread(m_thread);

	printf("Client connected..\n");
}

void TcpSocket::disconnected() {
	printf("Client disconnected..\n");
}

void TcpSocket::readyRead() {
	emit signalSendData(m_socket->readAll());
}
