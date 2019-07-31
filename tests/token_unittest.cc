
#include "../src/token.h"
#include "gtest/gtest.h"


namespace {

TEST(TokenTest, constructor){
    std::string type = "num";
    Token token(type, "10");
    EXPECT_EQ(type, token.getType());
    EXPECT_EQ("10", token.getValue());
    
    std::string type2 = "op";
    Token token2(type2, "+");
     
    EXPECT_EQ(type2, token2.getType());
    EXPECT_EQ("+", token2.getValue());
}

}
