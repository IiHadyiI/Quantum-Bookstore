#ifndef __USER__
#define __USER__
#include <iostream>
#include <vector>
#include<map>
#include"Book.h"
#include"Inventory.h"
#include"Payment_cards.h"
#include "Session.h"
#include "Utils.h"

class User{
    private:
        std::string user_name;
        std::string password;
        std::string name;
        std::string email;
		std::string address;
        std::vector<Book>books;
        std::vector<Session>my_sessions;
		PaymentCard paymentCard;
        bool isAdmin;
        int user_count=0;
    public:
        User(std::string user_name,std::string password,std::string email,std::string name
			,std::string address,bool isAdmin=false);
        ~User();
        Session&add_session(EBook&ebook);
        int display_my_reading_history()const;
        const std::string&get_user_name()const;
        const std::string&get_password()const;
        const std::string&get_name()const;
        const std::string&get_email()const;
        const std::string&get_address()const;
        const bool  is_library_admin()const;
        void view_profile()const;
		Session&get_session(int idx);
};

User::User(std::string user_name,std::string password,std::string email,
	std::string name,std::string address,bool isAdmin)
:user_name(user_name),password(password),name(name),email(email)
,user_count(user_count+1),address(address),isAdmin(isAdmin),paymentCard(PaymentCard()){}
User::~User(){}
int User::display_my_reading_history()const{
    for(int i=0;i<my_sessions.size();i++)
        std::cout << i+1 << ":" 
            << my_sessions[i].get_book_name()
            << " Page:" << my_sessions[i].get_current_page()
            << " - " << my_sessions[i].get_session_date() << "\n";
    return my_sessions.size();
}
const std::string&User::get_user_name()const{
    return user_name;
}
const std::string&User::get_password()const{
    return password;
}
const std::string&User::get_name()const{
    return name;
}
const std::string&User::get_email()const{
    return email;
}
const std::string&User::get_address()const{
	return address;
}
const bool User::is_library_admin()const{
    if(isAdmin)
        return 1;
    return 0;
}
void User::view_profile()const{
    std::cout << " User-Name:\t\t" << user_name
    << "\n email:\t\t" << email 
    << "\n books: \n \t";
    for(auto&book:books)
        std::cout << book.get_book_title() << "\n \t";
}
Session&User::add_session(EBook&ebook){
    my_sessions.push_back(Session(ebook));
    return my_sessions.back();
}
Session&User::get_session(int idx){
	return my_sessions[idx];
}

// =======================================USER VIEW=====================================================
#include "UserManager.h"
class UserView {
private:
	UsersManager&users_manager;
	Inventory&inventory;
	SessionManager&sessoin_manager;
	PaymentCard&paymentCard;
public:

	UserView(UsersManager & users_manager, Inventory &inventory,SessionManager&sessoin_manager,PaymentCard&paymentCard) :
			users_manager(users_manager), inventory(inventory),sessoin_manager(sessoin_manager),paymentCard(paymentCard){

	}

	void Display(PurchaseService purchaseService) {
		const User* user = users_manager.GetCurrentUser();
		cout << "\n\nHello " << user->get_name() << " | User View\n";

		vector<string> menu;
		menu.push_back("View Profile");
		menu.push_back("List & Select from My Reading History");
		menu.push_back("List & Select from Available Books");
		menu.push_back("Logout");

		while (true) {
			int choice = ShowReadMenu(menu);
			if (choice == 1)
				ViewProfile();
			else if (choice == 2)
				ListReadingHistory();
			else if (choice == 3)
				ListAvailableBooks(purchaseService);
			else
				break;
		}
	}

	void ViewProfile() {
		const User* user = users_manager.GetCurrentUser();

		// cout << "\n" << user->ToString() << "\n";
	}

	void DisplaySession(Session& session) {
		vector<string> menu;
		menu.push_back("Next Page");
		menu.push_back("Previous Page");
		menu.push_back("Stop Reading");

		while (true) {
			cout << "Current Page: " << session.get_page_num() << "\n";
			cout << session.get_current_page() << "\n";

			int choice = ShowReadMenu(menu);
			if (choice == 1)
				session.next_page();
			else if (choice == 2)
				session.previous_page();
			else
				break;
		}
		session.set_date();
	}

	void ListReadingHistory() {
		int idx = users_manager.GetCurrentUser()->display_my_reading_history();

		if (idx == 0)
			cout << "\nNo history. List books and start having fun\n";
		else {
			cout << "\nWhich session to open?: ";
			int choice = ReadInt(1, idx);
			sessoin_manager.DisplaySession(users_manager.GetCurrentUser()->get_session(choice-1));
		}
	}

	void ListAvailableBooks(PurchaseService&purchaseService) {
		inventory.display_all_books();

		cout << "\nOur current book collection:\n";
		int idx = inventory.get_inventory_size();

		cout << "\nWhich book to read?: ";
		int choice = ReadInt(1, idx);	// For simplicity, assume a new book is selected
		if(choice>10){
			cout << "Paid amount: " << 
			users_manager.buy_book(inventory.get_book_by_index((choice/10)-1)->get_demo_book(),paymentCard,purchaseService);
		}
		else{
			cout << "Paid amount: " << 
			users_manager.buy_book(inventory.get_book_by_index(choice-1),paymentCard,purchaseService);
		}
	}
};


#endif

