#include <iostream>
#include "DFA.h"
#include"Lexical_analyzer_generator.h"
#include"Lexical_analyzer.h"
#include "NFA.h"
#include <vector>

using namespace std;
void printNFA(NFA nfa);
int main()
{
    Lexical_analyzer_generator *generator = new Lexical_analyzer_generator();
    generator->read_lexical_rules("rules.txt");
    generator->generate_lexical_analyzer();
    Lexical_analyzer *lexical = new Lexical_analyzer();
    lexical->setDFA(generator->get_minimal_dfa());
    lexical->execute("input.txt");

    return 0;
}
