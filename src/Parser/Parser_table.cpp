//
// Created by DELL on 14-Apr-20.
//

#include <iostream>
#include <sstream>
#include "Production.h"
#include "Parser_table.h"

Parser_table::Parser_table() {
}

Parser_table::Parser_table(map <string, int> non_terminals, map<int, set<string>> first_sets, map<int, set<string>> follow_sets) {
    this->non_terminals = non_terminals;

    this->table = new Production *[non_terminals.size()];
    for (int i = 0; i < non_terminals.size(); i++)
        this->table[i] = new Production [terminals.size()];

    //initialize table 2D array with productions from each non-terminal to error terminal
    map<string, int>::iterator it;
    Production *p;
    Symbol *s;
    for ( it = non_terminals.begin(); it != non_terminals.end(); it++ ) {
        for (int j = 0; j < terminals.size(); j++) {
            p = new Production(it->first);
            s = new Symbol("error", true);
            p->addSymbol(*s);
            table[it->second][j] = *p;
        }
    }
}

Production **Parser_table::getTable() {
    return table;
}

std::map<string, int> Parser_table::getTerminals() {
    return terminals;
}

std::map<string, int> Parser_table::getNonTerminals() {
    return non_terminals;
}

void Parser_table::setTerminals(map<string, int> terminals) {
    Parser_table::terminals = terminals;
}

void Parser_table::setNonTerminals(map<string, int> nonTerminals) {
    non_terminals = nonTerminals;
}

void Parser_table::printTable() {
    string terminals_sorted[terminals.size()];

    map<string, int>::iterator it;
    for ( it = terminals.begin(); it != terminals.end(); it++ ) {
        terminals_sorted[it->second] = it->first;
    }
    cout << printHelper(" ", 15);
    for (int i = 0; i < terminals.size(); i++) {
        cout << printHelper(terminals_sorted[i], 15);
    }
    cout << endl;

    string production = "";
    for (int i = 0; i < non_terminals.size(); i++) {
        cout << printHelper(table[i][0].getFrom(), 14) << " : ";
        for (int j = 0; j < terminals.size(); j++) {
            production = "";
            for (int k = 0; k < table[i][j].getTo().size(); k++) {
                production += table[i][j].getTo().at(k).getSymbol();
            }
            cout << printHelper(production, 15);
        }
        cout << endl;
    }
}

string Parser_table::printHelper(const string x, const int width) {
    stringstream ss;
    ss << fixed << right;
    ss.fill(' ');        // fill space around displayed #
    ss.width(width);     // set  width around displayed #
    ss << x;
    return ss.str();
}

void Parser_table::build_table(){

}
