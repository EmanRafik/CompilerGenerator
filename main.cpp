#include <iostream>
#include "DFA.h"
#include"Lexical_analyzer_generator.h"
#include"Lexical_analyzer.h"
#include "NFA_constructor.h"
#include "NFA.h"
#include "State.h"
#include <map>
#include <vector>
#include <stdio.h>
using namespace std;
void printNFA(NFA nfa);
int main()
{
    /*Lexical_analyzer_generator *generator = new Lexical_analyzer_generator();
    generator->read_lexical_rules("rules.txt");
    generator->generate_lexical_analyzer();
//    DFA *dfa = generator->get_minimal_dfa();
    Lexical_analyzer *lexical = new Lexical_analyzer();

    DFA *dfa = new DFA(6, 2);
    dfa->addTransition(0,0,1);
    dfa->addTransition(1,0,0);
    dfa->addTransition(2,0,4);
    dfa->addTransition(3,0,4);
    dfa->addTransition(4,0,4);
    dfa->addTransition(5,0,5);

    dfa->addTransition(0,1,5);
    dfa->addTransition(1,1,1);
    dfa->addTransition(2,1,5);
    dfa->addTransition(3,1,5);
    dfa->addTransition(4,1,5);
    dfa->addTransition(5,1,5);

    Token *t1 = new Token();
    t1->setToken_class("id");
    Token *t2 = new Token();
    t2->setToken_class("num");
    Token *t3 = new Token();
    t3->setToken_class("relop");
    dfa->addAcceptState(2, *t1);
    dfa->addAcceptState(3, *t2);
    dfa->addAcceptState(4, *t3);

    dfa->minimize().print_dfa();

    lexical->setDFA(dfa);
    lexical->read_input("input.txt");
*/
    NFA_constructor *constructor = new NFA_constructor();
    NFA nfa1 = constructor->signleCharNFA('a');
    printNFA(nfa1);
    NFA nfa2 = constructor->signleCharNFA('b');
    printNFA(nfa2);
    NFA concatenatedNFA = constructor->concatinating(nfa1,nfa2);
    printNFA(concatenatedNFA);
    return 0;
}
void printNFA(NFA nfa){
    std::vector<map<char,vector<int>>>::iterator it = nfa.getNFATable().begin();
    int i=0;
    while(i <= nfa.getAcceptState() &&it != nfa.getNFATable().end()){
        printf("state: %d          ",i);
        std::map<char,vector<int>>::iterator mapIt = nfa.getNFATable()[i].begin();
        while(mapIt != nfa.getNFATable()[i].end() ){
            printf("input: %c        to ",mapIt->first);
            for(int state : mapIt->second){
                printf("%d ",state);
            }
            printf("\n");
            mapIt++;
        }
        i++;
        it++;
    }
    printf("---------------------------------------------------------------------------\n");
}
