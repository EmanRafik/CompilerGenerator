#ifndef LEXICAL_ANALYZER_GENERATOR_H
#define LEXICAL_ANALYZER_GENERATOR_H
#include "Token.h"
#include "NFA.h"
#include"Regular_definition.h"
#include"Regular_expression.h"
#include<string>
#include <vector>

using namespace std;

class Lexical_analyzer_generator
{
    public:
        Lexical_analyzer_generator();
        virtual ~Lexical_analyzer_generator();
        vector<NFA> getNFAList();
        void setNFAList(vector<NFA> list);
        void addNFA(NFA nfa);
        NFA combineNFA(vector<NFA> list);
        void read_lexical_rules(string file_name);

    protected:

    private:
        vector<NFA> NFAlist;
        void classify_line(string line);
        vector<Regular_expression> regular_expressions;
        vector<Regular_definition> regular_definitions;
        vector<string> keywords;
        vector<string> punctuations;
        string trim(string s);
};

#endif // LEXICAL_ANALYZER_GENERATOR_H
