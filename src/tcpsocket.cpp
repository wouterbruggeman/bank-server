#include <QThreadPool>

#include "tcpsocket.h"
#include "tcptask.h"

TcpSocket::TcpSocket(QObject *parent) :
	QObject(parent)
{
	QThreadPool::globalInstance()->setMaxThreadCount(2);
}

TcpSocket::~TcpSocket() {
	delete m_socket;
}

void TcpSocket::setSocket(qintptr descriptor) {
	m_socket = new QTcpSocket(this);

	connect(m_socket, &QTcpSocket::connected, this, &TcpSocket::connected);
	connect(m_socket, &QTcpSocket::disconnected, this, &TcpSocket::disconnected);
	connect(m_socket, &QTcpSocket::bytesWritten, this, &TcpSocket::bytesWritten);
	connect(m_socket, &QTcpSocket::readyRead, this, &TcpSocket::readyRead);

	m_socket->setSocketDescriptor(descriptor);

	printf("Client connected..\n");
}

void TcpSocket::connected() {
	printf("Connected\n");
}

void TcpSocket::disconnected() {
	printf("Disconnected\n");
}

void TcpSocket::bytesWritten(qint64 bytes) {
	printf("Bytes written: %lld\n", bytes);
}

void TcpSocket::readyRead() {
	printf("Reading...\n%s\n", m_socket->readAll().data());

	TcpTask *task = new TcpTask();
	task->setAutoDelete(true);
	connect(task, &TcpTask::signalResult, this, &TcpSocket::slotResult, Qt::QueuedConnection);
	QThreadPool::globalInstance()->start(task);
}

void TcpSocket::slotResult(int number) {
	printf("Task from task: %d\n", number);

	QByteArray buffer;
	buffer.append("Task from server: " + QString::number(number) + "\r\n");
	m_socket->write(buffer);
}
