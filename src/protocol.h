#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <stdint.h>

//-- General --//

#define CARD_UID_MAX 12
#define CARD_UID_MIN 8
#define IBAN_MAX 34
#define IBAN_MIN 9
#define LENGTH_MAX 255
#define PIN_ENTRY_MAX 3
#define PIN_MAX 12
#define PIN_MIN 4

// Packet types
enum requests {
	PING,
	PING_R,
	LOGIN,
	LOGIN_R,
	LOGOUT,
	LOGOUT_R,
	ACCOUNT_LIST,
	ACCOUNT_LIST_R,
	USER_DATA,
	USER_DATA_R,
	PAGEVIEW,
	PAGEVIEW_R,
	TRANSACTION,
	TRANSACTION_R,
};

// Account types
enum account {
	A_PAYMENT,
	A_SAVINGS,
};

//-- Shared requests / responses --//

struct shared_ping {
	uint8_t random;
};

//-- Requests --//

// Request header
struct request {
	uint8_t type;
	uint8_t size;
};

struct request_login {
	char card[CARD_UID_MAX];
	char pin[PIN_MAX];
};

//-- Responses --//

// Response status
enum response_status {
	S_TIMEOUT = -2,
	S_INVALID,
	S_FAIL,
	S_OK,
};

// Response header
struct response {
	uint8_t type;
	int8_t status;
	uint8_t size;
};

struct response_login {
	uint8_t failed_attempts;
};

#endif
