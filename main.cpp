#include <iostream>
#include <DFA.h>

using namespace std;

int main()
{
    map<int, Token> accept_states;
    Token *t = new Token();
    accept_states.insert(pair<int, Token>(1, *t));
    accept_states.insert(pair<int, Token>(2, *t));
    accept_states.insert(pair<int, Token>(3, *t));
    DFA *dfa = new DFA(5, 160 - 32, accept_states);
    return 0;
}
