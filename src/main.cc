#include <iostream>
#include "lex.h"
#include "token.h"
#include "grammar.h"
#include "parser.h"
#include  <stack>

#define print(word) std::cout << (word) << std::endl
#define printm(word) std::cout << word << std::endl

int main(){
    
    std::string text;;


    Grammar grammar;

    LRParser parser(grammar);

       
	
    print("Press <Ctrl-c> to exit");
    while (1) {
	std::cout << ">>> ";
	std::getline(std::cin, text); 
	
	Lexical lexer(text);
	parser.parse(lexer);

	// parsing was successfull
	if (parser.getStatus() == 0) {
	    printm(">>> " << parser.getResult());
	}
	else if (parser.getStatus() == 1) {
	    print("parser Error");
	}
	else if (parser.getStatus() == 2) {
	    print("lexer error"); 
	}
    
    }

    return 0;
}


