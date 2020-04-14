//
// Created by DELL on 14-Apr-20.
//

#ifndef COMPILERGENERATOR_PRODUCTION_H
#define COMPILERGENERATOR_PRODUCTION_H

#include <string>
#include <vector>
#include "Symbol.h"

using namespace std;

class Production {
public:
    Production(string from);
    void addSymbol (Symbol s);
    string getFrom();
    vector<Symbol> getTo();

private:
    string from;
    vector<Symbol> to;

};

#endif COMPILERGENERATOR_PRODUCTION_H

