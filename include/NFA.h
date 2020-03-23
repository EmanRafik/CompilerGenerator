#ifndef NFA_H
#define NFA_H
#include <map>
#include <string>
#include <vector>
#include "Token.h"
#include "State.h"
#include "DFA.h"

using namespace std;

class NFA {
public:
    NFA();
    virtual ~NFA();
    void addAcceptStateToList(State* state,Token token);
    map<State*,Token> getAcceptStatesList();
    void setNFATable(map<State*,map<char,vector<State*>>> table);
    map<State*,map<char, vector<State*>>> getNFATable();
    State *getAcceptState() const;
    void setAcceptState(State *acceptState);
    State *getStartState() const;
    void setStartState(State *startState);
    DFA convertToDFA();
    vector<State> closure(State *s);
protected:

private:
    map<State*,Token> acceptStatesList;
    map<State*,map<char,vector<State*>>> table;
    State* acceptState;
    State* startState;
};

#endif // NFA_H
