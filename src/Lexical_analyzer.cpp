#include "Lexical_analyzer.h"
#include "DFA.h"
#include <fstream>
#include<string>
#include<iostream>

using namespace std;

Lexical_analyzer::Lexical_analyzer() {

}

Lexical_analyzer::~Lexical_analyzer()
{
    //dtor
}

void Lexical_analyzer::setDFA(DFA *dfa)
{
    this->dfa = dfa;
}

void Lexical_analyzer::read_input(string file_name)
{
    ifstream file;
    file.open(file_name, ios::in);
    if (file.is_open())
    {
        for (char c; file.get(c);)
        {
            if (c != '\n')
            {
                cout << c << endl;
            }
        }
    }
}
