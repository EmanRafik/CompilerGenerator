//
// Created by DELL on 14-Apr-20.
//

#include <iostream>
#include <sstream>
#include "Production.h"
#include "Parser_table.h"

const int print_item_width = 13;

Parser_table::Parser_table() {
}

Parser_table::Parser_table(map <string, int> non_terminals, map <string, int> terminals, map<int, vector<Production>> productions, map<int, set<string>> first_sets, map<int, set<string>> follow_sets) {
    this->non_terminals = non_terminals;
    this->terminals = terminals;
    this->productions = productions;
    this-> first_sets = first_sets;
    this->follow_sets = follow_sets;

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
    if (terminals.size() == 0 || non_terminals.size() == 0)
        return;
    string terminals_sorted[terminals.size()];

    map<string, int>::iterator it;
    for ( it = terminals.begin(); it != terminals.end(); it++ ) {
        terminals_sorted[it->second] = it->first;
    }
    cout << printHelper(" ", print_item_width);
    for (int i = 0; i < terminals.size(); i++) {
        cout << printHelper(terminals_sorted[i], print_item_width);
    }
    cout << endl;

    string production = "";
    for (int i = 0; i < non_terminals.size(); i++) {
        cout << printHelper(table[i][0].getFrom(), print_item_width-1) << " : ";
        for (int j = 0; j < terminals.size(); j++) {
            production = "";
            for (int k = 0; k < table[i][j].getTo().size(); k++) {
                production += table[i][j].getTo().at(k).getSymbol();
            }
            cout << printHelper(production, print_item_width);
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

Parser_table Parser_table::build_table(){
    map<string,int>::iterator it = non_terminals.begin();
    while(it!=non_terminals.end()){
        int i = it->second;
        string s = it->first;
        set<string> follow = follow_sets[i];
        set<string> first = first_sets[i];
        vector<Production> pro = productions[i];
        set<string>::iterator follow_it = follow.begin();
        Symbol *synch = new Symbol("synch", true);
        Symbol *eps = new Symbol("epsilon", true);
        if(first.count("epsilon")){
            Production *p = new Production(s);
            p->addSymbol(*eps);
            while(follow_it!=follow.end()){
                table[i][terminals[*follow_it]] = *p;
                //cout << s << " " << *follow_it << " = " << p->getTo().at(0).getSymbol()<<endl;
                follow_it++;
            }
        }else{
            Production *p = new Production(s);
            p->addSymbol(*synch);
            while(follow_it!=follow.end()){
                table[i][terminals[*follow_it]] = *p;
                //cout << s << " " << *follow_it << " = " << p->getTo().at(0).getSymbol()<<endl;
                follow_it++;
            }
        }
        for(int j=0;j<pro.size();j++){
            Production p = pro[j];
            set<string> f = p.get_first();
            set<string>::iterator first_it = f.begin();
            while(first_it!=f.end()){
                table[i][terminals[*first_it]] = p;
                //cout << s << " " << *first_it << " = " << p.getTo().at(0).getSymbol()<<endl;
                first_it++;
            }
        }
        it++;
    }
    /*map<string, int>::iterator iter;
    for ( iter = terminals.begin(); iter != terminals.end(); iter++ ) {
        cout<< iter->first<< "   ";
    }*/
    return *this;
}
