#ifndef TOKEN_H
#define TOKEN_H

#include <string>


// represent a token <type, value>
class Token{
    public:
	Token(){};
	Token(std::string, std::string);
	Token(const Token&);

	Token& operator=(const Token&);


	std::string getType();
	std::string getValue();


    private:
	std::string type;
	std::string value; 

};


#endif // TOKEN_H
