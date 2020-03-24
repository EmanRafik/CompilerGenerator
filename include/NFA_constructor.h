#ifndef NFA_CONSTRUCTOR_H
#define NFA_CONSTRUCTOR_H
#include"NFA.h"
#include<string>
#include<iostream>
#include<vector>
#include"Regular_definition.h"


using namespace std;

class NFA_constructor
{
    public:
        NFA_constructor();
        virtual ~NFA_constructor();
        NFA constructNFA(string expression);
        NFA kleene_closure(NFA original_nfa);
        NFA positive_closure(NFA original_nfa);
        NFA oring(NFA original1, NFA original2,bool combine);
        NFA concatinating(NFA original1, NFA original2);
        NFA termNFA(string term);
        void setRegular_definitions(vector<Regular_definition> regular_definitions);

    protected:

    private:
        string trim(string s);
        vector<Regular_definition> regular_definitions;
};

#endif // NFA_CONSTRUCTOR_H
