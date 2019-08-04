#include "gtest/gtest.h"
#include "../src/lex.h"
#include "../src/token.h"
#include "../src/grammar.h"
#include "../src/parser.h"

#define print(word) std::cout << (word) << std::endl
#define printm(word) std::cout << word << std::endl


namespace {

TEST(parserTest, parse) {
     
    std::string text = "(2 + 10) / 4";
    Lexical lexer(text);

    Grammar grammar;

    LRParser parser(grammar);

    parser.parse(lexer);

    if (parser.getStatus() == 0) {
	print("Accept");
	print(parser.getResult());
    }
    else if (parser.getStatus() == 1) {
	print("parser Error");
    }
    else if (parser.getStatus() == 2) {
	print("lexer error"); 
    }

} // TEST


} // namespace

