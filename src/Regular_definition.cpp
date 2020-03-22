#include "Regular_definition.h"

using namespace std;

Regular_definition::Regular_definition()
{
    //ctor
}

Regular_definition::~Regular_definition()
{
    //dtor
}

void Regular_definition::setName(string name)
{
    this->name = name;
}

void Regular_definition::setValue(string value)
{
    this->value = value;
}

string Regular_definition::getName()
{
    return this->name;
}

string Regular_definition::getValue()
{
    return this->value;
}

NFA Regular_definition::constructNFA()
{
    NFA nfa = new NFA();

    return nfa;
}
