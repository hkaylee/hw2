#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) :
    Product::Product(category, name, price, qty), 
    genre_(genre), 
    rating_(rating)
{

}

Movie::~Movie()
{

}

 /**
     * Returns the appropriate keywords that this Movie should be associated with
     */
std::set<std::string> Movie::keywords() const{
    std::set<std::string> keywordSet; 

    std::set<std::string> nameKeywords = parseStringToWords(name_);
    for (std::set<std::string>::iterator nit = nameKeywords.begin(); nit != nameKeywords.end(); ++nit) {
        keywordSet.insert(*nit);
    }

    std::set<std::string> ratingKeywords = parseStringToWords(rating_);
    for (std::set<std::string>::iterator rit = ratingKeywords.begin(); rit != ratingKeywords.end(); ++rit) {
        keywordSet.insert(*rit);
    }


    keywordSet.insert(genre_); 

    return keywordSet; 

}

    /**
     * Returns a string to display the Movie info for hits of the search
     */

std::string Movie::displayString() const {
    std::string price = std::to_string(price_);
    price = price.substr(0, price.find('.') + 3); 
    std::string s = name_ + "\n" + "Genre: " + genre_ + " Rating: " + rating_ + "\n" + price + " " + std::to_string(qty_) + " left.";

    return s;
 
}



void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << std::endl;
}



