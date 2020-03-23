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
    return constructNFA(this->value);
}

NFA Regular_expression::constructNFA(string expression)
{
    expression = trim(expression);
    int n = expression.length();
    if (expression.at(0) == '(')
    {
        if (expression.at(n-1) == ')')
        {
            expression = expression.substr(1, n-2);
            return constructNFA(expression);
        }
        else if (expression.at(n-2) == ')')
        {
            NFA nfa = constructNFA(expression.substr(1,n-3));
            if (expression.at(n-1) == '*')
            {
                return kleene_closure(nfa);
            }
            else if (expression.at(n-1) == '+')
            {
                return positive_closure(nfa);
            }
        }
    }
    int open = 0;
    for (int i = 0; i < n; i++)
    {
        char c = expression.at(i);
        if (c == '(')
        {
            open++;
        }
        else if (c == ')')
        {
            open--;
        }
        else if (c == '|')
        {
            if (open == 0)
            {
                NFA nfa1 = constructNFA(value.substr(0, i-1));
                NFA nfa2 = constructNFA(value.substr(i+1, value.length()-i));
                return oring(nfa1, nfa2);
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        char c = expression.at(i);
        if (c == ' ')
        {
            NFA nfa1 = constructNFA(value.substr(0, i-1));
            NFA nfa2 = constructNFA(value.substr(i+1, value.length()-i));
            return concatinating(nfa1, nfa2);
        }
    }
    int closure = -1;
    if (expression.at(n-1) == '*')
    {
        closure = 0;
        expression = expression.substr(0,n-1);
    }
    else if (expression.at(n-1) == '+')
    {
        closure = 1;
        expression = expression.substr(0,n-1);
    }
    bool found = false;
    NFA nfa;
    for (int i = 0; i < regular_definitions.size(); i++)
    {
        if (regular_definitions[i].getName() == expression)
        {
            nfa = regular_definitions[i].getNFA();
            found = true;
            break;
        }
    }
    if (!found)
    {
        nfa = termNFA(expression);
    }
    if (closure == 0)
    {
        return kleene_closure(nfa);
    }
    else if (closure == 1)
    {
        return positive_closure(nfa);
    }
    else
    {
        return nfa;
    }
}

NFA Regular_expression::kleene_closure(NFA original_nfa)
{

}

NFA Regular_expression::positive_closure(NFA original_nfa)
{

}

NFA Regular_expression::oring(NFA original1, NFA original2)
{

}

NFA Regular_expression::concatinating(NFA original1, NFA original2)
{

}

NFA Regular_expression::termNFA(string term)
{
    size_t f = term.find("(");
    if (f == std::string::npos)
        handleBrackets(term);
    vector<map<char, vector<int>>> table;
    for (int i = 0; i < term.length(); i++)
    {
        if (term.at(i) != '\\')
        {
            vector<int> v;
            v.push_back(i+1);
            map<char, vector<int>> m;
            m.insert(pair<char, vector<int>>(term.at(i), v));
            table.push_back(m);
        }
    }
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
