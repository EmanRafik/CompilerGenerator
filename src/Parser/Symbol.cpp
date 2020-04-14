//
// Created by DELL on 14-Apr-20.
//

#include<string>
#include <Parser/Symbol.h>

Symbol::Symbol(string s, bool isTerminal) : s(s), isTerminal(isTerminal) {}

const string Symbol::getSymbol() {
    return s;
}

bool Symbol::isTerminal1() {
    return isTerminal;
}
