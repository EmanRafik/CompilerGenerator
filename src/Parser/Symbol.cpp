//
// Created by DELL on 14-Apr-20.
//

#include <string>
#include "Phase2_Parser/Symbol.h"

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

void Symbol::setSymbol(const string &symbol) {
    Symbol::symbol = symbol;
}

void Symbol::setIsTerminal(bool isTerminal) {
    is_terminal = isTerminal;
}

