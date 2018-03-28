#ifndef TCPTASK_H
#define TCPTASK_H

#include <QObject>
#include <QRunnable>

class TcpTask : public QObject, public QRunnable
{
	Q_OBJECT

public:
	explicit TcpTask(QObject *parent = 0);
	~TcpTask();

signals:
	void signalResult(int);

public slots:

protected:
	void run();

};

#endif

