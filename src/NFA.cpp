#include "NFA.h"
#include "Token.h"
#include <map>
#include <string>
#include <vector>
NFA::NFA()
{

}

NFA::~NFA()
{
    //dtor
}

vector<map<char, vector<int>>> NFA::getNFATable() {
    return table;
}

void NFA::setNFATable(vector<map<char,vector<int>>> table){
    this->table = table;
}

map<int,Token> NFA::getAcceptStates() {
    return acceptStates;
}

void NFA::addAcceptState(int state,Token token) {
    getAcceptStates().insert(pair<int, Token>(state, token));
}
