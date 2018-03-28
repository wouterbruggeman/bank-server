#include "tcpsocket.h"

TCPSocket::TCPSocket(QObject *parent) :
	QObject(parent)
{
	printf("Connecting..\n");
	this->connectToHost("localhost", 1234);
	if (!this->waitForConnected(1000)) {
		printf("Error: %s\n", this->errorString().toUtf8().data());
	}
}

TCPSocket::~TCPSocket() {
}

void TCPSocket::connected() {
	printf("Connected\n");

	this->write("Hello there.");
}

void TCPSocket::disconnected() {
	printf("Disconnected\n");
}

void TCPSocket::bytesWritten(qint64 bytes) {
	printf("Bytes written: %lld\n", bytes);
}

void TCPSocket::readyRead() {
	printf("Reading...\n%s\n", this->readAll().data());
}

