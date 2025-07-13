#ifndef _BOOKNAVIGATOR_
#define _BOOKNAVIGATOR_
#include <iostream>
#include "User.h"
#include "Book.h"
#include <time.h>
#include "Utils.h"
class Session{
    private:
        std::string currentPage;
        EBook ebook;
        time_t ct=time(0);
        std::string currnettime;
        int current_page_num;
        int page_num;
        int it;
    public:
        Session(EBook&ebook);
        // ~Session();
        void set_current_page(std::string current);
        void set_date();
        void delete_session();
        void session_menu();
        const std::string&get_book_name()const;
        const std::string&get_current_page()const;
        const std::string&get_session_date()const;
        const int&get_page_num()const;
        void next_page();
        void previous_page();
};


Session::Session(EBook&ebook):ebook(ebook),page_num(1),it(0){}
void Session::set_current_page(std::string page){
    currentPage=page;
}
const std::string&Session::get_current_page()const{
    return currentPage;
}
void Session::set_date(){
    currnettime=ctime(&ct);
}
const std::string&Session::get_book_name()const{
    return ebook.get_book_title();
}
const std::string&Session::get_session_date()const{
    return currnettime;
}
const int&Session::get_page_num()const{
    return page_num;
}
void Session::next_page(){
    set_current_page(ebook.get_page_content(++it));
}
void Session::previous_page(){
    set_current_page(ebook.get_page_content(--it));
}
void Session::session_menu(){
    while(true){
        std::cout << "Current Page: " << page_num << "/" << ebook.get_number_of_pages() << "\n";
        std::cout << ebook.get_page_content(it) << "\n";
        std::cout << "Menu:\n"
        <<"\t\t1: Next Page\n"
        <<"\t\t2: Previous Page\n"
        <<"\t\t3:Stop Reading\n";
        int choise;
        std::cin >> choise;
        if(choise==1){
            if(page_num!=ebook.get_number_of_pages()){++it;++page_num;}
        }
        else if(choise==2){
            if(page_num!=1)--it,--page_num;
        }
        else if(choise==3){
            set_date();
            set_current_page(ebook.get_page_content(it));
            current_page_num=page_num;
            break;
        }
    }
}

// ========================================SESSION MANAGER===================================================

class SessionManager
{
private:
    
public:
    SessionManager(){}
    ~SessionManager(){}
    void DisplaySession(Session&session) {
		vector<string> menu;
		menu.push_back("Next Page");
		menu.push_back("Previous Page");
		menu.push_back("Stop Reading");

		while (true) {
			cout << "Current Page: " << session.get_page_num() << "\n";
			cout << session.get_current_page() << "\n";
            int choice=ShowReadMenu(menu);
			if (choice == 1)
				session.next_page();
			else if (choice == 2)
				session.previous_page();
			else
				break;
		}
		session.set_date();
	}
};

#endif

