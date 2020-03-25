#ifndef NFA_H
#define NFA_H
#include <map>
#include <string>
#include <vector>
#include <set>
#include "Token.h"
#include "State.h"
#include "DFA.h"

using namespace std;

class NFA {
public:
    NFA();
    virtual ~NFA();
    void addAcceptStateToList(int state,Token token);
    map<int,Token> getAcceptStatesList();
    void setNFATable(vector<map<char,vector<int>>> table);
    vector<map<char,vector<int>>> getNFATable();
    int getAcceptState() const;
    void setAcceptState(int acceptState);
    int getStartState() const;
    void setStartState(int startState);
    void printNFA();
    DFA convertToDFA();
    set<State*> closure(State *s);
    set<State*> moveStates(set<State*> s, char c);
    bool inSet(set<State*> m,vector<set<State*>> vec);
protected:

private:
    map<int,Token> acceptStatesList;
    vector<map<char,vector<int>>> table;
    int acceptState;
    int startState;
};

#endif // NFA_H
