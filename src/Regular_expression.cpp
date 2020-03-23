#include "Regular_expression.h"
#include"NFA.h"
#include"Regular_definition.h"
#include<regex>
#include<iostream>
#include<string>
#include<vector>
#include<map>
using namespace std;

//static const int kleene_closure = 0;
//static const int positive_closure = 1;
//static const int concatenation = 2;
//static const int dor = 3;

Regular_expression::Regular_expression()
{
    //ctor
}

Regular_expression::~Regular_expression()
{
    //dtor
}

void Regular_expression::setName(string name)
{
    this->name = name;
}

void Regular_expression::setValue(string value)
{
    this->value = value;
}

void Regular_expression::setRegular_definitions(vector<Regular_definition> regular_definitions)
{
    this->regular_definitions = regular_definitions;
}

string Regular_expression::getName()
{
    return this->name;
}

bool Regular_expression::isDefinition()
{
    return this->definition;
}

bool Regular_expression::isSymbol()
{
    return this->symbol;
}

int Regular_expression::getRelation()
{
    return this->relation_with_next;
}

int Regular_expression::getClosure()
{
    return this->closure;
}

void Regular_expression::setDefinition(bool definition)
{
    this->definition = definition;
}

void Regular_expression::setSymbol(bool symbol)
{
    this->symbol = symbol;
}

void Regular_expression::setRelation(int relation)
{
    this->relation_with_next = relation;
}

void Regular_expression::setClosure(int closure)
{
    this->closure = closure;
}

NFA Regular_expression::getNFA()
{
    //return constructNFA(this->value);
}



void Regular_expression::handleBrackets(string term)
{

}

string Regular_expression::trim(string s)
{
    while (s.at(0) == ' ')
    {
        s = s.substr(1);
    }
    while (s.at(s.length()-1)== ' ')
    {
        s = s.substr(0, s.length()-1);
    }
    return s;
}
