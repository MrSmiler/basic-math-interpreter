

#include "util.h"
#include <vector>
#include <string>

namespace util{

// create std::string word from beginnig and end index of the text
std::string createString(int begin, int end, std::string pstr){
    int pstr_length = end - begin + 1;


    char* str = new char[pstr_length];
    int l = 0;
    for (int i = begin; i <= end; i++){
        str[l++] = pstr[i]; 
    }
    str[l] = '\0';

    std::string new_str = str;
    delete [] str;
    
    return new_str;
}

// this determines a character is alphabet character
bool isAlpha(char ch){
    if ((ch > 64 && 
         ch < 91) ||
        (ch > 96 && 
         ch < 122)) {

        return true;
    }
    else {
        return false; 
    }
}


// this determines a character is number
bool isNumber(char ch){
    return (ch > 47 && ch < 58)? true: false;
}


// is operator
bool isOperator(char ch) {
    if (ch == '+' ||
        ch == '-' ||
	ch == '*' ||
	ch == '/') {
	    return true;	
	}
    return false;
}

bool isOperator(std::string ch) {
    if (!ch.compare("+") ||
        !ch.compare("-") ||
	!ch.compare("*") ||
	!ch.compare("/")) {
	    return true;	
	}
    return false;
}

// convert a string to integer
int convertToNumber(std::string num){
    int n = 0;

    for(int i = 0; i < num.size(); i++){
	// since number zero is in 48 place of ascii table
	n = n * 10 + (num[i] - 48); 
    }

    return n;
}

std::vector<std::string> split(std::string str, char delim){
    std::vector<std::string> words;
    int word_begin = 0;
    int i;
    for(i = 0; i < str.size()+1; i++){
	if (str[i] == delim) {
	    std::string s = util::createString(word_begin, i-1, str);
	    words.push_back(s);
	    word_begin = i + 1;
	}
    }        

    if(str[word_begin]){
	 std::string s = util::createString(word_begin, i-2, str);
	    words.push_back(s);
    }
    

    return words;
}

}
