#include "NFA.h"
#include "Token.h"
#include <map>
#include <string>
#include <vector>
#include <stack>
#include "State.h"
NFA::NFA()
{

}

NFA::~NFA()
{
    //dtor
}

map<State*,map<char, vector<State*>>> NFA::getNFATable() {
    return table;
}

void NFA::setNFATable(map<State*,map<char,vector<State*>>> table){
    this->table = table;
}

map<State*,Token> NFA::getAcceptStatesList() {
    return acceptStatesList;
}

void NFA::addAcceptStateToList(State* state,Token token) {
    getAcceptStatesList().insert(pair<State*, Token>(state, token));
}

State *NFA::getAcceptState() const {
    return acceptState;
}

void NFA::setAcceptState(State *acceptState) {
    NFA::acceptState = acceptState;
}

State *NFA::getStartState() const {
    return startState;
}

void NFA::setStartState(State *startState) {
    NFA::startState = startState;
}

DFA NFA::convertToDFA(){
    DFA *dfa = new DFA(1,2);
    set<State*> s = closure(startState);
}

set<State*> NFA::closure(State *st){
    set<State*> res;
    stack<State*> closureStack;
    closureStack.push(st);
    while(!closureStack.empty()){
        State *s = closureStack.top();
        closureStack.pop();
        if(res.count(s)==0){
            res.insert(s);
            vector<State*> v = table[s][' '];
            for(int i=0;i<v.size();i++){
                res.insert(v.at(i));
            }
        }
    }
    return res;
}
