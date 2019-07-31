#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <string>
#include <vector>

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

    private:
	TermType type;
	std::string value;
	// void (*fptr)(int) = nullptr;

}; // Term


// product of a grammar
// ex: E -> E + E
class Product {	 
    private:
	Term left;	
	std::vector<Term> right;

    public:
	Product(Term left, std::vector<Term> right);
	Product(const Product& other);
	Product& operator=(Product other);
	Term getLeft();
	std::vector<Term> getRight();

}; // Product 


// Math Expression Grammar
// mathematical Grammar defination:
// Gramamr: <Variables, Terminals, Start variable, Proudcts>
class ExpGrammar {

    public:
	ExpGrammar();

	void getAction(int state, Term t);
	Product getProduct(int);
    private:

	void addProduct(std::string left, std::string right);
	bool findTerm(std::string str, std::vector<Term> terms);

	std::vector<Term> variables;
	std::vector<Term> terminals;
	Term s;
	std::vector<Product> products;

};


#endif
