#include <cstring>
#include <iostream>
#include <set>
#include <fstream>
#include <iterator>
#include <string>
#include "WordleGame.h"
using namespace std;

WordleGame:: WordleGame(const std::string& filename) {
    done = false;
    ifstream file;
    string word;
    file.open(filename);
    while (file >> word) {
        dictionary.insert(word);
    }
}

void WordleGame:: select_key(int index) {
    set<string> :: iterator i = dictionary.begin();
    advance(i,((index % dictionary.size())-1));
    key = *i;
}

std::string WordleGame:: score(const std:: string& input) {
    
    string currScore = "-----"; //5 characters
    string tempKey = key; //create a copy
    
    //if the input is not in the dictionary, print 'not in dictionary'
    if (!dictionary.count(input)) {
        return "not in dictionary";
    }
    
    //compare strings (5 characters)
    if (input[0] == key[0] && input[1] == key[1] && input[2] == key[2]
        && input[3] == key[3] && input[4] == key[4]) {
        done = true;
        return "*****";
    }else {
        
        //first step, match 100%
        //iterate the list
        for (int i = 0; i < 5; ++i) {
            if (input[i] == tempKey[i]) {
                currScore[i] = '*';
                tempKey[i] = '-';//mark as used
            }
        }
        
        //second step, find but in different position
        //iterate the list
        for (int i = 0; i < 5; ++i) {
            
            if (currScore[i] != '*')
            {
                //check if the input[i] is in different positions
                int j = 0;
                for (j = 0; j < 5; j++)
                {
                    if (input[i] == tempKey[j]) {
                        break;
                    }
                }
                
                if (j < 5)
                {//in different positions
                    currScore[i] = '+';
                    tempKey[j] = '-'; //mark as used
                }
            }
        }
    }
    
    return currScore;
}

bool WordleGame :: over(void) const {
    return done;
}


