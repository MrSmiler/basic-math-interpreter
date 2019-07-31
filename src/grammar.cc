#include "grammar.h"
#include "util.h"
#include <string>

// Term constructor
Term::Term(TermType type, std::string value) {
    this->type = type;
    this->value = value;
}

/*
Term::Term(TermType type, void (*funcptr)(int)){
    this->type = type;
    this->fptr = funcptr;
}
*/

// get term type
Term::TermType Term::getType() {
    return this->type;
} // getType

// get term value
std::string Term::getValue() {
    return this->value;
} // getValue

// product constructor
Product::Product(Term left, std::vector<Term> right) {
    this->left = left; 
    this->right = right;
} // Product

Product::Product(const Product& other) {
    this->left = other.left;
    this->right = other.right;
} // Product

Product& Product::operator=(Product other) {

    this->left = other.left;	
    this->right = other.right;
    return *this;

}


Term Product::getLeft(){
    return this->left;
} // getLeft

std::vector<Term> Product::getRight(){
    return this->right;
} // getRight



ExpGrammar::ExpGrammar() {

    std::string startVar = "E";
    std::vector<std::string> variables = {"E", "T", "F"};

    std::vector<std::string> terminals = {"+", "-", "*", "/",
					  "(", ")", "num"};

    int i;
    for (i = 0; i < variables.size(); i++){
	Term t1(Term::NT, variables[i]);
	this->variables.push_back(t1);	 
    }

    for (i = 0; i < terminals.size(); i++){
	Term t2(Term::T, terminals[i]);
	this->terminals.push_back(t2);
    }

    this->s = Term(Term::NT, startVar); 



    this->addProduct("E", "E + T");
    this->addProduct("E", "E - T");
    this->addProduct("E", "T");
    this->addProduct("T", "T * F");
    this->addProduct("T", "T / F");
    this->addProduct("T", "F");
    this->addProduct("F", "( E )");
    this->addProduct("F", "num");


}

bool ExpGrammar::findTerm(std::string str, std::vector<Term> terms){
    for(int i = 0; i < terms.size(); i++){
	if(!str.compare(terms[i].getValue())){
	   return true; 	
	} 
    }
    return false;

} // findTerm


void ExpGrammar::addProduct(std::string left, std::string right) {
    Term productLeft = Term(Term::NT, left);
    
    std::vector<std::string> words = util::split(right, ' ');
    std::vector<Term> productRight; 
    
    for (int i = 0; i < words.size(); i++) {
	
	if (!words[i].compare("epsilon")) {
	    break;	
	}
	// word is within terminals
	else if (this->findTerm(words[i], this->terminals)) { 
	    Term t1(Term::T, words[i]);	
	    productRight.push_back(t1);
	}
	else if (this->findTerm(words[i], this->variables)) {
	    Term t2(Term::NT, words[i]);	
	    productRight.push_back(t2);
	}
	else {
	    throw "invalid Term";
	}

    } // for


    this->products.push_back(Product(productLeft, productRight));

} // addProduct

Product ExpGrammar::getProduct(int i) {
    return this->products[i];
}

void getAction(int state, Term t) {
    switch(state) {
    
	case 0:
	     
    
    } 
}



