//
// Created by DELL on 14-Apr-20.
//

#include<string>
#include "Symbol.h"

Symbol::Symbol() {

}

Symbol::Symbol(string symbol, bool isTerminal) {
    this->symbol = symbol;
    this->is_terminal = isTerminal;
}

string Symbol::getSymbol() {
    return symbol;
}

bool Symbol::isTerminal() {
    return is_terminal;
}

