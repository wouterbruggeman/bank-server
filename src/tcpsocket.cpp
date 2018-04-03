#include <QThread>

#include "packethandler.h"
#include "tcpsocket.h"

QThread *TcpSocket::m_thread = new QThread;

TcpSocket::TcpSocket(QObject *parent) :
	QObject(parent)
{
	m_thread->start();
}

TcpSocket::~TcpSocket() {
	m_socket->close();
	delete m_socket;
	delete m_packetHandler;
}

void TcpSocket::setSocket(qintptr descriptor) {
	m_socket = new QTcpSocket(this);

	connect(m_socket, &QTcpSocket::disconnected, this, &TcpSocket::disconnected);
	connect(m_socket, &QTcpSocket::readyRead, this, &TcpSocket::readyRead);

	m_socket->setSocketDescriptor(descriptor);

	m_packetHandler = new PacketHandler;
	connect(this, &TcpSocket::signalStart, m_packetHandler, &PacketHandler::slotStart);
	connect(this, &TcpSocket::signalSendData, m_packetHandler, &PacketHandler::slotReceiveData);
	connect(m_packetHandler, &PacketHandler::signalSendData, this, &TcpSocket::slotReceiveData);
	connect(m_packetHandler, &PacketHandler::signalTimeout, this, &TcpSocket::slotTimeout);
	m_packetHandler->moveToThread(m_thread);
	emit signalStart();

#ifdef DEBUG
	printf("Client connected..\n");
#endif
}

void TcpSocket::disconnected() {
#ifdef DEBUG
	printf("Client disconnected..\n");
#endif
}

void TcpSocket::readyRead() {
	emit signalSendData(m_socket->readAll());
}

void TcpSocket::slotReceiveData(QByteArray data) {
	m_socket->write("Received from server: " + data);
}

void TcpSocket::slotTimeout() {
#ifdef DEBUG
	printf("Client timed out..\n");
#endif
	delete this;
}
