#ifndef LOG_H
#define LOG_H

class Log
{

public:
	Log();
	~Log();

	enum Type {
		LOGIN,
		LOGOUT,
		PAGE_VISIT,
	};

	void newLog(Log::Type type, QString value, int userId);

private:

};

#endif
