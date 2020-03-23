#ifndef NFA_H
#define NFA_H
#include <map>
#include <string>
#include <vector>
#include "Token.h"

using namespace std;

class NFA {
public:
    NFA();
    virtual ~NFA();
    void addAcceptState(int state,Token token);
    map<int,Token> getAcceptStates();
    void setNFATable(vector<map<char,vector<int>>> table);
    vector<map<char, vector<int>>> getNFATable();
protected:

private:
    map<int,Token> acceptStates;
    vector<map<char,vector<int>>> table;
};

#endif // NFA_H
