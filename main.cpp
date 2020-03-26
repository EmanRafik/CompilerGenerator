#include <iostream>
#include "DFA.h"
#include"Lexical_analyzer_generator.h"
#include"Lexical_analyzer.h"
#include "NFA_constructor.h"
#include "NFA.h"
#include "State.h"
#include <map>
#include <vector>
#include <set>
#include <stdio.h>
using namespace std;
void printNFA(NFA nfa);
int main()
{
    Lexical_analyzer_generator *generator = new Lexical_analyzer_generator();
    generator->read_lexical_rules("rules.txt");
    generator->generate_lexical_analyzer();
    Lexical_analyzer *lexical = new Lexical_analyzer();
    lexical->setDFA(generator->get_minimal_dfa());
    lexical->read_input("input.txt");

//    DFA *dfa = generator->get_minimal_dfa();
/*   Lexical_analyzer *lexical = new Lexical_analyzer();

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


   /*NFA_constructor *constructor = new NFA_constructor();
    NFA nfa1 = constructor->signleCharNFA('a');
    //nfa1.printNFA();
    NFA nfa2 = constructor->signleCharNFA('b');
    NFA nfa3 = constructor->signleCharNFA('c');
    //nfa2.printNFA();
    NFA concatenatedNFA = constructor->concatinating(nfa1,nfa2);
    //concatenatedNFA.printNFA();
    NFA orNFA = constructor->oring(nfa1,nfa2);
    vector<NFA> list;
    list.push_back(nfa1);
    list.push_back(nfa2);
    list.push_back(nfa3);
    NFA orNFAlist = constructor->oringList(list,true);
    orNFAlist.printNFA();
    DFA* d = orNFAlist.convertToDFA();
    d->print_dfa();
    set<int> x;
    x.insert(0);
    x.insert(1);
    x.insert(5);*/


    /*set<int> s = orNFAlist.moveStates(x,'c');
    set<int>::iterator it = s.begin();
    while(it != s.end()){
        cout<<*it<<endl;
        it++;
    }*/

   // NFA kleeneclosureNFA = constructor->kleene_closure(nfa1);
    //kleeneclosureNFA.printNFA();
   // NFA positiveclosureNFA = constructor->positive_closure(nfa1);
   // positiveclosureNFA.printNFA();

    return 0;
}
