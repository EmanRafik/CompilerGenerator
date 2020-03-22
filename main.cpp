#include <iostream>
#include <DFA.h>

using namespace std;

int main()
{
    cout << "Hello" << endl;
    int a[3] = {1,2,3};
    DFA *dfa = new DFA(5, 160 - 32, a);
    cout << *dfa->getAcceptStates();
    return 0;
}
