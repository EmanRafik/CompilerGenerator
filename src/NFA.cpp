#include "NFA.h"
#include "Token.h"
#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <stack>
#include <cstdio>
#include "State.h"
#include <stdio.h>
NFA::NFA()
{

}

NFA::~NFA()
{
    //dtor
}

vector<map<char,vector<int>>> NFA::getNFATable() {
    return table;
}

void NFA::setNFATable(vector<map<char,vector<int>>> table){
    this->table = table;
}

map<int,Token> NFA::getAcceptStatesList() {
    return acceptStatesList;
}

void NFA::addAcceptStateToList(int state,Token token) {
    acceptStatesList.insert(pair<int, Token>(state, token));
}
void NFA::setAcceptStatesList(map<int,Token> acceptStatesList) {
    this->acceptStatesList = acceptStatesList;
}
int NFA::getAcceptState() {
    return acceptState;
}

void NFA::setAcceptState(int acceptState) {
    NFA::acceptState = acceptState;
}

int NFA::getStartState(){
    return startState;
}

void NFA::setStartState(int startState) {
    NFA::startState = startState;
}
void NFA::printNFA(){
    std::vector<map<char,vector<int>>>::iterator it = table.begin();
    int i=0;
    while(it != table.end()){
        printf("state: %d          ",i);
        std::map<char,vector<int>>::iterator mapIt = table[i].begin();
        while(mapIt != table[i].end() ){
            printf("input: %c        to ",mapIt->first);
            for(int state : mapIt->second){
                printf("%d ",state);
            }
            printf("\n");
            mapIt++;
        }
        i++;
        it++;
    }
    printf("---------------------------------------------------------------------------\n");
}
void NFA::printAcceptStatesList(){
    std::map<int, Token>::iterator it = acceptStatesList.begin();
    while (it != acceptStatesList.end())
    {
        cout << " accept state num: " << it->first<< endl;
        Token t = it->second;
        cout << "token: "<< t.getToken_class() << endl;
        it++;
    }
};

DFA* NFA::convertToDFA(){
    DFA *dfa = new DFA(0,95);
    set<int> s = closure(0);
    dfa->addState();
    vector<set<int>> vec;
    vec.push_back(s);
    int n=0;
    while(n<vec.size()){
        for(int i=1;i<95;i++){
            set<int> m = moveStates(vec.at(n),i+32);
            if(m.size()>0){
                if(!inSet(m,vec)){
                    vec.push_back(m);
                    dfa->addState();
                    dfa->addTransition(n,i,vec.size()-1);
                }else{
                    for(int j=0;j<vec.size();j++){
                        if(vec.at(j)==m){
                            dfa->addTransition(n,i,j);
                        }
                    }
                }
            }
        }
        n++;
    }
    map<int,Token>::iterator it = acceptStatesList.begin();
    while(it!=acceptStatesList.end()){
        for(int j=0;j<vec.size();j++){
            set<int>::iterator setit = vec.at(j).begin();
            while(setit!=vec.at(j).end()){
                if(*setit==it->first){
                    dfa->addAcceptState(j,it->second);
                }
                setit++;
            }
        }
        it++;
    }
    return dfa;
}

set<int> NFA::closure(int st){
    set<int> res;
    stack<int> closureStack;
    closureStack.push(st);
    while(!closureStack.empty()){
        int s = closureStack.top();
        closureStack.pop();
        if(res.count(s)==0){
            res.insert(s);
            int c = table[s].count(' ');
            if(c>0){
                vector<int> v = table[s][' '];
                for(int i=0;i<v.size();i++){
                    closureStack.push(v.at(i));
                }
            }
        }
    }
    return res;
}

set<int> NFA::moveStates(set<int> s, char c){
    set<int> res;
    set<int>::iterator it = s.begin();
    while(it!=s.end()){
        int x = table[*it].count(c);
        if(x>0){
            vector<int> v = table[*it][c];
            for(int i=0;i<v.size();i++){
                set<int> eps = closure(v.at(i));
                set<int>::iterator epsit = eps.begin();
                while(epsit!=eps.end()){
                    res.insert(*epsit);
                    epsit++;
                }
            }
        }
        it++;
    }
    return res;
}

bool NFA::inSet(set<int> s,vector<set<int>> vec){
    for(int i=0;i<vec.size();i++){
        if(vec.at(i)==s){
            return true;
        }
    }
    return false;
}

