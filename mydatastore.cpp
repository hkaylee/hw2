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
        keywordMap_.insert(std::make_pair(*it, std::set<Product*>{p})); // insert to map
    }
}

void MyDataStore::addUser(User *u){
    users_.insert(u); 

    cart_.insert(std::make_pair(u->getName(), std::deque<Product*>()));


}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){

}

void MyDataStore::addToCart(std::string username, int hit_result_index){
    if(users_.find(username) == users_.end()){
        std::cout<< "Invalid Request"<< std::endl; 
    }

}

void MyDataStore::viewCart(std::string username) const {

}

void MyDataStore::buyCart(std::string username){

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