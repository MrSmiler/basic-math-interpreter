#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "token.h"
#include <string>
#include <vector>
#include <iostream>
#include <stack>

// a Term is either a Terminal or a Non terminal
class Term {
     
    public:
	enum TermType {
	    T, // Terminal
	    NT, // Non Terminal
	};
	Term(){};
	Term(TermType type, std::string value);
	// Term(TermType type, void (*funcptr)(int)=nullptr);
	TermType getType();
	std::string getValue();

	// set numerical value
	void setNVal(std::string);

	// set numerical value
	void setNVal(int);


	// get numerical value
	int getNVal();


    protected:
	// term type
	TermType type;

	// term string value
	std::string value;

	// numerical value
	int nval = 0;

}; // Term


// product of a grammar
// ex: E -> E + E
class Product {	 
    private:
	Term left;	
	std::vector<Term> right;

	// product action
	// like E -> E + T {product action}
    public:
	Product(Term left, std::vector<Term> right, void (*action)(Term& leftTerm, std::stack<Term>& s));

	Product(const Product& other);
	void (*action)(Term& leftTerm, std::stack<Term>& s);

	Product& operator=(Product other);

	// get left side of the product
	Term getLeft();

	// get right of the product
	std::vector<Term> getRight();

}; // Product 

// bottom-up parser Action
class Action {
    public: 
	enum ActionType {
	    INIT,
	    SHIFT,
	    GOTO,
	    REDUCE, 
	    ERROR,
	    ACCEPT
	};
    
	Action() {};

	Action(ActionType type, int value = -1);
	ActionType getType();
	int getValue();
    private:
	ActionType type;	
	int value;

};


// Math Expression Grammar
// mathematical Grammar defination:
// Gramamr: <Variables, Terminals, Start variable, Proudcts>
class Grammar {

    public:
	Grammar();

	Product getProduct(int);

	// get a action from the action section of the parsing table
	Action getAction(int state, Token t);

	// get a action from the goto section of the parsing table 
	Action getAction(int state, Term t);

    private:
	
	// add new product to grammar
	void addProduct(std::string left, std::string right, void (*action)(Term& leftTerm, std::stack<Term>& s));

	// find the a term amonge the terminals and variables
	bool findTerm(std::string str, std::vector<Term> terms);

	// grammar variables
	std::vector<Term> variables;

	// grammar terminals
	std::vector<Term> terminals;

	// start variable
	Term s;

	// grammar products
	std::vector<Product> products;
};

#endif

