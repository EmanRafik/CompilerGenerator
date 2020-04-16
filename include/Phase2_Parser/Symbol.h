//
// Created by DELL on 14-Apr-20.
//

#ifndef COMPILERGENERATOR_SYMBOL_H
#define COMPILERGENERATOR_SYMBOL_H

#include <string>

using namespace std;

class Symbol {
public:
    Symbol();
    Symbol(string symbol, bool isTerminal);
    string getSymbol();
    bool isTerminal();

private:
    string symbol;
    bool is_terminal;

};

#endif //COMPILERGENERATOR_SYMBOL_H
