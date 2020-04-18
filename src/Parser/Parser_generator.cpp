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

Parser_generator::Parser_generator() {

}

void Parser_generator::read_rules(string file_name) {

}

void Parser_generator::generate_parser() {

}

void Parser_generator::convert_grammar_to_LL1() {
    performLeftRecursion();
    for(int i = 0; i<grammar.size(); i++){
        string from = grammar[i].getFrom();
        int index = non_terminals_map.at(from);
        vector<Production> vec;
        if(non_terminals.count(index)){
            vector<Production> vec = non_terminals.at(index);
        }
        vec.push_back(grammar[i]);
        non_terminals.insert(pair<int,vector<Production>>(index,vec));
    }
    performLeftFactoring();
}

void Parser_generator::performLeftFactoring(){
    for(int i = 0; i < non_terminals.size(); i++) {

    }

}
void Parser_generator::performLeftRecursion(){
    set<string> updated;
    set<string> epsilonSet;
    for (int i = 0; i < grammar.size(); i++) {
        Symbol symbol;
        symbol.setSymbol(grammar[i].getFrom() + "~");
        symbol.setIsTerminal(false);
        string firstTo = grammar[i].getTo()[0].getSymbol();
        if (grammar[i].getFrom() == firstTo) {
            leftRecursion(updated, epsilonSet, symbol, i);
            for (int j = 0; j < grammar.size(); j++) {
                if (updated.count(grammar[j].getFrom())) {
                    Symbol symbol;
                    symbol.setSymbol(grammar[j].getFrom() + "~");
                    symbol.setIsTerminal(false);
                    if (grammar[j].getTo()[0].getSymbol() != " " &&
                        grammar[j].getTo()[grammar[j].getTo().size() - 1].getSymbol() != symbol.getSymbol()) {
                        grammar[j].addSymbol(symbol);
                    }
                }
            }
            i--;
        } else if (!grammar[i].getTo()[0].isTerminal()) {
            bool nonTerminalreplaced = false;
            vector<Symbol> clone = grammar[i].getTo();
            string from = grammar[i].getFrom();
            clone.erase(clone.begin());
            for (int j = 0; j < i; j++) {
                if (grammar[j].getFrom() == firstTo) {
                    if (!nonTerminalreplaced) {
                        nonTerminalreplaced = true;
                        grammar.erase(grammar.begin() + i);
                        i++;
                    }
                    vector<Symbol> newVector = grammar[j].getTo();
                    for (int k = 0; k < clone.size(); k++) {
                        newVector.push_back(clone[k]);
                    }
                    Production p;
                    p.setFrom(from);
                    p.setTo(newVector);
                    grammar.insert(grammar.begin() + i, p);
                    if (p.getFrom() == p.getTo()[0].getSymbol()) {
                        leftRecursion(updated, epsilonSet, symbol, i);
                    }
                    for (int k = 0; k < grammar.size(); k++) {
                        if (updated.count(grammar[k].getFrom())) {
                            Symbol symbol;
                            symbol.setSymbol(grammar[k].getFrom() + "~");
                            symbol.setIsTerminal(false);
                            if (grammar[k].getTo()[0].getSymbol() != " " &&
                                grammar[k].getTo()[grammar[k].getTo().size() - 1].getSymbol() != symbol.getSymbol()) {
                                grammar[k].addSymbol(symbol);
                            }
                        }
                    }
                    i--;
                }
            }
        }
    }
    for (int i = 0; i < grammar.size(); i++) {
        if (epsilonSet.count(grammar[i].getFrom())) {
            epsilonSet.erase(grammar[i].getFrom());
            Symbol symbol;
            symbol.setSymbol(" ");
            symbol.setIsTerminal(true);
            Production p;
            p.setFrom(grammar[i].getFrom());
            p.addSymbol(symbol);
            grammar.push_back(p);
        }
    }
}

