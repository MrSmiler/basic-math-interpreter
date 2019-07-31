#include <iostream>
#include "lex.h"
#include "token.h"
#include "grammar.h"
#include "parser.h"
#include  <stack>

void pushNum(int);
void add(int);
void sub(int);
void mul(int);
void div(int);


std::stack<int> nums;

int main(){
    
    std::string mathStr;

    // std::cout << ">>> ";
    // std::getline(std::cin, mathStr);
    // mathStr = "((9 - 3)* 8) + (2*2)";
    std::vector<Token*> tokens;
    

    std::vector<std::string> variables = {"A", "B",
					  "C", "D",
					  "E"};

    std::vector<std::string> terminals = {"+", "-",
					  "*", "/",
					  "(", ")",
					  "num"};

    Grammar* expGrammar = new Grammar(variables, terminals, "A");

    expGrammar->addProduct("A", "C B");
    expGrammar->addProduct("B", "+ C B", add);
    expGrammar->addProduct("B", "- C B", sub);
    expGrammar->addProduct("B", "epsilon");
    expGrammar->addProduct("C", "E D");
    expGrammar->addProduct("D", "* E D", mul);
    expGrammar->addProduct("D", "/ E D", div);
    expGrammar->addProduct("D", "epsilon");
    expGrammar->addProduct("E", "( A )");
    expGrammar->addProduct("E", "num", pushNum);

    



    while(1) {

	std::cout << ">>> ";
	std::getline(std::cin, mathStr);

	// should not create new lex object every time
	// but since its for practice it does not matter
	Lexical* lex = new Lexical(mathStr);
	lex->scan();

	// is there was any lexical error
	if (lex->getStatus() != 0) {
	    continue;
	}

	tokens = lex->getTokens();
    
	// should not create new parser every time
	// but since its for practice it does not matter
	Parser* parser = new Parser(expGrammar);
	parser->parse(tokens);

	if (!parser->getStatus()) {
	    std::cout << ">>> "<< nums.top() << std::endl;
	    nums.pop();
	}
	else {
	    std::cout << "Error" << std::endl;
	}

	delete lex;
	delete parser;

    }

    

    return 0;
}


// push a number in to the stack
void pushNum(int n) {
    nums.push(n);    
}

// add the two top numbers in the stack
void add(int n) {
    int x = nums.top();
    nums.pop();
    int y = nums.top();
    nums.pop();

    nums.push(x+y);
}

// subtract the two top numbers in the stack
void sub(int n) {

    int x = nums.top();
    nums.pop();
    int y = nums.top();
    nums.pop();

    nums.push(y-x);

}

// multiply the two top numbers in the stack
void mul(int n) {

    int x = nums.top();
    nums.pop();
    int y = nums.top();
    nums.pop();

    nums.push(y*x);
}

// divide the two top numbers in the stack
void div(int n) {

    int x = nums.top();
    nums.pop();
    int y = nums.top();
    nums.pop();

    nums.push(y/x);
}
