#ifndef PARSER_H
#define PARSER_H

#include "Lex.h"
#include <stack>



class LRParser {

    public:
	LRParser(Grammar grammar);
	void parse(Lexical lexer);

    private:
	std::stack parse_stack;



}


#endif
