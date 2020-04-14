#include "LexicalAnalyzer/Regular_expression.h"
#include"LexicalAnalyzer/NFA.h"
#include"LexicalAnalyzer/Regular_definition.h"
#include"LexicalAnalyzer/NFA_constructor.h"
#include"LexicalAnalyzer/Token.h"
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

NFA Regular_expression::getNFA(vector<Regular_definition> regular_definitions)
{
    NFA_constructor *constructor = new NFA_constructor();
    constructor->setRegular_definitions(regular_definitions);
    NFA nfa = constructor->constructNFA(value);
    Token *token = new Token();
    token->setToken_class(name);
    token->setPriority(priority);
    int accept = nfa.getAcceptState();
    nfa.addAcceptStateToList(accept, *token);
    return nfa;
}

