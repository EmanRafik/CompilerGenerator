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
    void setAcceptStatesList(map<int,Token> acceptStatesList);
    void setNFATable(vector<map<char,vector<int>>> table);
    vector<map<char,vector<int>>> getNFATable();
    int getAcceptState();
    void printAcceptStatesList();
    void setAcceptState(int acceptState);
    int getStartState();
    void setStartState(int startState);
    void printNFA();
    DFA* convertToDFA();
    set<int> closure(int s);
    set<int> moveStates(set<int> s, char c);
    bool inSet(set<int> m,vector<set<int>> vec);
protected:

private:
    map<int,Token> acceptStatesList;
    vector<map<char,vector<int>>> table;
    int acceptState;
    int startState;
};

#endif // NFA_H
