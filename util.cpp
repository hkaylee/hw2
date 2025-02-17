#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"

using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
// split string of many words into individual keywords 
// define keyword of any string of 2 or more characters, split at each punctuation
// store in common case - use convToLower
// return a set- unique keys, unordered 
    std::set<std::string> keywordSet;
    std::string keyword;

    for (std::string::iterator it = rawWords.begin(); it != rawWords.end(); ++it) {
        if(std::isalpha(*it)){ // if char is valid alphabet
            keyword += *it;   // append to keyword 
        } else { // if reached punctuation mark don't append to keyword
            if(keyword.size() >= 2){  // if up until puncutation is at least 2 char long
                keywordSet.insert(convToLower(keyword));  // insert to set common case
            }
            keyword = ""; // reset keyword 
        }
    }

    if(keyword.size() >= 2){ // if no puncutation, if word at least 2 characters long 
        keywordSet.insert(convToLower(keyword)); // add to set  
    }

    return keywordSet; 

}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
