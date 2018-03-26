#ifndef IBAN_H
#define IBAN_H

class Iban
{

public:
	Iban();
	~Iban();

	static bool isValid(QString iban);
	static int modulo97(QString bigInt);

private:

};

#endif
