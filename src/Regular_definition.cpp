#include "Regular_definition.h"
#include<string>
#include"NFA.h"
#include"NFA_constructor.h"

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

NFA Regular_definition::getNFA(vector<Regular_definition> regular_definitions)
{
    NFA_constructor *constructor = new NFA_constructor();
    constructor->setRegular_definitions(regular_definitions);
    NFA nfa = constructor->constructNFA(this->value);
    return nfa;
}
