#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"


Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author) :
    Product::Product(category, name, price, qty), 
    isbn_(isbn), 
    author_(author)
{

}

Book::~Book()
{

}

 /**
     * Returns the appropriate keywords that this Book should be associated with
     */
std::set<std::string> Book::keywords() const{
    std::set<std::string> keywordSet; 

    std::set<std::string> nameKeywords = parseStringToWords(name_);
    for (std::set<std::string>::iterator nit = nameKeywords.begin(); nit != nameKeywords.end(); ++nit) {
        keywordSet.insert(*nit);
    }

 
    std::set<std::string> authorKeywords = parseStringToWords(author_);
    for (std::set<std::string>::iterator ait = authorKeywords.begin(); ait != authorKeywords.end(); ++ait) {
        keywordSet.insert(*ait);
    }

    keywordSet.insert(isbn_); 
    return keywordSet; 

}

    /**
     * Returns a string to display the Book info for hits of the search
     */
std::string Book::displayString() const {
    std::string s = name_ + "\n" + "Author: " + author_ + " ISBN: " + isbn_ + "\n" + std::to_string(price_) + " " + std::to_string(qty_) + " left.";

    return s;
 
}



void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << std::endl;
}



