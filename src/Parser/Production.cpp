//
// Created by DELL on 14-Apr-20.
//

#include "Phase2_Parser/Production.h"

Production::Production() {

}

Production::Production(string from){
    this->from = from;
}

void Production::addSymbol (Symbol s){
    to.push_back(s);
}

string Production::getFrom() {
    return from;
}

std::vector <Symbol> Production::getTo() {
    return to;
}
