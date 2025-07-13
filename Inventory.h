#ifndef INVENTORY_H_
#define INVENTORY_H_

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include "Book.h"

class Inventory {
private:
    std::vector<std::shared_ptr<Book>> books;

public:
    void add_book(std::shared_ptr<Book> book) {
        books.push_back(book);
    }

    std::shared_ptr<Book> get_book_by_title(const std::string& title) {
        for (auto& book : books) {
            if (book->get_book_title() == title)
                return book;
        }
        return nullptr;
    }

    std::shared_ptr<Book> get_book_by_index(int index) {
        if (index >= 0 && index < books.size())
            return books[index];
        return nullptr;
    }

    void display_all_books() const {
        for (size_t i = 0; i < books.size(); ++i) {
            std::cout << i + 1 << ". " << books[i]->get_book_title() ;
            if(books[i]->has_demo())
                cout << "\t" << i+1 << "2-View demo ";
            cout << "\n";
        }
    }

    int get_inventory_size() const {
        return books.size();
    }


    void LoadDatabase() {
		cout << "BooksManager: LoadDatabase\n";
        
		shared_ptr<Book> book1=make_shared<EBook>("C++ how to program","00001","Mostafa",500,5,
            vector<string>{"A C++","B C++","C C++","D C++","E C++"},vector<string>{"A C++","B C++"});
		add_book(book1);

        shared_ptr<Book> book2=make_shared<EBook>("Intro to algo","00002","Morad",500,5
            ,vector<string>{ "A Algo", "B Algo", "C Algo", "D Algo", "E " });
		add_book(book2);		

        shared_ptr<Book> book3=make_shared<EBook>("Intro to algo","00003","Mohammed",500,5
            ,vector<string>{ "A Data", "B Data", "C Data", "D Data", "E Data" });
		add_book(book3);
	}

};

#endif

