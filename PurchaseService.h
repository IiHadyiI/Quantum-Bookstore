#ifndef PURCHSESERVICE_H_
#define PURCHSESERVICE_H_
#include <iostream>
#include <memory>
#include "Book.h"
#include "ExoSErvices.h"
#include "Payment_cards.h"
#include "User.h"
using namespace::std;

class PurchaseService {
private:
    ExoServices&exo;
    const double fees;
public:
    PurchaseService(ExoServices&exo)
    :exo(exo),fees(50){}
    bool buy(string book_pdf, User& user) {
        if (!book_pdf.empty()) {
            exo.mail(user.get_email(),book_pdf);
            return 1;
        } else {
                exo.ship(user.get_address());
                return 1;
        }
        cout << "Unknown product type";
        return 0;
    }
    int ChargeCost(double cost, PaymentCard &payment_card) const {

        return cost+fees;
    }
};

#endif