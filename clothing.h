#ifndef CLOTHING_H
#define CLOTHING_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"

/**
 * derived product class Clothing implementing the keywords() which return keywords 
 * displayString() creates string that contains Product info 
 * dump()- outputs database format of Product info 
 * Clothing: size, brand
 */

class Clothing : public Product{
public:
    // constructor
    Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand);
    // destructor
    ~Clothing();

    /**
     * Returns the appropriate keywords that this Clothing should be associated with
     */
    std::set<std::string> keywords() const override;

    /**
     * Returns a string to display the Clothing info for hits of the search
     */
    std::string displayString() const override;

    /**
     * Outputs the Clothing info in the database format
     */
    void dump(std::ostream& os) const override;

private:
    std::string size_;
    std::string brand_;

};
#endif

