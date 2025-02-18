#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <map>
#include <deque>
#include <vector>
#include "product.h"
#include "user.h"
#include "util.h"
#include "datastore.h"

/**
 *
 * A derived version of the DataStore can provide other services as well but
 * must support those below
 * searching (setintersection and setunion), adding products and users, saving the database,
 * store products and users 
 * 1. search (map between keywords and products)
 *    -  hits with displayProducts(vector<Product*>& hits) from amazon.cpp
 * 2. add to carts (FIFO with deque), invalid request if no username or hit_result_index
 * 3. viewcart username command, print cart 
 * 4. buy cart, if item is in stock and enough money, reduce qty and credit. if out of stock or user does not have enough credit, move on to next product 
 * 5. quit , save database into filename
 */


class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();

    /**
     * Adds a product to the data store
     */
    void addProduct(Product* p) override;

    /**
     * Adds a user to the data store
     */
    void addUser(User* u) override;

    /**
     * Performs a search of products whose keywords match the given "terms"
     *  type 0 = AND search (intersection of results for each term) while
     *  type 1 = OR search (union of results for each term)
     */
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;

    /**
     * Reproduce the database file from the current Products and User values
     */
    void dump(std::ostream& ofile) override;

     
    /**
     * Adds a product to the user's shopping cart
     */
    void addToCart(std::string username, int hit_result_index);

    /**
     * Views the contents of a user's shopping cart
     */
    void viewCart(std::string username) const;

    /**
     * Allows the user to purchase items from their shopping cart
     */
    void buyCart(std::string username);

private:
    std::set<Product*> products_; // set of all products (pointers to product)
    std::set<User*> users_; // set of all users 
    std::map<std::string, std::set<Product*>> keywordMap_; // keyword and set of products that match keyword
    std::map<std::string, std::deque<Product*>> cart_; // username and shopping cart for user (FIFO order)



};

#endif
