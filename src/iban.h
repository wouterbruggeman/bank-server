#ifndef IBAN_H
#define IBAN_H

#include <QHash>

class Iban
{

public:
	Iban();
	~Iban();

	void format(QString &iban);
	bool isValid(QString iban);
	int calculateCheckDigit(QString countryCode, QString number);
	QString convertIbanToNumber(QString iban);
	int modulo97(QString bigInt);

private:
	QHash<QString, char> m_countryLength;

};

#endif
