#ifndef CARD_H
#define CARD_H

#include <QByteArray>

#define MAX_FAILED_ATTEMPTS 3

class Card{
	public:
		explicit Card();
		void setPincode(QByteArray pincode);
		void setUid(QByteArray uid);
		bool authenticate();
		bool hasAccess();
		char getFailedLoginAttempts();
		//User getOwner();

	private:
		void setFailedLoginAttempts(char amount);
		void clearFailedLoginAttempts();
		void incrementFailedLoginAttempts();

		QByteArray pincode;
		QByteArray uid;
		unsigned char failedLoginAttempts;
		bool accessGranted = false;
		int userId;
};
#endif
