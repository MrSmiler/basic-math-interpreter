
#include "token.h"
#include "util.h"
#include "lex.h"
#include <iostream>

Lexical::Lexical(std::string text){
    this->text = text;
    this->state = START_STATE;
    this->forward = -1;
    this->status = 0;
}

Lexical::~Lexical(){
    /*
    for(int i = 0; i < this->tokens.size(); i++){
	delete this->tokens[i]; 
    }
    */
}

std::vector<Token> Lexical::getTokens(){
    return this->tokens;
}

Token Lexical::nextToken() {

    char ch;
    std::string token_type;
    std::string token_value;
    Token token;
    while(this->nextChar() && !this->status){
	ch = this->getChar();

	switch(this->state){
	    case START_STATE:
		
		if(util::isNumber(ch)){
		    this->word_begin = this->forward;
		    this->state = STATE_NUM; 
		}
		else if (ch == '+' ||
			 ch == '-' ||
			 ch == '*' ||
			 ch == '/'){
			
		    this->word_begin = this->forward;
		    this->state = STATE_OP; 
			 
		}
		else if (ch == '('  ||
			 ch == ')'){
		
		    this->word_begin = this->forward;
		    this->state = STATE_SEP;
		}
		else if (ch == ' '  ||
			 ch == '\n' ||
			 ch == '\t' ||
			 ch == '\0'){
			 
		    this->state = START_STATE;	 
		} 
		else {
		    this->state = ERROR_STATE; 		
		}

		break;

	    case STATE_NUM:
		if(util::isNumber(ch)){
		    this->state = STATE_NUM;	
		}
		else {
		    token_type = "num";    
		    this->state = FINAL_STATE;	
		}

		break;


	    case STATE_OP:
		
		token_type = "op";
		this->state = FINAL_STATE;

		break;


	    case STATE_SEP:
		token_type = "sep";
		this->state = FINAL_STATE;
		break;

	    case FINAL_STATE:
		this->forward--;	
		token_value = util::createString(this->word_begin, 
						 this->forward, 
						 this->text);

		token = Token(token_type, token_value);
		
		this->tokens.push_back(token);

		this->state = START_STATE;

		return token;
		
		break;

	    case ERROR_STATE:
		this->status= 1;

		std::cout << "invalid character '" << this->text[this->forward] << "'" << std::endl;

		return Token("", "");
		
		break;

	} // switch

	

    } // while

    if (this->status == 2) {
	throw "end of file"; 
    }

    if (!this->status){
	Token token("eos", "eos");
	this->tokens.push_back(token);
	this->status = 2;
	return token;
    }

} // scan

bool Lexical::nextChar(){
    if (this->state != FINAL_STATE && this->state != ERROR_STATE){
	this->forward++;
    }
    if (this->forward == text.size() + 1){

	// current character is null
	return false;		 
    }
    return true;

} // nextChar

char Lexical::getChar(){
    return this->text[this->forward];
} // getChar

void Lexical::printTokens(){
    /*
    for(int i = 0; i < this->tokens.size(); i++){
	std::cout << this->tokens[i]->getValue() << std::endl; 
    } 
    */
} // printTokens

int Lexical::getStatus() {
    return this->status;
}

