//
// Created by DELL on 14-Apr-20.
//

#ifndef COMPILERGENERATOR_PRODUCTION_H
#define COMPILERGENERATOR_PRODUCTION_H

#include <string>
#include <vector>
#include<set>
#include "Phase2_Parser/Symbol.h"

using namespace std;

class Production {
public:
    Production();
    Production(string from);
    void addSymbol (Symbol s);
    string getFrom();
    vector<Symbol> getTo() ;
    set<string> get_first();
    void add_first(set<string> s);
    void setTo(const vector<Symbol> &to);
    void setFrom(const string &from);

private:
    string from;
    vector<Symbol> to;
    set<string> first;
};

#endif //COMPILERGENERATOR_PRODUCTION_H

