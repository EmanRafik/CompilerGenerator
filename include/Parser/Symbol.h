//
// Created by DELL on 14-Apr-20.
//

#ifndef COMPILERGENERATOR_SYMBOL_H
#define COMPILERGENERATOR_SYMBOL_H

#include <string>

using namespace std;

class Symbol {
public:
    Symbol(string s, bool isTerminal);
    const string getSymbol();
    bool isTerminal1();

private:
    string s;
    bool isTerminal;

};

#endif //COMPILERGENERATOR_SYMBOL_H
