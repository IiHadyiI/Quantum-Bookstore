#include<iostream>
using namespace::std;

#include <iostream>
#include <cassert>
#include "Inventory.h"
#include "ExoServices.h"
#include "PurchaseService.h"
#include "User.h"
using namespace std;

class InventoryBlackBoxTester {
private:
    const double fees = 50;

public:
    void Test_AddBooks() {
        cout << __func__ << "\n";

        Inventory inventory;
        assert(inventory.get_inventory_size() == 0);

        auto book = make_shared<EBook>("C++ Book", "101", "Author", 500, 3, vector<string>{"A", "B", "C"});
        inventory.add_book(book);

        assert(inventory.get_inventory_size() == 1);
        assert(inventory.get_book_by_title("C++ Book") != nullptr);
    }

    void Test_RemoveExpiredBooks() {
        cout << __func__ << "\n";

        Inventory inventory;

        auto book1 = make_shared<EBook>("OldBook", "201", "Author", 500, 3, vector<string>{"A", "B", "C"});
        book1->set_expiry_date(-1); 

        auto book2 = make_shared<EBook>("NewBook", "202", "Author", 500, 3, vector<string>{"A", "B", "C"});
        book2->set_expiry_date(10);  

        inventory.add_book(book1);
        inventory.add_book(book2);

        assert(inventory.get_inventory_size() == 2);

        inventory.remove_expired_books();  
        assert(inventory.get_inventory_size() == 1);
        assert(inventory.get_book_by_title("OldBook") == nullptr);
        assert(inventory.get_book_by_title("NewBook") != nullptr);
    }

    void Test_BuyBook() {
        cout << __func__ << "\n";

        ExoServices exo;
        PurchaseService purchaseService(exo);
        User user("mohamed", "1234", "m@gmail.com", "Mohamed Hady", "Alex");
        auto ebook = make_shared<EBook>("Clean Code", "303", "Uncle Bob", 450, 5, vector<string>{"page1", "page2", "page3", "page4", "page5"});

        string pdf;
        assert(ebook->buy_product(pdf) == true);
        assert(!pdf.empty());

        int total_payment = purchaseService.ChargeCost(ebook->get_price(), *(new PaymentCard()));
        assert(total_payment == 500);
    }

    void RunAll() {
        Test_AddBooks();
        Test_RemoveExpiredBooks();
        Test_BuyBook();
        cout << "\n Passed All Inventory Tests\n";
    }
};
