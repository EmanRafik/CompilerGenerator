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
    DFA *dfa = new DFA(0,126-32);
    set<State*> s = closure(startState);
    dfa.addState();
    vector<set<State*>> vec;
    vec.push_back(s);
    int n=0;
    while(n<vec.size()){
        for(int i=0;i<95;i++){
            set<State*> m = moveStates(vec.at(n));
            if(m.size()>0){
                if(!inSet(m,vec)){
                    vec.push_back(moveStates(vec.at(n)),i+32);
                    dfa.addState();
                    dfa.addTransition(n,i,vec.size()-1);
                }else{
                    for(int j=0;j<vec.size();j++){
                        if(vec.at(j)==m){
                            dfa.addTransition(n,i,j);
                        }
                    }
                }
            }
        }
        n++;
    }
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

set<State*> NFA::moveStates(set<State*> s, char c){
    set<State*> res;
    set<State*>::iterator it = s.begin();
    while(it!=s.end()){
        vector<State*> v = table[*it][c];
        for(int i=0;i<v.size();i++){
            res.insert(v.at(i));
        }
        it++;
    }
    return res;
}

bool NFA::inSet(set<State*> s,vector<set<State*>> vec){
    for(int i=0;i<vec.size();i++){
        if(vec.at(i)==s){
            return true;
        }
    }
    return false;
}
