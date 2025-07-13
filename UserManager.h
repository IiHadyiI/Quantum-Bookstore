#ifndef USERMANAGER_H_
#define USERMANAGER_H_
#include "User.h"
#include "ExoSErvices.h"
#include "PurchaseService.h"
class UsersManager {
private:
	User* current_user {nullptr};
	map<string, User*> userame_userobject_map;
	void FreeLoadedData() {
		for (auto pair : userame_userobject_map) {
			delete pair.second;
		}
		userame_userobject_map.clear();
		current_user = nullptr;
	}

public:
	UsersManager()
    {
	}

	~UsersManager() {
		cout << "Destuctor: UsersManager\n";
		FreeLoadedData();
	}

	UsersManager(const UsersManager&) = delete;
	void operator=(const UsersManager&) = delete;

	void LoadDatabase() {
		if (userame_userobject_map.size() > 0)
			return;		// let's assume 1 run for this system only

		cout << "UsersManager: LoadDatabase\n";

		FreeLoadedData();
		// Some "Dummy Data" for simplicity
		User* user1 = new User("mostafa","111","most@gmail.com","Mostafa Saad Ibrahim","cairo",true);
		userame_userobject_map[user1->get_user_name()] = user1;
		User* user2 = new User("asmaa","222","asmaa@gmail.com","Asmaa Saad Ibrahim","alex",false);
		userame_userobject_map[user2->get_user_name()] = user2;
	}

	void AccessSystem() {
		int choice = ShowReadMenu( { "Login", "Sign Up" });
		if (choice == 1)
			DoLogin();
		else
			DoSignUp();
	}

	void DoLogin() {
		LoadDatabase();

		while (true) {
			string user_name, pass;
			cout << "Enter user name (no spaces): ";
			cin >> user_name;
			cout << "Enter password (no spaces): ";
			cin >> pass;

			if (!userame_userobject_map.count(user_name)) {
				cout << "\nInvalid user user_name or password. Try again\n\n";
				continue;
			}
			User* user_exist = userame_userobject_map.find(user_name)->second;

			if (pass != user_exist->get_password()) {
				cout << "\nInvalid user user_name or password. Try again\n\n";
				continue;
			}
			current_user = user_exist;
			break;
		}
	}

	void DoSignUp() {
		string user_name;
		while (true) {
			cout << "Enter user name (No spaces): ";
			cin >> user_name;

			if (userame_userobject_map.count(user_name))
				cout << "Already used. Try again\n";
			else
				break;
		}

        string password;
		cout << "Enter password (no spaces): ";
		cin >> password;

        string name;
		cout << "Enter name (no spaces): ";
		cin >> name;

        string email;
		cout << "Enter email (no spaces): ";
		cin >> email;

		string address;
		cout << "Enter address (no spaces): ";
		cin >> address;

		current_user = new User(user_name,password,email,name,address);
		string t = current_user->get_user_name();
		userame_userobject_map[current_user->get_user_name()] = current_user;
	}

	User* GetCurrentUser() const {
		return current_user;
	}
    int buy_book(shared_ptr<Book>book,PaymentCard&card,PurchaseService&purchaseService){
        string book_pdf;
        if(book->buy_book(book_pdf)){
            int is_paid=purchaseService.ChargeCost(book->get_price(),card);
            auto Ebook = std::dynamic_pointer_cast<EBook>(book);
            if(is_paid){
                if(Ebook)
                    current_user->add_session(*Ebook);
                
                purchaseService.buy(book_pdf,*current_user);
                return is_paid;
            }
            else
                "Payment process failed\n";
        }
        else    
            cout << "Quantity isn't enough! \n";
		return 0;
    }
    void start_session(){
        
    }
};

#endif