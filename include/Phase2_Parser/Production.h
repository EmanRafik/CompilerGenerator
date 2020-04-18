//
// Created by DELL on 14-Apr-20.
//

#ifndef COMPILERGENERATOR_PRODUCTION_H
#define COMPILERGENERATOR_PRODUCTION_H

#include <string>
#include <vector>
#include "Phase2_Parser/Symbol.h"

using namespace std;

class Production {
public:
    Production();
    Production(string from);
    void addSymbol (Symbol s);
    string getFrom();
    vector<Symbol> getTo() ;

private:
    string from;
public:
    void setFrom(const string &from);

private:
    vector<Symbol> to;
public:
    void setTo(const vector<Symbol> &to);

};

#endif //COMPILERGENERATOR_PRODUCTION_H

