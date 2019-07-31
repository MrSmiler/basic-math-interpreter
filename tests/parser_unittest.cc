#include "gtest/gtest.h"
#include "../src/lex.h"
#include "../src/token.h"

namespace {

TEST(parserTest, parse) {
     

    std::string text = "(2 + 4) * 9  ";
    Lexical lexer(text);

    SlrExpGrammar grammar;
    LRParser parser(grammar);

    parser.parse(lexer);

    if (!parser.getStatus()) {
	std::cout << "successfull parsing\n"; 
    }
    else {
	parser.printErrors(); 
    }

    //parser.parse(tokens);
    //EXPECT_EQ();

} // TEST



} // namespace

