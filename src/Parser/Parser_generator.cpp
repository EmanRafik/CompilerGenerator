//
// Created by DELL on 14-Apr-20.
//
#include "Phase2_Parser/Parser_generator.h"
#include <vector>
#include <string>
#include <map>
#include <set>
#include "Symbol.h"
#include "Production.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>

using namespace std;


const string epsilon = "epsilon";

Parser_generator::Parser_generator()
{

}

void Parser_generator::read_rules(string file_name)
{

}

void Parser_generator::generate_parser()
{

}

void Parser_generator::convert_grammar_to_LL1()
{

}
// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
void Parser_generator::read_cfg(string file_name){
    fstream file;
    file.open(file_name, ios::in);
    if (file.is_open())
    {
        string line;
        int i = 0;
        string lastNonTerminal = "";
        while (getline(file, line))
        {
           line = trim(line);
            cout<<line<<endl;
            string equalDelimiter = "=";
            int pos = 0;
            string lhs = "";
            //if this is a new production rule split it on the first '='
            if (line.length()!=0 && line[0] == '#' && (pos = line.find(equalDelimiter)) != std::string::npos) {
                lhs = line.substr(0, pos);
                std::cout << lhs << std::endl;
                line.erase(0, pos + equalDelimiter.length());
            }
            //if the previous was a new production rule then handle LHS and RHS
            if(lhs.length() != 0){
                string nonTerminal = handleLHS(lhs, i);
                lastNonTerminal = nonTerminal;
                i++;
                handleRHS(line , lastNonTerminal);
            }
            //the production rule is expanded and this is a part of the RHS
            else{
                handleRHS(line, lastNonTerminal);
            }
        }
    }
}
string Parser_generator::handleLHS(string s, int i){
    string nonTerminal = s.substr(1); //eliminate # character
    nonTerminal = trim(nonTerminal);
    non_terminals_map.insert(pair<string,int>(nonTerminal,i));
    Symbol *nonTerminalSymbol = new Symbol(nonTerminal, false); //leave it for now
    return nonTerminal;
}
void Parser_generator::handleRHS(string s, string from){
    string delimiter = "|";
    int pos = 0;
    string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            if(token.length() != 0){
                handleToken(token, from);
            }
            s.erase(0, pos + delimiter.length());
        }
        if(s.length() != 0){
            handleToken(s, from);
        }
}
void Parser_generator::handleToken(string s, string from){
        s = trim(s);
        string delimiter = " ";
        int pos = 0;
        string token;
        Production production;
        production.setFrom(from);
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        token = trim(token);
        Symbol symbol;
        if(token.length() > 2 && token[0] == '\'') { //a terminal will be inside single quotes
            int pos = token.length() - 1;
            token = token.substr(1, pos);
            terminals.insert(token);
            symbol.setSymbol(token);
            symbol.setIsTerminal(true);
            production.addSymbol(symbol);
        }
        else if(token == "\\L"){ //epsilon
            symbol.setSymbol(" ");
            symbol.setIsTerminal(true);
            production.addSymbol(symbol);
        }
        else{ //non terminal
            symbol.setSymbol(token);
            symbol.setIsTerminal(false);
            production.addSymbol(symbol);
        }
        s.erase(0, pos + delimiter.length());
    }
    token = trim(s);
    Symbol symbol;
    if(token.length() > 2 && token[0] == '\'') { //a terminal will be inside single quotes
        int pos = token.length() - 1;
        token = token.substr(1, pos);
        terminals.insert(token);
        symbol.setSymbol(token);
        symbol.setIsTerminal(true);
        production.addSymbol(symbol);
    }
    else if(token == "\\L"){ //epsilon
        symbol.setSymbol(" ");
        symbol.setIsTerminal(true);
        production.addSymbol(symbol);
    }
    else{ //non terminal
        symbol.setSymbol(token);
        symbol.setIsTerminal(false);
        production.addSymbol(symbol);
    }
    grammar.push_back(production);
};
void Parser_generator::compute_first_and_follow()
{
    int non_terminals_count = non_terminals_map.size();

    /**compute first**/
    bool computed[non_terminals_count];
    for (int i = 0; i < non_terminals_count; i++)
    {
        computed[i] = false;
    }
    map<int, vector<Production>>::iterator it = non_terminals.begin();
    while(it != non_terminals.end())
    {
        int non_terminal = it->first;
        if (!computed[non_terminal])
        {
            vector<Production> productions = it->second;
            non_terminal_first(non_terminal, productions, computed);
        }
        it++;
    }

    /**compute follow**/
    for (int i = 0; i < non_terminals_count; i++)
    {
        computed[i] = false;
    }
    map<string,int>::iterator it2 = non_terminals_map.begin();
    while (it2 != non_terminals_map.end())
    {
        string non_terminal = it2->first;
        int non_terminal_mapping = it2->second;
        if (!computed[non_terminal_mapping])
        {
            non_terminal_follow(non_terminal, non_terminal_mapping, computed);
        }
        it2++;
    }
}

