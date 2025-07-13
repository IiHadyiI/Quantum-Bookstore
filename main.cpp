#include <iostream>
#include <vector>
#include "User.h"
#include "UserManager.h"
#include "Admin.h"
#include "TestClass.h"
using namespace :: std;
class OnlineReaderSystem {
private:
	Inventory inventory;
	UsersManager users_manager;
	SessionManager sessoinManager;
	ExoServices exoServices;
	PaymentCard paymentCard;
	PurchaseService purchaseService;
	void LoadDatabase() {
		users_manager.LoadDatabase();
		inventory.LoadDatabase();
	}
// g++ -std=c++17 -o main.exe main.cpp Book.cpp Session.cpp Inventory.cpp Admin.cpp User.cpp Utils.cpp ExoServices.cpp
public:
	OnlineReaderSystem() :
			inventory(Inventory()), users_manager(UsersManager()),sessoinManager(SessionManager())
			,paymentCard(PaymentCard()),exoServices(ExoServices()),purchaseService(PurchaseService(exoServices)) {
	}

	~OnlineReaderSystem() {
	}

	void Run() {	// only public one
		LoadDatabase();

		while (true) {
			users_manager.AccessSystem();	// login/signup

			// Let's make for every user, its own viewer class: Remember: Single responsibility principle
			if (users_manager.GetCurrentUser()->is_library_admin()) {
				Admin view(inventory,users_manager);
				view.admin_menu();
			} else {
				UserView view(users_manager,inventory,sessoinManager,paymentCard);
				view.Display(purchaseService);
			}
		}
	}
};
int main() {
    InventoryBlackBoxTester tester;
    tester.RunAll();
    
	OnlineReaderSystem sys=OnlineReaderSystem();
	sys.Run();
}	