#include "Lexical_analyzer_generator.h"
#include <map>
#include "NFA.h"
#include "DFA.h"
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

vector<NFA> Lexical_analyzer_generator:: getNFAList(){
    return NFAlist;
}

void Lexical_analyzer_generator:: setNFAList(vector<NFA> list) {
    this->NFAlist = list;
}

DFA* Lexical_analyzer_generator::get_minimal_dfa()
{
    return this->minimal_dfa;
}

void Lexical_analyzer_generator::generate_lexical_analyzer()
{

}

void Lexical_analyzer_generator:: addNFA(NFA nfa){
    vector<NFA> list = getNFAList();
    list.push_back(nfa);
    setNFAList(list);
}

NFA Lexical_analyzer_generator::combineNFA(vector<NFA> list)
{

}

void Lexical_analyzer_generator::read_lexical_rules(string file_name)
{
    fstream file;
    file.open(file_name, ios::in);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            classify_line(line);
        }
    }
}

void Lexical_analyzer_generator::classify_line(string line)
{
    line = trim(line);
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
                keywords.push_back(keyword);
            }

        }
        return;
    }
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
                punctuations.push_back(punc);
            }
        }
        return;
    }
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
