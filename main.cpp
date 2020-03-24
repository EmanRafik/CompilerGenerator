#include <iostream>
#include "DFA.h"
#include"Lexical_analyzer_generator.h"
#include"Lexical_analyzer.h"

using namespace std;

int main()
{
    Lexical_analyzer_generator *generator = new Lexical_analyzer_generator();
    generator->read_lexical_rules("rules.txt");
    generator->generate_lexical_analyzer();
////    DFA *dfa = generator->get_minimal_dfa();
//    Lexical_analyzer *lexical = new Lexical_analyzer();
//
//    DFA *dfa = new DFA(6, 95);
//    dfa->addTransition(0,0,1);
//    dfa->addTransition(1,0,0);
//    dfa->addTransition(2,0,4);
//    dfa->addTransition(3,0,4);
//    dfa->addTransition(4,0,4);
//    dfa->addTransition(5,0,5);
//
//    dfa->addTransition(0,1,5);
//    dfa->addTransition(1,1,1);
//    dfa->addTransition(2,1,5);
//    dfa->addTransition(3,1,5);
//    dfa->addTransition(4,1,5);
//    dfa->addTransition(5,1,5);
//
//    Token *t1 = new Token();
//    t1->setToken_class("id");
//    Token *t2 = new Token();
//    t2->setToken_class("num");
//    Token *t3 = new Token();
//    t3->setToken_class("relop");
//    dfa->addAcceptState(2, *t1);
//    dfa->addAcceptState(3, *t2);
//    dfa->addAcceptState(4, *t3);
//
//    dfa->minimize().print_dfa();
//
//    lexical->setDFA(dfa);
//    lexical->read_input("input.txt");

    return 0;
}
