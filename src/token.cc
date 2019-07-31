
#include "token.h"
#include <string>

Token::Token(std::string type, std::string value) {
    this->type = type;
    this->value = value;
}

Token::Token(const Token& t) {
    this->type = t.type;
    this->value = t.value;
}

Token& Token::operator=(const Token& t) {
    this->type = t.type;
    this->value = t.value;
    return *this;
}


std::string Token::getType() {
    return this->type;
}

std::string Token::getValue() {
    return this->value;
}
