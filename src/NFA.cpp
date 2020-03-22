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

vector<map<char,int>> NFA::getNFATable() {
    return table;
}

void NFA::setNFATable(vector<map<char,vector<int>>> table){
    this->table = table;
}

vector<map<int,Token>> NFA::getAcceptStates() {
    return acceptStates;
}

void NFA::setAcceptState(int state,Token token){
    map<int, Token> acceptStatesMap = getAcceptStates();
    acceptStatesMap[state] = token;
    this->acceptStates = acceptStatesMap;
}
