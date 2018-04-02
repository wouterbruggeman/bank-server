#ifndef USERSESSION_H
#define USERSESSION_H

#include <QObject>

class UserSession : public QObject
{
	Q_OBJECT

public:
	explicit UserSession(QObject *parent = 0);
	~UserSession();

signals:
	void signalSendData(QByteArray);

public slots:
	void slotReceiveData(QByteArray);

protected:

};

#endif

