//
// Created by DELL on 14-Apr-20.
//

#include <iostream>
#include "Production.h"
#include "Parser_table.h"

Parser_table::Parser_table() {
}

Parser_table::Parser_table(map <string, int> non_terminals, map <string, int> terminals) {
    this->terminals = terminals;
    this->non_terminals = non_terminals;
    //initialize table 2D array with -2s
    this->table = new Production *[non_terminals.size()];
    for (int i = 0; i < non_terminals.size(); i++)
        this->table[i] = new Production [terminals.size()];


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
    for (int i = 0; i < non_terminals.size(); i++) {
        cout << table[i][0].getFrom() << " : ";
        for (int j = 0; j < terminals.size(); j++) {
            cout << table[i][j].getTo().at(0).getSymbol() << " ";
        }
        cout << endl;
    }
}