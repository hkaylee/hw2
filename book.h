#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

/**
 * derived product class book implementing the keywords() which return keywords 
 * displayString() creates string that contains Product info 
 * dump()- outputs database format of Product info 
 * book: ISBN, Author
 */

class Book : public Product{
public:
    // constructor
    Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author);
    // destructor
    ~Book();

    /**
     * Returns the appropriate keywords that this Book should be associated with
     */
    std::set<std::string> keywords() const override;

    /**
     * Returns a string to display the Book info for hits of the search
     */
    std::string displayString() const override;

    /**
     * Outputs the Book info in the database format
     */
    void dump(std::ostream& os) const override;

private:
    std::string isbn_;
    std::string author_;

};
#endif

