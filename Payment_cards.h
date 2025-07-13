#ifndef PAYMENT_CARDS_H_
#define PAYMENT_CARDS_H_
#include <iostream>
using namespace::std;
class PaymentCard {
protected:
	string owner_name;
	string card_number;
	string expiry_date;
	int security_code;
};

#endif