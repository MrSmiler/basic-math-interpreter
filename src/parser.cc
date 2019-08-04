#include "token.h"
#include "grammar.h"
#include "parser.h"
#include <iostream>

LRParser::LRParser(Grammar grammar) {
    this->grammar = grammar; 
}

int LRParser::getStatus() {
    return this->status;
}

// do the actual parsing
void LRParser::parse(Lexical lexer) {

    // parser status is without error
    this->status = 0; 

    // state of the parser
    int state = 0;

    // top symbole
    Term symbole;

    // current token from input
    Token c_token;
    // initialize stack with the zero state
    this->state_stack.push(state);
    this->symbole_stack.push(Term(Term::T, "eos"));

    Action::ActionType a_type;

    Action action = Action(Action::INIT);
    
    while (!this->status) {
	
	// current state of the state stack
	state = this->state_stack.top();

	// current symbole of the symbole stack
	symbole = this->symbole_stack.top();


	a_type = action.getType();

	if (a_type != Action::REDUCE) {

	    if (a_type == Action::SHIFT || a_type == Action::INIT) {
		c_token = lexer.nextToken();

		if (lexer.getStatus() == 1) {
		    this->status = 2;
		    break;
		}
	    }

	    action = grammar.getAction(state, c_token);
	}
	// action is reduce
	else {
	    action = grammar.getAction(state, symbole);
	}

	// action type 
	a_type = action.getType();
	
	if (a_type == Action::SHIFT) {

	    int s = action.getValue();
	    this->state_stack.push(s);
	    
	    if (c_token.getType() == "num") {
		Term nt = Term(Term::T, "num");
		nt.setNVal(c_token.getValue());
		this->symbole_stack.push(nt);
	    }
	    else {
		this->symbole_stack.push(Term(Term::T, c_token.getValue()));
	    }
	}
	else if (a_type == Action::REDUCE) {
	    // get rule in grammar	
	    Product p = grammar.getProduct(action.getValue());
	    Term leftTerm = p.getLeft(); 

	    // perform the product action
	    p.action(leftTerm, this->symbole_stack);

	    for(int i = 0 ; i < p.getRight().size(); i++) {
		//this->symbole_stack.pop(); 
		this->state_stack.pop();
	    }

	    this->symbole_stack.push(leftTerm);
	}
	else if (a_type == Action::GOTO) {
	    this->state_stack.push(action.getValue());
	}
	else if (a_type == Action::ERROR) {
	    this->status = 1;
	    break;
	} 
	else if(a_type == Action::ACCEPT){
	    this->mathResult = this->symbole_stack.top().getNVal();
	    
	    while(!this->symbole_stack.empty())
		this->symbole_stack.pop();

	    while(!this->state_stack.empty())
		this->state_stack.pop();

	    break;
	}

    } // while

} // parse

