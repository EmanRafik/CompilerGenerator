#include "Phase1_LexicalAnalyzer/Lexical_analyzer_generator.h"
#include <map>
#include "Phase1_LexicalAnalyzer/NFA.h"
#include "Phase1_LexicalAnalyzer/DFA.h"
#include"Phase1_LexicalAnalyzer/NFA_constructor.h"
#include <vector>
#include <fstream>
#include<iostream>
#include <bits/stdc++.h>

using namespace std;

Lexical_analyzer_generator::Lexical_analyzer_generator()
{
    //ctor
}

Lexical_analyzer_generator::~Lexical_analyzer_generator()
{
    //dtor
}

DFA* Lexical_analyzer_generator::get_minimal_dfa()
{
    return this->minimal_dfa;
}

void Lexical_analyzer_generator::generate_lexical_analyzer()
{
    vector<NFA> NFAlist;
    NFA_constructor *constructor = new NFA_constructor();
    constructor->setRegular_definitions(regular_definitions);
    ///construct NFA for each keyword
    for (unsigned int i = 0; i < keywords.size(); i++)
    {
        NFA nfa = constructor->termNFA(keywords[i].first);
        Token *token = new Token();
        token->setToken_class("keyword");
        token->setValue(keywords[i].first);
        token->setPriority(keywords[i].second);
        int accept = nfa.getAcceptState();
        nfa.addAcceptStateToList(accept, *token);
        NFAlist.push_back(nfa);
    }
    ///construct NFA for each punctuation character
    for (unsigned int i = 0; i < punctuations.size(); i++)
    {
        string punc = punctuations[i].first;
        vector<char> vec;
        vec.push_back(punc.at(0));
        NFA nfa = constructor->signleCharNFA(vec);
        Token *token = new Token();
        token->setToken_class("punctuation");
        token->setValue(punc);
        token->setPriority(punctuations[i].second);
        int accept = nfa.getAcceptState();
        nfa.addAcceptStateToList(accept, *token);
        NFAlist.push_back(nfa);
    }
    ///get constructed NFA of each regular expression
    for (unsigned int i = 0; i < regular_expressions.size(); i++)
    {
        NFA nfa = regular_expressions[i].getNFA(regular_definitions);
        NFAlist.push_back(nfa);
    }
    ///combine all NFA
    NFA combined = constructor->oringList(NFAlist, true);
    ///convert NFA to DFA
    DFA* dfa = combined.convertToDFA();
    ///minimize DFA
    minimal_dfa = dfa->minimize();
    minimal_dfa->print_dfa();
}

void Lexical_analyzer_generator::read_lexical_rules(string file_name)
{
    ///read rules line by line from lexical rules file, specify line class and set priority
    fstream file;
    file.open(file_name, ios::in);
    if (file.is_open())
    {
        int priority = 1;
        string line;
        while (getline(file, line))
        {
            classify_line(line, priority);
            priority++;
        }
    }
}

void Lexical_analyzer_generator::classify_line(string line, int priority)
{
    line = trim(line);
    ///keywords
    if (line.at(0) == '{')
    {
        line = line.substr(1, line.length()-2);
        line = trim(line);
        istringstream ss(line);
        while (ss)
        {
            string keyword;
            ss >> keyword;
            if (keyword != "")
            {
                pair<string,int> p(keyword, priority);
                keywords.push_back(p);
            }
        }
        return;
    }
    ///Punctuations
    if (line.at(0) == '[')
    {
        line = line.substr(1, line.length()-2);
        line = trim(line);
        istringstream ss(line);
        while (ss)
        {
            string punc;
            ss >> punc;
            if (punc != "")
            {
                if (punc.length() > 1 && punc.at(0)=='\\')
                {
                    punc = punc.substr(1);
                }
                pair<string,int> p(punc, priority);
                punctuations.push_back(p);
            }
        }
        return;
    }
    ///Regular definitions
    size_t f = line.find("=");
    if (f != std::string::npos)
    {
        if (line.at(f-1) != '\\')
        {
            Regular_definition *rd = new Regular_definition();
            string name = trim(line.substr(0,f));
            string value = trim(line.substr(f+1));
            rd->setName(name);
            rd->setValue(value);
            regular_definitions.push_back(*rd);
            return;
        }
    }
    ///Regular expressions
    f = line.find(":");
    if (f != std::string::npos)
    {
        if (line.at(f-1) != '\\')
        {
            Regular_expression *re = new Regular_expression();
            string name = trim(line.substr(0,f));
            string value = trim(line.substr(f+1));
            re->setName(name);
            re->setValue(value);
            re->setPriority(priority);
            regular_expressions.push_back(*re);
            return;
        }
    }
}

string Lexical_analyzer_generator::trim(string s)
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
