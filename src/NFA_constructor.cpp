#include "NFA_constructor.h"
#include"NFA.h"
#include<string>
#include<vector>
#include<map>
#include<iostream>
#include"Regular_definition.h"

using namespace std;

NFA_constructor::NFA_constructor()
{
    //ctor
}

NFA_constructor::~NFA_constructor()
{
    //dtor
}


void NFA_constructor::setRegular_definitions(vector<Regular_definition> regular_definitions)
{
    this->regular_definitions = regular_definitions;
}


NFA NFA_constructor::constructNFA(string expression)
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
                NFA nfa1 = constructNFA(expression.substr(0, i-1));
                NFA nfa2 = constructNFA(expression.substr(i+1, expression.length()-i));
                return oring(nfa1, nfa2);
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        char c = expression.at(i);
        if (c == ' ')
        {
            NFA nfa1 = constructNFA(expression.substr(0, i-1));
            NFA nfa2 = constructNFA(expression.substr(i+1, expression.length()-i));
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

NFA NFA_constructor::kleene_closure(NFA original_nfa)
{

}

NFA NFA_constructor::positive_closure(NFA original_nfa)
{

}

NFA NFA_constructor::oring(NFA original1, NFA original2)
{

}

NFA NFA_constructor::concatinating(NFA original1, NFA original2)
{

}

NFA NFA_constructor::termNFA(string term)
{
    size_t f = term.find("(");
    if (f == std::string::npos)
        //handleBrackets(term);
    vector<map<char, vector<int>>> table;
    for (int i = 0; i < term.length(); i++)
    {
        if (term.at(i) != '\\')
        {
            vector<int> v;
            v.push_back(i+1);
            map<char, vector<int>> m;
            m.insert(pair<char, vector<int>>(term.at(i), v));
            //table.push_back(m);
        }
    }
}

string NFA_constructor::trim(string s)
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
