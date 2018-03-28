#include <QDateTime>
#include <QSqlQuery>

#include "db.h"
#include "log.h"

Log::Log() {
}

Log::~Log() {
}

void Log::newLog(Log::Type type, QString value, int userId) {

	QSqlQuery user = Db::q("SELECT `id` FROM user WHERE `id`=?", {userId});
	if (user.exec() && user.size() == 1 && user.next()) {

		QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
		QSqlQuery insertLog = Db::q("INSERT INTO `user_log` (`type`, `value`, \
				`date_time`, `user_id`) VALUES (?, ?, ?, ?)",
				{(int)type, value, dateTime, userId});
		insertLog.exec();
#ifdef DEBUG
		printf("Log, inserted new log\n");
#endif
	}
}
