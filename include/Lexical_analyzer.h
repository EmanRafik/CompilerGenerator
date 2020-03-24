#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H
#include<string>
#include"DFA.h"

using namespace std;

class Lexical_analyzer
{
    public:
        Lexical_analyzer();
        virtual ~Lexical_analyzer();
        void read_input(string file_name);
        void setDFA(DFA *dfa);

    protected:

    private:
        DFA *dfa;

};

#endif // LEXICAL_ANALYZER_H
