#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

/**
 * derived product class Movie implementing the keywords() which return keywords 
 * displayString() creates string that contains Product info 
 * dump()- outputs database format of Product info 
 * Movie: genre, rating
 */

class Movie : public Product{
public:
    // constructor
    Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating);
    // destructor
    ~Movie();

    /**
     * Returns the appropriate keywords that this Movie should be associated with
     */
    std::set<std::string> keywords() const override;

    /**
     * Returns a string to display the Movie info for hits of the search
     */
    std::string displayString() const override;

    /**
     * Outputs the Movie info in the database format
     */
    void dump(std::ostream& os) const override;

private:
    std::string genre_;
    std::string rating_;

};
#endif

