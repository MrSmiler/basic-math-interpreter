
#ifndef LEX_H
#define LEX_H

#include "token.h"
#include <vector>
#include <string>


class Lexical{

    public:
	Lexical(std::string);	
	~Lexical();

	// scan the source code
	Token nextToken();

	// print the tokens
	void printTokens();

	// return the tokens 
	std::vector<Token> getTokens();

	// scanner status 0 mean without error and 1 means error
	int getStatus();


	enum STATES{
	    START_STATE,	
	    STATE_NUM,
	    STATE_OP,
	    STATE_SEP,
	    FINAL_STATE,
	    ERROR_STATE
	};

    private:
	// source code text
	std::string text;	

	// lexer error status
	char status;

	// valid tokens
	std::vector<Token> tokens;

	// beginning of a word
	int word_begin;

	// scanner current state
	int state;

	// current character index
	int forward;

	// increase text index
	bool nextChar();

	// get current character
	char getChar();

	
};


#endif // LEX_H
