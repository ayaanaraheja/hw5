#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm>
#include <map>
#include <set>
#endif
#include "wordle.h"
#include "dict-eng.h"
using namespace std;

// Add prototypes of helper functions here
void helper(
    std::string curr,
    const std::string& yellow_left,
    const std::set<std::string>& dict,
    std::set<std::string>& words_found,
    int index);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    std::set<std::string> words_found;
    helper(in, floating, dict, words_found, 0);
    return words_found;
}

// Define any helper functions here
void helper(
    std::string curr,
    const std::string& yellow_left,
    const std::set<std::string>& dict,
    std::set<std::string>& words_found,
    int index)
{
    if(index == curr.size()) {
        if(dict.find(curr) != dict.end() && yellow_left.empty()) {
            words_found.insert(curr); 
        }
            return;
    }


    if(curr[index] != '-') {
        helper(curr, yellow_left, dict, words_found, index + 1);
        return;
    }

    for(size_t i = 0; i < yellow_left.size(); ++i) {
        char floating_char = yellow_left[i];
        
        string next = curr;
        next[index] = floating_char;
        
        string next_yellow = yellow_left;
        next_yellow.erase(i, 1);
        
        helper(next, next_yellow, dict, words_found, index + 1);
    }

    int blanks_left = 0;
    for(size_t i = index + 1; i < curr.size(); ++i) {
        if(curr[i] == '-') blanks_left++;
    }
    
    if(yellow_left.size() <= blanks_left) {
        for(char c = 'a'; c <= 'z'; ++c) {
            if(yellow_left.find(c) != string::npos) { continue; }
            string next = curr;
            next[index] = c;
            
            helper(next, yellow_left, dict, words_found, index + 1);
        }
    }
}

//bool all_floating_used = true;
            
            //for(char c : floating) {
                //if(curr.find(c) == std::string::npos) {
                    //all_floating_used = false;
                    //break;
                //}
                //}
                
                //if(all_floating_used) {
                    //words_found.insert(curr);
                //}
            //}