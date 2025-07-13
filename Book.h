#ifndef BOOK_H_
#define BOOK_H_
#include<iostream>
#include <vector>
#include <memory>
#include "ExoServices.h"
#include "User.h"
using namespace::std;
enum BookType{EBOOK,PAPERBOOK};
class User;
class product{

};
class EBook;
class Book : public product
{
private:
    const std::string title,ISBN,author_name,year;
    vector<string>demo;
    int price;
    bool hasDemo;
protected:
     shared_ptr<EBook>Demo;
public:
    int number_of_pages;
    Book();
    Book(std::string tilte,std::string ISBN,std::string author_name,int number_of_pages,int price,vector<string>demo={});
    const std::string&get_book_title()const;
    const int&get_price()const;
    bool get_isE()const;
    int get_number_of_pages()const;
    virtual bool buy_book(string&book_pdf)=0;
    bool has_demo()const;
    shared_ptr<EBook>get_demo_book();
    virtual ~Book();
};
Book::Book(){}
Book::Book(std::string tilte,std::string ISBN,std::string author_name,int number_of_pages,int price,vector<string> demo)
:title(tilte),ISBN(ISBN),author_name(author_name),price(price),demo(demo)
{
    if(!demo.empty())
        hasDemo=true;
}
const std::string&Book::get_book_title()const{
    return title;
}
const int&Book::get_price()const{
    return price;
}
int Book::get_number_of_pages()const{
    return number_of_pages;
}
bool Book::has_demo()const{
    return !demo.empty();
}
shared_ptr<EBook>Book::get_demo_book(){
    return Demo;
}
Book::~Book()
{
}

// ==================EBOOK===================
class EBook:public Book{
    private:
        std::vector<std::string>book_pages;
    public:
        EBook(std::string tilte,std::string ISBN,std::string author_name,int price,
            int number_of_pages,std::vector<std::string>book_pages,vector<string> demo={});
        void add_pages(std::vector<std::string> page);
        std::vector<std::string>&get_book_pages();
        std::string get_page_content(int posistion);
        virtual bool buy_book(string&book_pdf);
        const string to_pdf()const;
};
EBook::EBook(std::string tilte,std::string ISBN,std::string author_name,int price,
        int number_of_pages,std::vector<std::string>book_pages,vector<string> demo)
:Book(tilte,ISBN,author_name,number_of_pages,price,demo),book_pages(book_pages){
    if(has_demo())
        Demo=make_shared<EBook>(tilte,"0"+ISBN,author_name,0,number_of_pages/2,vector<string>(demo));
}
std::string EBook::get_page_content(int position){
    return book_pages[position];
}
void EBook::add_pages(std::vector<std::string> pages){
    for(auto page:pages)
        book_pages.push_back(page),number_of_pages++;
}
std::vector<std::string>&EBook::get_book_pages() {
    return book_pages;
}
const string EBook::to_pdf()const{
    return "Book";
}
bool EBook::buy_book(string&book_pdf){
    book_pdf=to_pdf();
    return 1;
}
// =====================PAPERBOOK========================
class PaperBook:public Book
{
private:
    int quantity;
public:
    PaperBook(std::string title,std::string ISBN,std::string author_name,int price,
        int number_of_pages,int quantity,vector<string> demo={});
    void inc_quantity(int newQuant);
    bool dec_quantity(int quant);
    virtual bool buy_book(string&book_pdf);
    ~PaperBook();
};

PaperBook::PaperBook(std::string title,std::string ISBN,std::string author_name,int price,
    int number_of_pages,int quantity,vector<string> demo)
:Book(title,ISBN,author_name,number_of_pages,price,demo),quantity(quantity)
{
    if(has_demo())
        Demo=make_shared<EBook>(title,"0"+ISBN,author_name,0,number_of_pages/2,vector<string>(demo));
}
void PaperBook::inc_quantity(int newQuant){
    quantity+=newQuant;
}
bool PaperBook::dec_quantity(int quant){
    if(quant<=quantity){
        quantity-=quant;
        return 1;
    }
    return 0;
}
bool PaperBook::buy_book(string&book_pdf){
    if(quantity)
        return quantity--;
    return 0;
}
PaperBook::~PaperBook()
{
}

std::shared_ptr<Book>book_factory(BookType bookType,std::string tilte,std::string ISBN,std::string author_name,
    int price,int number_of_pages,bool addDemo,int quantity={}){
    switch (bookType)
    {
    case BookType::EBOOK:{
        std::vector<std::string> pages;
        for (int i = 1; i <= number_of_pages; ++i) {
            std::string page;
            std::cout << "Enter page #" << i << ": ";
            std::getline(std::cin >> std::ws, page);
            pages.push_back(page);
        }
        if(addDemo){
            vector<string>demo(pages.begin(),pages.begin()+(pages.size())/2);
            return std::make_shared<EBook>(tilte,ISBN,author_name,price,number_of_pages,pages,demo);
        }
        return std::make_shared<EBook>(tilte,ISBN,author_name,price,number_of_pages,pages,vector<string>{});
        break;
    }
    case PAPERBOOK:
        if(addDemo){
            std::vector<std::string> pages;
            for (int i = 1; i <= number_of_pages/2; ++i) {
                std::string page;
                std::cout << "Enter page #" << i << ": ";
                std::getline(std::cin >> std::ws, page);
                pages.push_back(page);
            }
            vector<string>demo(pages.begin(),pages.begin()+pages.size());
            return std::make_shared<PaperBook>(tilte,ISBN,author_name,price,number_of_pages,quantity,demo);
        }
        return std::make_shared<PaperBook>(tilte,ISBN,author_name,price,number_of_pages,quantity,vector<string>{});
    
    }
    return nullptr;
}
#endif

