#include "Regular_expression.h"
#include"NFA.h"
#include<regex>
#include<iostream>
#include<string>

using namespace std;

final int kleene_closure = 0;
final int positive_closure = 1;
final int concatenation = 2;
final int or = 3;

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

NFA Regular_expression::constructNFA()
{
    size_t n = strlen(value);
    string term = "";
    bool is_operator = false;
    for (int i = 0; i < n; i++)
    {
        char c = value.at(i);
        if (c == '(')
        {
            if (term != "")
            {
                string expression1 = value.substr(0, i-1);
            }
            int counter = 0, j = i+1;
            while (j < n)
            {
                if (value.at(j) == ')')
                {
                    if (counter != 0)
                    {
                        counter--;
                    }
                    else
                    {
                        string expression = value.substr(i+1, j-i-1);
                        Regular_expression e = new Regular_expression();
                        e.setValue(expression);
                        e.setSymbol(false);
                        e.setDefinition(false);
                        if (value.at(j+1) == '*')
                        {
                            e.setClosure(kleene_closure);
                            i = j+2;
                        }
                        else if (value.at(j+1) == '+')
                        {
                            e.setClosure(positive_closure);
                            i = j+2;
                        }
                        else
                        {
                            e.setClosure(-1);
                            i = j+1;
                        }
                        NFA n = e.constructNFA();
                        is_operator = true;
                    }
                }
                else if (value.at(j) == '(')
                {
                    counter++;
                }
            }
            is_operator = false;
        }
        else if (c == '|')
        {
            string expression1 = value.substr(0, i-1);
            string expression2 = value.substr(i+1, strlen(vlaue)-i)
            is_operator = true;
        }
        else if (c == '*')
        {
            is_operator = true;
        }
        else if (c == '+')
        {
            is_operator = true;
        }
        else if (c == '\\')
        {
            term += value.at(i+1);
            i++;
            is_operator = false;
        }
        else if (c == ' ')
        {
            if (!is_operator)
            {
                bool found = fasle;
                for (int i = 0; i < regular_definitions.size(); i++)
                {
                    if (term == regular_definitions[i])
                    {

                        found = true;
                    }
                }
                if (!found)
                {

                }
                term = "";
            }
        }
        else
        {
            term += c;
            is_operator = false;
        }
    }
    NFA nfa = new NFA();

}
