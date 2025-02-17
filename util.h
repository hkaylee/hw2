#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <iostream>
#include <set>


/** Complete the setIntersection and setUnion functions below
 *  in this header file (since they are templates).
 *  Both functions should run in time O(n*log(n)) and not O(n^2)
 */
template <typename T>
std::set<T> setIntersection(std::set<T>& s1, std::set<T>& s2)
{
    // New set with all elements that appear in both set1 and set2
    std::set<T> s3; 

    for (typename set<T>::iterator it = s1.begin(); it != s1.end(); ++it) { // loop through set 1
        if(s2.find(*it) != s2.end()){ // it you find same *it in s2 before reaching end 
            s3.insert(*it);  // insert to s3 
        }
    }

    return s3; 

}
template <typename T>
std::set<T> setUnion(std::set<T>& s1, std::set<T>& s2)
{
    // New set with all elements that appear in either set1 and set2

    std::set<T> s3; 
    for (typename std::set<T>::iterator it = s1.begin(); it != s1.end(); ++it){
        s3.insert(*it);  // insert all of s1
    }

    for (typename std::set<T>::iterator it = s2.begin(); it != s2.end(); ++it){
        if(s1.find(*it) == s1.end()){ // if you don't find s2 elements in s1
            s3.insert(*it); // insert to set 
        }
    }

    return s3; 


}

/***********************************************/
/* Prototypes of functions defined in util.cpp */
/***********************************************/

std::string convToLower(std::string src);

std::set<std::string> parseStringToWords(std::string line);

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// Removes any leading whitespace
std::string &ltrim(std::string &s) ;

// Removes any trailing whitespace
std::string &rtrim(std::string &s) ;

// Removes leading and trailing whitespace
std::string &trim(std::string &s) ;
#endif