void Parser_generator::leftRecursion(set<string> &updated, set<string> &epsilonSet, Symbol symbol, int i) {
    Production p;
    p.setFrom(symbol.getSymbol());
    vector<Symbol> vec = grammar[i].getTo();
    vec.erase(vec.begin());
    if(vec[vec.size()-1].getSymbol() != symbol.getSymbol()){
        vec.push_back(symbol);
    }
    p.setTo(vec);
    grammar.push_back(p);
    updated.insert(grammar[i].getFrom());
    epsilonSet.insert(symbol.getSymbol());
    int index = non_terminals_map.size();
    if(!non_terminals_map.count(symbol.getSymbol())){
        non_terminals_map.insert(pair<string, int>(symbol.getSymbol(),index));
    }
    grammar.erase(grammar.begin() + i);
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

void Parser_generator::read_cfg(string file_name) {
    fstream file;
    file.open(file_name, ios::in);
    if (file.is_open()) {
        string line;
        string lastNonTerminal = "";
        while (getline(file, line)) {
            line = trim(line);
            cout << line << endl;
            string equalDelimiter = "=";
            int pos = 0;
            string lhs = "";
            //if this is a new production rule split it on the first '='
            if (line.length() != 0 && line[0] == '#' && (pos = line.find(equalDelimiter)) != std::string::npos) {
                lhs = line.substr(0, pos);
                std::cout << lhs << std::endl;
                line.erase(0, pos + equalDelimiter.length());
            }
            //if the previous was a new production rule then handle LHS and RHS
            if (lhs.length() != 0) {
                string nonTerminal = handleLHS(lhs);
                lastNonTerminal = nonTerminal;
                handleRHS(line, lastNonTerminal);
            }
                //the production rule is expanded and this is a part of the RHS
            else {
                handleRHS(line, lastNonTerminal);
            }
        }
    }
}

string Parser_generator::handleLHS(string s) {
    string nonTerminal = s.substr(1); //eliminate # character
    nonTerminal = trim(nonTerminal);
    int i =non_terminals_map.size();
    non_terminals_map.insert(pair<string, int>(nonTerminal, i));
    Symbol *nonTerminalSymbol = new Symbol(nonTerminal, false); //leave it for now
    return nonTerminal;
}

void Parser_generator::handleRHS(string s, string from) {
    string delimiter = "|";
    int pos = 0;
    string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        if (token.length() != 0) {
            handleToken(token, from);
        }
        s.erase(0, pos + delimiter.length());
    }
    if (s.length() != 0) {
        handleToken(s, from);
    }
}

void Parser_generator::handleToken(string s, string from) {
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
        if (token.length() > 2 && token[0] == '\'') { //a terminal will be inside single quotes
            int pos = token.length() - 1;
            token = token.substr(1, pos);
            terminals.insert(token);
            symbol.setSymbol(token);
            symbol.setIsTerminal(true);
            production.addSymbol(symbol);
        } else if (token == "\\L") { //epsilon
            symbol.setSymbol(" ");
            symbol.setIsTerminal(true);
            production.addSymbol(symbol);
        } else { //non terminal
            symbol.setSymbol(token);
            symbol.setIsTerminal(false);
            production.addSymbol(symbol);
        }
        s.erase(0, pos + delimiter.length());
    }
    token = trim(s);
    Symbol symbol;
    if (token.length() > 2 && token[0] == '\'') { //a terminal will be inside single quotes
        int pos = token.length() - 1;
        token = token.substr(1, pos);
        terminals.insert(token);
        symbol.setSymbol(token);
        symbol.setIsTerminal(true);
        production.addSymbol(symbol);
    } else if (token == "\\L") { //epsilon
        symbol.setSymbol(" ");
        symbol.setIsTerminal(true);
        production.addSymbol(symbol);
    } else { //non terminal
        symbol.setSymbol(token);
        symbol.setIsTerminal(false);
        production.addSymbol(symbol);
    }
    if (!recursionMap.count(from)) {
        vector<Production> pVector;
        pVector.push_back(production);
        recursionMap.insert(pair<string, vector<Production>>(from, pVector));
    } else {
        vector<Production> pVector = recursionMap.at(from);
        pVector.push_back(production);
        recursionMap.insert(pair<string, vector<Production>>(from, pVector));
    }
    grammar.push_back(production);
};

void Parser_generator::compute_first_and_follow() {
    int non_terminals_count = non_terminals_map.size();

    /**compute first**/
    bool computed[non_terminals_count];
    for (int i = 0; i < non_terminals_count; i++) {
        computed[i] = false;
    }
    map<int, vector<Production>>::iterator it = non_terminals.begin();
    while (it != non_terminals.end()) {
        int non_terminal = it->first;
        if (!computed[non_terminal]) {
            vector<Production> productions = it->second;
            non_terminal_first(non_terminal, productions, computed);
        }
        it++;
    }

    /**compute follow**/
    for (int i = 0; i < non_terminals_count; i++) {
        computed[i] = false;
    }
    map<string, int>::iterator it2 = non_terminals_map.begin();
    while (it2 != non_terminals_map.end()) {
        string non_terminal = it2->first;
        int non_terminal_mapping = it2->second;
        if (!computed[non_terminal_mapping]) {
            non_terminal_follow(non_terminal, non_terminal_mapping, computed);
        }
        it2++;
    }
}

