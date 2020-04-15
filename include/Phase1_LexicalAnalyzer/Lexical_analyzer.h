#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H
#include<string>
#include"DFA.h"

using namespace std;

class Lexical_analyzer {
    public:
        Lexical_analyzer();
        virtual ~Lexical_analyzer();
        void execute(string file_name);
        void read_input(string file_name);
        void setDFA(DFA *dfa);
        void analyze (vector<char> input_code);
        void set_input_code (vector<char> input_code);
        Token getNextToken ();

    private:
        vector<char> input_code;
        vector<Token> tokens;
        vector<string> symbol_table;
        int current_token_index;
        DFA *dfa;


};

#endif // LEXICAL_ANALYZER_H