set<string> Parser_generator::non_terminal_first(int non_terminal, vector<Production> productions, bool computed[])
{
    set<string> first;
    for (unsigned int i = 0; i < productions.size(); i++)
    {
        Production production = productions[i];
        Symbol first_symbol = production.getTo()[0];
        if (first_symbol.isTerminal())
        {
            first.insert(first_symbol.getSymbol());
        }
        else
        {
            vector<Symbol> to_vector = production.getTo();
            bool add_epsilon = true;
            for (unsigned int i = 0; i < to_vector.size(); i++)
            {
                Symbol symbol = to_vector[i];
                if (symbol.isTerminal())
                {
                    first.insert(symbol.getSymbol());
                    add_epsilon = false;
                    break;
                }
                map<string,int>::iterator it;
                it = non_terminals_map.find(symbol.getSymbol());
                if (it != non_terminals_map.end())
                {
                    int mapping = it->second;
                    if (computed[i])
                    {
                        map<int, set<string>>::iterator it2 = first_sets.find(mapping);
                        if (it2 != first_sets.end())
                        {
                            set<string> s = it2->second;
                            first.insert(s.begin(), s.end());
                            if (s.find(epsilon) == s.end())
                            {
                                add_epsilon = false;
                                break;
                            }
                        }
                    }
                    else
                    {
                        map<int, vector<Production>>::iterator it2 = non_terminals.find(mapping);
                        if (it2 != non_terminals.end())
                        {
                            vector<Production> p = it2->second;
                            set<string> s = non_terminal_first(mapping, p, computed);
                            first.insert(s.begin(), s.end());
                            if (s.find(epsilon) == s.end())
                            {
                                add_epsilon = false;
                                break;
                            }
                        }
                    }
                }
            }
            if (add_epsilon)
            {
                first.insert(epsilon);
            }
        }
    }
    first_sets.insert(pair<int, set<string>>(non_terminal, first));
    computed[non_terminal] = true;
    return first;
}

set<string> Parser_generator::non_terminal_follow(string non_terminal, int non_terminal_mapping, bool computed[])
{
    set<string> follow;
    if (non_terminal_mapping == 0)
    {
        follow.insert("$");
    }
    map<int, vector<Production>>::iterator it = non_terminals.begin();
    while (it != non_terminals.end())
    {
        vector<Production> productions = it->second;
        for (unsigned int i = 0; i < productions.size(); i++)
        {
            Production production = productions[i];
            vector<Symbol> symbols = production.getTo();
            for (unsigned int j = 0; j < symbols.size() - 1; j++)
            {
                if (symbols[j].getSymbol() == non_terminal)
                {
                    unsigned int k = j + 1;
                    while (k < symbols.size())
                    {
                        if (symbols[k].isTerminal())
                        {
                            follow.insert(symbols[k].getSymbol());
                            break;
                        }
                        map<string, int>::iterator i = non_terminals_map.find(symbols[k].getSymbol());
                        if (i != non_terminals_map.end())
                        {
                            int mapping = i->second;
                            map<int,set<string>>::iterator i2 = first_sets.find(mapping);
                            if (i2 != first_sets.end())
                            {
                                set<string> first = i2->second;
                                follow.insert(first.begin(), first.end());
                                set<string>::iterator follow_it = follow.find(epsilon);
                                if (follow_it != follow.end())
                                {
                                    follow.erase(follow_it);
                                    k++;
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            if (non_terminal_mapping != it->first)
            {
                for (unsigned int j = symbols.size() - 1; j >= 0; j--)
                {
                    Symbol symbol = symbols[j];
                    if (symbol.isTerminal())
                    {
                        break;
                    }
                    if (symbol.getSymbol() == non_terminal)
                    {
                        set<string> s;
                        if (computed[it->first])
                        {
                            map<int, set<string>>::iterator i2 = follow_sets.find(it->first);
                            if (i2 != follow_sets.end())
                            {
                                s = i2->second;
                            }
                        }
                        else
                        {
                            s = non_terminal_follow(production.getFrom(), it->first, computed);
                        }
                        follow.insert(s.begin(), s.end());
                        break;
                    }
                    map<string, int>::iterator i = non_terminals_map.find(symbol.getSymbol());
                    if (i != non_terminals_map.end())
                    {
                        int mapping = i->second;
                        map<int, set<string>>::iterator i2 = first_sets.find(mapping);
                        if (i2 != first_sets.end())
                        {
                            set<string> first = i2->second;
                            if (first.find(epsilon) == first.end())
                            {
                                break;
                            }
                        }
                    }
                }
            }
        }
        it++;
    }
    follow_sets.insert(pair<int,set<string>>(non_terminal_mapping, follow));
    computed[non_terminal_mapping] = true;
    return follow;
}

void Parser_generator::construct_parser_table()
{

}

