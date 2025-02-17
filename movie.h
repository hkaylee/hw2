#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>

/**
 * derived product class clothing implementing the keywords() which return keywords 
 * displayString() creates string that contains Product info 
 * dump()- outputs database format of Product info 
 * movie: genre, rating
 */

class Book : public Product{
public:
    Book(const std::string category, const std::string name, double price, int qty);
    virtual ~Book();

    /**
     * Returns the appropriate keywords that this Book should be associated with
     */
    virtual std::set<std::string> keywords() const = 0;

    /**
     * Allows for a more detailed search beyond simple keywords
     */
    virtual bool isMatch(std::vector<std::string>& searchTerms) const;

    /**
     * Returns a string to display the Book info for hits of the search
     */
    virtual std::string displayString() const = 0;

    /**
     * Outputs the Book info in the database format
     */
    virtual void dump(std::ostream& os) const;

    /**
     * Accessors and mutators
     */
    double getPrice() const;
    std::string getName() const;
    int getQty() const;
    void subtractQty(int num);

protected:
    std::string name_;
    double price_;
    int qty_;
    std::string category_;

};
#endif

