#include "gtest/gtest.h"
#include "../src/grammar.h"

namespace {

TEST(gramamrTest, init) {
     
    Grammar grammar;

    Product p = grammar.getProduct(1);
    EXPECT_EQ(p.getLeft().getValue(), "E");
    EXPECT_EQ(p.getRight()[1].getValue(), "+");
    
    //parser.parse(tokens);

} // TEST

} // namespace


