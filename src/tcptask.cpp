#include "tcptask.h"

TcpTask::TcpTask(QObject *parent) :
	QObject(parent)
{
}

TcpTask::~TcpTask() {
}

void TcpTask::run() {
	emit signalResult(666);
}
