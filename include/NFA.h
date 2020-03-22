#ifndef NFA_H
#define NFA_H
#include <map>
#include <string>
#include <vector>
#include "Token.h"

class NFA {
public:
    NFA();
    virtual ~NFA();
    void setAcceptState(int state,Token token);
    vector<map<int,Token>> getAcceptStates();
    void setNFATable(vector<map<char,vector<int>>> table);
    vector<map<char,int>> getNFATable();
protected:

private:
    vector<map<int,Token>> acceptStates;
    vector<map<char,vector<int>>> table;
};

#endif // NFA_H
