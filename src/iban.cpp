#include <QString>

#include "iban.h"

Iban::Iban() {
	m_countryLength.insert("NL", 18);
}

Iban::~Iban() {
}

void Iban::format(QString &iban) {
	iban = iban.toUpper();
	iban.replace(" ", "");
}

bool Iban::isValid(QString iban) {
	bool valid = true;

	format(iban);

	// Length check
	if (m_countryLength[iban.left(2)] != iban.size()) {
		valid = false;
	}

	if (valid) {
		QString ibanInt = convertIbanToNumber(iban);

		// IBAN % 97 must return 1
		if (modulo97(ibanInt) != 1) {
			valid = false;
		}
	}

	return valid;
}

int Iban::calculateCheckDigit(QString countryCode, QString number) {
	int checkDigit = -1;

	format(countryCode);
	format(number);

	// Length check
	if (m_countryLength[countryCode] != number.size() + 4) {
		return checkDigit;
	}

	QString ibanInt = convertIbanToNumber(countryCode + "00" + number);

	return 98 - modulo97(ibanInt);
}

QString Iban::convertIbanToNumber(QString iban) {
	QString ibanInt = "";

	int size = iban.size();

	// Move the 4 initial characters to the end of the string
	iban = iban.right(size - 4) + iban.left(4);

	const char *data = iban.toUtf8().data();
	// Convert IBAN to int (A = 10, Z = 35)
	for (int i = 0; i < size; i++) {
		// Between char A and Z
		if (data[i] >= 65 && data[i] <= 90) {
			ibanInt.append(QString::number(data[i] - 55));
		}
		else {
			ibanInt.append(data[i]);
		}
	}

	return ibanInt;
}

int Iban::modulo97(QString bigInt) {
	int result = -1;

	while (true) {
		if (result == -1) {
			// Modulo 97 of the first 9 numbers
			result = bigInt.left(9).toInt() % 97;
			// Chop off first 9 numbers
			bigInt = bigInt.right(bigInt.size() - 9);
		}
		else if (bigInt.size() >= 1) {
			// Module 97 off the previous result + the next 7 numbers
			QString tmp = QString::number(result) + bigInt.left(7);
			result = tmp.toInt() % 97;

			// If we reached the end, set to empty
			if (bigInt.size() < 7) {
				bigInt = "";
			}
			// Otherwise, chop off the next 7 numbers
			else {
				bigInt = bigInt.right(bigInt.size() - 7);
			}
		}
		// Exit when there are no numbers left
		else if (bigInt.isEmpty()) {
			break;
		}
	}

	return result;
}
