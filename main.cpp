#include <iostream>
#include <DFA.h>

using namespace std;

int main()
{
    DFA *dfa = new DFA(6, 2);

    dfa->addTransition(0,0,1);
    dfa->addTransition(1,0,0);
    dfa->addTransition(2,0,4);
    dfa->addTransition(3,0,4);
    dfa->addTransition(4,0,4);
    dfa->addTransition(5,0,5);

    dfa->addTransition(0,1,2);
    dfa->addTransition(1,1,3);
    dfa->addTransition(2,1,5);
    dfa->addTransition(3,1,5);
    dfa->addTransition(4,1,5);
    dfa->addTransition(5,1,5);

    Token *t = new Token();
    dfa->addAcceptState(2, *t);
    dfa->addAcceptState(3, *t);
    dfa->addAcceptState(4, *t);

    DFA mini_dfa = dfa->minimize();

    dfa->print_dfa();
    return 0;
}
