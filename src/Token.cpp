#include "Token.h"
#include<string>

using namespace std;

Token::Token()
{
    //ctor
}

Token::~Token()
{
    //dtor
}

void Token::setToken_class(string token_class)
{
    this->token_class = token_class;
}

void Token::setValue(string value)
{
    this->value = value;
}

string Token::getToken_class()
{
    return this->token_class;
}

string Token::getValue()
{
    return this->value;
}
