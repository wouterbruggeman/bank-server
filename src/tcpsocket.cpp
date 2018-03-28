#include "tcpsocket.h"

TcpSocket::TcpSocket(QObject *parent) :
	QObject(parent)
{
	m_socket = new QTcpSocket(this);

	connect(m_socket, &QTcpSocket::connected, this, &TcpSocket::connected);
	connect(m_socket, &QTcpSocket::disconnected, this, &TcpSocket::disconnected);
	connect(m_socket, &QTcpSocket::bytesWritten, this, &TcpSocket::bytesWritten);
	connect(m_socket, &QTcpSocket::readyRead, this, &TcpSocket::readyRead);

	printf("Connecting..\n");

	m_socket->connectToHost("riyyi.com", 80);

	if (!m_socket->waitForConnected(1000)) {
		printf("Error: %s\n", m_socket->errorString().toUtf8().data());
	}
}

TcpSocket::~TcpSocket() {
	delete m_socket;
}

void TcpSocket::connected() {
	printf("Connected\n");

	m_socket->write("HEAD / HTTP/1.0\r\n\r\n");
}

void TcpSocket::disconnected() {
	printf("Disconnected\n");
}

void TcpSocket::bytesWritten(qint64 bytes) {
	printf("Bytes written: %lld\n", bytes);
}

void TcpSocket::readyRead() {
	printf("Reading...\n%s\n", m_socket->readAll().data());
}

