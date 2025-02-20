#include <sstream>
#include <iostream>
#include <iomanip>
#include "mydatastore.h"


// constructor
MyDataStore::MyDataStore()
{

}

//destructor
MyDataStore::~MyDataStore()
{
    // deallocate products set
    for (std::set<Product*>::iterator pit = products_.begin(); pit != products_.end(); ++pit){
        delete *pit; 
    }

    // deallocate users set 
    for (std::set<User*>::iterator uit = users_.begin(); uit != users_.end(); ++uit){
        delete *uit; 
    }
}

void MyDataStore::addProduct(Product *p){
    products_.insert(p); // add to product set 

    std::set<std::string> keywords = p->keywords(); // get keywords for product 

    for(std::set<std::string>::iterator it = keywords.begin(); it != keywords.end(); ++it){
        keywordMap_[convToLower(*it)].insert(p); // insert to map


    }

    std::cerr << "added product: " << p->getName()<<std::endl;
}

void MyDataStore::addUser(User *u){
    std::string caseInsensitiveUser = convToLower(u->getName()); 
    users_.insert(u); 

    cart_[caseInsensitiveUser] = std::deque<Product*>();
    std::cerr << "User added: " << caseInsensitiveUser <<std::endl; 


}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    std::vector<Product*> results; // stores search results 

    if (terms.empty()) { // no terms 
        return results; 
    }

    std::set<Product*> matchingProducts; // store matching products

    for (std::vector<std::string>::iterator it = terms.begin(); it != terms.end(); ++it) { // iterate through search terms
        std::map<std::string, std::set<Product*>>::iterator kit = keywordMap_.find(convToLower(*it)); // find in keyword map
        
        // missing keywords 
        if (kit == keywordMap_.end()) { // search is not found in the map 
            if (type == 0) { // and search
                return results; // empty results 
            }
            continue; // skip missing keyword and continue search 
        }

        if (matchingProducts.empty()) { // for first keyword found 
            matchingProducts = kit->second; // set of products match first keyword
        } 
        else { // terms exists 
            if (type == 0) { // intersection, keep products that match all keywords 
                matchingProducts = setIntersection(matchingProducts, kit->second);
            } 
            else { // union- only matches at least one keyword
                matchingProducts = setUnion(matchingProducts, kit->second);
            }
        }
    }

    for (std::set<Product*>::iterator prodit = matchingProducts.begin(); prodit != matchingProducts.end(); ++prodit) {
        results.push_back(*prodit); 
    }

    std::cerr << "Search results (" << results.size() << "):" << std::endl;
    for (size_t i = 0; i < results.size(); i++) {
        std::cerr << i+1 << ": " << results[i]->displayString() << std::endl;
    }

    hits_.clear(); 
    hits_ = results; 

    return results; // return vector 

}

void MyDataStore::addToCart(std::string username, int hit_result_index){
    std::string caseInsensitiveUser = convToLower(username); 

    // Find user in users_
    if(cart_.find(caseInsensitiveUser) == cart_.end()){
      std::cout << "Invalid request" << std::endl;
      return; 
    }

    if(hits_.empty() || hit_result_index < 1 || hit_result_index > static_cast<int>(hits_.size())){
      std::cout << "Invalid request" << std::endl;
      return; 
    }
    // for (std::set<User*>::iterator uit = users_.begin(); uit != users_.end(); ++uit) {
    //     if ((*uit)->getName() == username) {
    //         userFound = true;  
    //         break; 
    //     }
    // }

    Product* newProduct = hits_[hit_result_index - 1]; // vector 0 indexed
    cart_[caseInsensitiveUser].push_back(newProduct); // add product to cart 
    std::cerr << "Added to cart: " <<caseInsensitiveUser << " "<< newProduct->displayString()<< std:: endl; 


}

void MyDataStore::viewCart(std::string username) const {
  std::string caseInsensitiveUser = convToLower(username); 
    if(username.empty()){
        std::cout<< "Invalid username" << std::endl; 
        return;
    }
    
    // Find user in users_
    if(cart_.find(caseInsensitiveUser) == cart_.end()){
      std::cout<< "Invalid username" << std::endl; 
      return; 
    }

    // Find the user's cart
    std::map<std::string, std::deque<Product*>>::const_iterator cit = cart_.find(caseInsensitiveUser);

    // check if user has a cart or if cart is empty 
    if (cit == cart_.end() || cit->second.empty()) {
        std::cout << "Empty Cart" << std::endl;
        return;
    }

    // Print cart 
    int index = 1;
    for (std::deque<Product*>::const_iterator pit = cit->second.begin(); pit != cit->second.end(); ++pit) {
        std::cout << "Item " << index << "\n" << (*pit)->displayString() << std::endl << std::endl;
        index++;
    }

}


// buy cart, if item is in stock and enough money, reduce qty and credit. if out of stock or user does not have enough credit, move on to next product 
void MyDataStore::buyCart(std::string username) {
    // for each item in cart 
    // reduce qty by 1 
    // reduce credit 
    // if qty = 0 || credit <price ++product 
    std::string caseInsensitiveUser = convToLower(username); 
    User* user = nullptr;

    // Find user in users_
    for (std::set<User*>::iterator uit = users_.begin(); uit != users_.end(); ++uit) {
        if (convToLower((*uit)->getName()) == caseInsensitiveUser) {
            user = *uit;
            break;
        }
    }

    if(user == nullptr){
        std::cout << "Invalid username" << std::endl;
        return;
    }

    // Find the cart for the user
    std::map<std::string, std::deque<Product*>>::iterator cit = cart_.find(caseInsensitiveUser);
    if (cit == cart_.end()) {
        std::cout << "Invalid request" << std::endl;
        return;
    }

    std::deque<Product*>& cart = cit->second;
    std::deque<Product*> remainingCart; 

    while (!cart.empty()) {
        Product* product = cart.front();
        cart.pop_front();

        // no qty and user doesn't have enough money 
        if (product->getQty() == 0 || user->getBalance() < product->getPrice()) {
            remainingCart.push_back(product);
        } else {
            product->subtractQty(1);  // Reduce product quantity
            user->deductAmount(product->getPrice()); 
        }
    }

    // Update cart
    cart = remainingCart;
}


// save current database to a file after quit 
void MyDataStore::dump(std::ostream& ofile){
    ofile << "<products>\n"; 
    for (std::set<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
        (*it)->dump(ofile);
    }
    ofile << "</products>\n"; 
    ofile << "<users>\n"; 
    for (std::set<User*>::iterator it = users_.begin(); it != users_.end(); ++it){
        (*it)->dump(ofile);
    }
    ofile << "</users>\n"; 
}