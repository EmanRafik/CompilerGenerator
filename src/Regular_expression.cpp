#include "Regular_expression.h"
#include"NFA.h"
#include"Regular_definition.h"
#include"NFA_constructor.h"
#include"Token.h"
#include"State.h"
#include<iostream>
#include<string>
#include<vector>

using namespace std;

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

void Regular_expression::setPriority(int priority)
{
    this->priority = priority;
}

string Regular_expression::getName()
{
    return this->name;
}

string Regular_expression::getValue()
{
   return this->value;
}

int Regular_expression::getPriority()
{
    return this->priority;
}

/*NFA Regular_expression::getNFA()
{
    NFA_constructor *constructor = new NFA_constructor();
    NFA nfa = constructor->constructNFA(this->value);
    Token *token = new Token();
    token->setToken_class(name);
    token->setPriority(this->priority);
    State *accept = nfa.getAcceptState();
    nfa.addAcceptStateToList(accept, *token);
    return nfa;
}
*/
