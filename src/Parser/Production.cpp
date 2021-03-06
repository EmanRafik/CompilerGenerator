//
// Created by DELL on 14-Apr-20.
//

#include<set>
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

void Production::setFrom(const string &from) {
    Production::from = from;
}

void Production::setTo(const vector<Symbol> &to) {
    Production::to = to;
}
set<string> Production::get_first()
{
    return this->first;
}

void Production::add_first(set<string> s)
{
    first.insert(s.begin(), s.end());
}
