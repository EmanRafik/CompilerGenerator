#ifndef LEXICAL_ANALYZER_GENERATOR_H
#define LEXICAL_ANALYZER_GENERATOR_H
#include "Token.h"
#include "NFA.h"
#include <vector>

class Lexical_analyzer_generator
{
    public:
        Lexical_analyzer_generator();
        virtual ~Lexical_analyzer_generator();
        vector<NFA> getNFAList();
        void setNFAList(vector<NFA> list);
        void addNFA(NFA nfa);
        NFA combineNFA(vector<NFA> list);
    protected:

    private:
        vector<NFA> NFAlist;
};

#endif // LEXICAL_ANALYZER_GENERATOR_H
