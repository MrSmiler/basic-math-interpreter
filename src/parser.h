#ifndef PARSER_H
#define PARSER_H

#include "lex.h"
#include "grammar.h"
#include <stack>

/*
class ParsingSymbol: public Term {
    public:
	enum TermType {
	    T, // Terminal	
	    NT, // Non Terminal
	    S // State
	}
	

    private:
     

}
*/


// LR(0) parser
class LRParser {

    public:
	LRParser(Grammar grammar);
	void parse(Lexical lexer);
	int getStatus();
	int getResult(){return mathResult;}

    private:
	// holds the state of the parsing
	std::stack<int> state_stack;

	// holds the grammar symboles
	std::stack<Term> symbole_stack;
	
	// status of the parsing
	// 0 without errors
	// 1 there is or are parser errors 
	// 2 there is a lexer error
	int status;

	int mathResult = 0;

	Grammar grammar;	


};


#endif
