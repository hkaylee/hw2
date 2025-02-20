#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) :
    Product::Product(category, name, price, qty), 
    size_(size), 
    brand_(brand)
{

}

Clothing::~Clothing()
{

}

 /**
     * Returns the appropriate keywords that this Clothing should be associated with
     */
std::set<std::string> Clothing::keywords() const{
    std::set<std::string> keywordSet; 

    std::set<std::string> nameKeywords = parseStringToWords(name_);
    for (std::set<std::string>::iterator nit = nameKeywords.begin(); nit != nameKeywords.end(); ++nit) {
        keywordSet.insert(*nit);
    }

    std::set<std::string> sizeKeywords = parseStringToWords(size_);
    for (std::set<std::string>::iterator sit = sizeKeywords.begin(); sit != sizeKeywords.end(); ++sit) {
        keywordSet.insert(*sit);
    }

 
    std::set<std::string> brandKeywords = parseStringToWords(brand_);
    for (std::set<std::string>::iterator ait = brandKeywords.begin(); ait != brandKeywords.end(); ++ait) {
        keywordSet.insert(*ait);
    }

    return keywordSet; 

}

    /**
     * Returns a string to display the Clothing info for hits of the search
     */

std::string Clothing::displayString() const {
    std::string price = std::to_string(price_);
    price = price.substr(0, price.find('.') + 3);

    std::string s = name_ + "\n" + "Size: " + size_ + " Brand: " + brand_ + "\n" + price + " " + std::to_string(qty_) + " left.";

    return s;
 
}



void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << std::endl;
}



