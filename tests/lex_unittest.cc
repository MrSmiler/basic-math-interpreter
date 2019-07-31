#include "../src/lex.h"
#include "../src/token.h"
#include "gtest/gtest.h"
#include <string>
#include <vector>

namespace {

TEST(lexTest, getTokens) {

    std::string text = "(2 + 4) * 9  ";
    std::string samples[] = {"(", "2", "+", "4", ")", "*", "9", "eos"};
    std::vector<Token> tokens;
    Lexical lex(text);

    int i = 0;
    while(!lex.getStatus()) {
	EXPECT_EQ(samples[i++], lex.nextToken().getValue());
    }
}

TEST(lexTest, wrongInput) {
    std::string text = "(2 + 4) @ 9 ";
    std::vector<Token*> tokens;
    Lexical lex(text);

    while(!lex.getStatus()) {
	//EXPECT_EQ(samples[i++], );
	std::cout << lex.nextToken().getValue() << std::endl;
    }
}

} // ns
