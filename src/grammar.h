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
	void setNVal(std::string);
	void setNVal(int);
	int getNVal();


    protected:
	TermType type;
	std::string value;
	int nval = 0;
	// void (*fptr)(int) = nullptr;

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
	Term getLeft();
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
	Action getAction(int state, Token t);
	Action getAction(int state, Term t);

    private:

	void addProduct(std::string left, std::string right, void (*action)(Term& leftTerm, std::stack<Term>& s));

	bool findTerm(std::string str, std::vector<Term> terms);

	std::vector<Term> variables;
	std::vector<Term> terminals;
	Term s;
	std::vector<Product> products;

};

#endif
