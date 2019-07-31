#include "../src/util.h"
#include "gtest/gtest.h"
#include <string>
#include <vector>



namespace {

TEST(ConvertToNumberTest, Integer){
    
	
    EXPECT_EQ(1, util::convertToNumber("1"));
    EXPECT_EQ(5, util::convertToNumber("5"));
    EXPECT_EQ(9, util::convertToNumber("9"));
    EXPECT_EQ(10, util::convertToNumber("10"));
    EXPECT_EQ(99, util::convertToNumber("99"));
    EXPECT_EQ(100, util::convertToNumber("100"));
    EXPECT_EQ(1234, util::convertToNumber("1234"));
    EXPECT_EQ(987654321, util::convertToNumber("987654321"));
     
    //EXPECT_EQ(type2, token2.getType());
}

TEST(splitTest, NormalString){
    std::string str = "hello mohsen where are you ?"; 
    std::vector<std::string>  words = util::split(str, ' ');

    EXPECT_EQ(6, words.size());
    EXPECT_EQ("hello", words[0]);
    EXPECT_EQ("mohsen", words[1]);
    EXPECT_EQ("where", words[2]);
    EXPECT_EQ("are", words[3]);
    EXPECT_EQ("you", words[4]);
    EXPECT_EQ("?", words[5]);

}

TEST(splitTest, spaceAtTheEnd){
    std::string str = "hello mohsen where are you ? "; 
    std::vector<std::string>  words = util::split(str, ' ');

    EXPECT_EQ(6, words.size());
    EXPECT_EQ("hello", words[0]);
    EXPECT_EQ("mohsen", words[1]);
    EXPECT_EQ("where", words[2]);
    EXPECT_EQ("are", words[3]);
    EXPECT_EQ("you", words[4]);
    EXPECT_EQ("?", words[5]);

}

TEST(splitTest, comaAsDelim){
    std::string str = "hello,mohsen,where,are,you,? "; 
    std::vector<std::string>  words = util::split(str, ',');

    EXPECT_EQ(6, words.size());
    EXPECT_EQ("hello", words[0]);
    EXPECT_EQ("mohsen", words[1]);
    EXPECT_EQ("where", words[2]);
    EXPECT_EQ("are", words[3]);
    EXPECT_EQ("you", words[4]);
    EXPECT_EQ("? ", words[5]);

}

TEST(isOpTest, basic){

    EXPECT_EQ(true, util::isOperator('+'));
    EXPECT_EQ(true, util::isOperator('-'));
    EXPECT_EQ(true, util::isOperator('*'));
    EXPECT_EQ(true, util::isOperator('/'));
    EXPECT_EQ(false, util::isOperator('('));
}









}
