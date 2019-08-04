#include "grammar.h"
#include "token.h"
#include "util.h"
#include <string>
#include <stack>
#include <iostream>

#define s(i) action = Action(Action::SHIFT, i)
#define r(i) action = Action(Action::REDUCE, i)
#define ERROR action = Action(Action::ERROR)
#define g(i) action = Action(Action::GOTO, i)
#define ACCEPT action = Action(Action::ACCEPT)


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

void Term::setNVal(std::string val) {
    this->nval = util::convertToNumber(val);
}

void Term::setNVal(int val) {
    this->nval = val;
}

int Term::getNVal() {
    return this->nval;
}

// product constructor
Product::Product(Term left, std::vector<Term> right, void (*action)(Term& leftTerm, std::stack<Term>& s)) {
    this->left = left; 
    this->right = right;
    this->action = action;
} // Product

Product::Product(const Product& other) {
    this->left = other.left;
    this->right = other.right;
    this->action = other.action;
} // Product

Product& Product::operator=(Product other) {

    this->left = other.left;	
    this->right = other.right;
    this->action = other.action;
    return *this;

}

Term Product::getLeft(){
    return this->left;
} // getLeft

std::vector<Term> Product::getRight(){
    return this->right;
} // getRight


Action::Action(ActionType type, int value) {
    this->type = type;
    this->value = value;
}

Action::ActionType Action::getType() {
    return this->type;
}

int Action::getValue() {
    return this->value;
}


void replaceTerm(Term& leftTerm, std::stack<Term>& s) {
    leftTerm.setNVal(s.top().getNVal());	
    s.pop();
}

void ePran(Term& leftTerm, std::stack<Term>& s) {
    s.pop();
    leftTerm.setNVal(s.top().getNVal());	
    s.pop();
    s.pop();
}

void doOp(Term& leftTerm, std::stack<Term>& s) {
    int x = s.top().getNVal();
    s.pop();
    std::string op = s.top().getValue();
    s.pop();
    int y = s.top().getNVal();
    s.pop();
    int r;

    if (op == "+")
	r = y + x;
    else if (op == "-") 
	r = y - x;
    else if (op == "*")
	r = y * x;
    else if (op == "/")
	r = y / x;

    leftTerm.setNVal(r);	
}


Grammar::Grammar() {

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



    this->addProduct("E", "E + T", doOp);
    this->addProduct("E", "E - T", doOp);
    this->addProduct("E", "T", replaceTerm);
    this->addProduct("T", "T * F", doOp);
    this->addProduct("T", "T / F", doOp);
    this->addProduct("T", "F", replaceTerm);
    this->addProduct("F", "( E )", ePran);
    this->addProduct("F", "num", replaceTerm);


}

bool Grammar::findTerm(std::string str, std::vector<Term> terms){
    for(int i = 0; i < terms.size(); i++){
	if(!str.compare(terms[i].getValue())){
	   return true; 	
	} 
    }
    return false;

} // findTerm


void Grammar::addProduct(std::string left, std::string right, void (*action)(Term& leftTerm, std::stack<Term>& s)) {
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


    this->products.push_back(Product(productLeft, productRight, action));

} // addProduct

Product Grammar::getProduct(int i) {
    return this->products[i-1];
}


Action Grammar::getAction(int state, Token t) {
    std::string val = t.getValue();
    std::string type = t.getType();
    
    Action action;  

    switch(state) {
	case 0:
	    if (type == "num")
		s(5);
	    else if (val == "(")
		s(4);
	    else 
		ERROR;
	    break; 
	case 1:
	    if (val == "+")
		s(6);
	    else if (val == "-")
		s(7);

	    else if (type == "eos")
		ACCEPT;
	    else
		ERROR;

	    break;
	case 2:
	    if (val == "+" || val == "-")
		r(3);
	    else if (val == "*")
		s(8);
	    else if (val == "/")
		s(9);
	    else if (val == ")" || type == "eos")
		r(3);
	    else 
		ERROR;

	    break;
	case 3:

	    if (val == "+" || val == "-" ||
		val == "*" || val == "/" ||
		val == ")" || type == "eos")

		r(6);

	    else
		ERROR;

	    break;

	case 4:
	    if (type == "num")
		s(5);
	    else if (val == "(")
		s(4);
	    else
		ERROR;
	    break;	
	case 5:
	    if (val == "+" || val == "-" ||
		val == "*" || val == "/" ||
		val == ")" || type == "eos")

		r(8);
	    else
		ERROR;

	    break;
	    
	case 6:
	case 7:
	case 8:
	case 9:
	    if (type == "num")
		s(5);
	    else if (val == "(")
		s(4);
	    else 
		ERROR;

	    break;	

	
	case 10:
	    if (val == "+")
		s(6);
	    else if (val == "-")
		s(7);

	    else if (val == ")")
		s(15);
	    else 
		ERROR;

	    break;

	case 11:
	    if (val == "+" || val == "-")
		r(1);

	    else if (val == "*")
		s(8);
	    else if (val == "/")
		s(9);
	    else if (val == ")" || type == "eos")
		r(1);
	    else 
		ERROR;

	    break;
	case 12:
	    if (val == "+" || val == "-")
		r(2);

	    else if (val == "*")
		s(8);
	    else if (val == "/")
		s(9);
	    else if (val == ")" || type == "eos")
		r(2);
	    else 
		ERROR;

	    break;

	case 13:
	    if (val == "+" || val == "-")
		r(4);

	    else if (val == "*")
		r(4);
	    else if (val == "/")
		r(4);
	    else if (val == ")" || type == "eos")
		r(4);
	    else 
		ERROR;

	    break;
    
	case 14:
	    if (val == "+" || val == "-")
		r(5);

	    else if (val == "*")
		r(5);
	    else if (val == "/")
		r(5);
	    else if (val == ")" || type == "eos")
		r(5);
	    else 
		ERROR;

	    break;

	case 15:
	    if (val == "+" || val == "-")
		r(7);

	    else if (val == "*")
		r(7);
	    else if (val == "/")
		r(7);
	    else if (val == ")" || type == "eos")
		r(7);
	    else 
		ERROR;

	    break;
	
	default:
	    ERROR;
	    break;

    } // switch 

    return action;
} // getAction



Action Grammar::getAction(int state, Term t) {
    std::string val = t.getValue();
    
    Action action;

    switch(state) {
	case 0:
	    if (val == "E")
		g(1);
	    else if (val == "T")
		g(2);
	    else if (val == "F")
		g(3);
	    else
		ERROR;
	    break;

	case 4:
	    if (val == "E")
		g(10);
	    else if (val == "T")
		g(2);
	    else if (val == "F")
		g(3);
	    else
		ERROR;
	    break;
	case 6:
	    if (val == "T")
		g(11);
	    else if (val == "F")
		g(3);
	    else
		ERROR;
	    break;
	case 7:
	    if (val == "T")
		g(12);
	    else if (val == "F")
		g(3);
	    else
		ERROR;
	    break;

	case 8:
	    if (val == "F")
		g(13);
	    else
		ERROR;
	    break;

	case 9:
	    if (val == "F")
		g(14);
	    else
		ERROR;
	    break;
	
	default:
	    ERROR;
	    break;
	    
    } // switch

    return action;
}