set<string> Parser_generator::non_terminal_first(int non_terminal, vector<Production> productions, bool computed[]) {
    set<string> first;
    for (unsigned int i = 0; i < productions.size(); i++) {
        Production production = productions[i];
        Symbol first_symbol = production.getTo()[0];
        if (first_symbol.isTerminal()) {
            first.insert(first_symbol.getSymbol());
        } else {
            vector<Symbol> to_vector = production.getTo();
            bool add_epsilon = true;
            for (unsigned int i = 0; i < to_vector.size(); i++) {
                Symbol symbol = to_vector[i];
                if (symbol.isTerminal()) {
                    first.insert(symbol.getSymbol());
                    add_epsilon = false;
                    break;
                }
                map<string, int>::iterator it;
                it = non_terminals_map.find(symbol.getSymbol());
                if (it != non_terminals_map.end()) {
                    int mapping = it->second;
                    if (computed[i]) {
                        map<int, set<string>>::iterator it2 = first_sets.find(mapping);
                        if (it2 != first_sets.end()) {
                            set<string> s = it2->second;
                            first.insert(s.begin(), s.end());
                            if (s.find(epsilon) == s.end()) {
                                add_epsilon = false;
                                break;
                            }
                        }
                    } else {
                        map<int, vector<Production>>::iterator it2 = non_terminals.find(mapping);
                        if (it2 != non_terminals.end()) {
                            vector<Production> p = it2->second;
                            set<string> s = non_terminal_first(mapping, p, computed);
                            first.insert(s.begin(), s.end());
                            if (s.find(epsilon) == s.end()) {
                                add_epsilon = false;
                                break;
                            }
                        }
                    }
                }
            }
            if (add_epsilon) {
                first.insert(epsilon);
            }
        }
    }
    first_sets.insert(pair<int, set<string>>(non_terminal, first));
    computed[non_terminal] = true;
    return first;
}

set<string> Parser_generator::non_terminal_follow(string non_terminal, int non_terminal_mapping, bool computed[]) {
    set<string> follow;
    if (non_terminal_mapping == 0) {
        follow.insert("$");
    }
    map<int, vector<Production>>::iterator it = non_terminals.begin();
    while (it != non_terminals.end()) {
        vector<Production> productions = it->second;
        for (unsigned int i = 0; i < productions.size(); i++) {
            Production production = productions[i];
            vector<Symbol> symbols = production.getTo();
            for (unsigned int j = 0; j < symbols.size() - 1; j++) {
                if (symbols[j].getSymbol() == non_terminal) {
                    unsigned int k = j + 1;
                    while (k < symbols.size()) {
                        if (symbols[k].isTerminal()) {
                            follow.insert(symbols[k].getSymbol());
                            break;
                        }
                        map<string, int>::iterator i = non_terminals_map.find(symbols[k].getSymbol());
                        if (i != non_terminals_map.end()) {
                            int mapping = i->second;
                            map<int, set<string>>::iterator i2 = first_sets.find(mapping);
                            if (i2 != first_sets.end()) {
                                set<string> first = i2->second;
                                follow.insert(first.begin(), first.end());
                                set<string>::iterator follow_it = follow.find(epsilon);
                                if (follow_it != follow.end()) {
                                    follow.erase(follow_it);
                                    k++;
                                } else {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            if (non_terminal_mapping != it->first) {
                for (unsigned int j = symbols.size() - 1; j >= 0; j--) {
                    Symbol symbol = symbols[j];
                    if (symbol.isTerminal()) {
                        break;
                    }
                    if (symbol.getSymbol() == non_terminal) {
                        set<string> s;
                        if (computed[it->first]) {
                            map<int, set<string>>::iterator i2 = follow_sets.find(it->first);
                            if (i2 != follow_sets.end()) {
                                s = i2->second;
                            }
                        } else {
                            s = non_terminal_follow(production.getFrom(), it->first, computed);
                        }
                        follow.insert(s.begin(), s.end());
                        break;
                    }
                    map<string, int>::iterator i = non_terminals_map.find(symbol.getSymbol());
                    if (i != non_terminals_map.end()) {
                        int mapping = i->second;
                        map<int, set<string>>::iterator i2 = first_sets.find(mapping);
                        if (i2 != first_sets.end()) {
                            set<string> first = i2->second;
                            if (first.find(epsilon) == first.end()) {
                                break;
                            }
                        }
                    }
                }
            }
        }
        it++;
    }
    follow_sets.insert(pair<int, set<string>>(non_terminal_mapping, follow));
    computed[non_terminal_mapping] = true;
    return follow;
}

void Parser_generator::construct_parser_table() {

}

