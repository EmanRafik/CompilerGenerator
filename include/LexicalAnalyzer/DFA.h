#ifndef DFA_H
#define DFA_H

#include <vector>
#include "Token.h"
#include <map>

using namespace std;

class DFA {
    public:
        DFA(int number_of_states, int number_of_inputs);
        DFA(int number_of_inputs);
        virtual ~DFA();
        int getNumberOfStates() const;
        int getNumberOfInputs() const;
        map<int, Token> getAcceptStates();
        int **getTable() const;
        void addTransition(int from, int input, int to);
        void addState();
        void addAcceptState(int state,Token token);
        bool isAcceptState(int state);
        bool areCompatibleStates (int state1, int state2, vector<int> partitions);
        DFA* minimize ();
        void print_dfa();
        string printHelper(const int x, const int width);


        private:
        int number_of_states, number_of_inputs;
        map<int, Token> accept_states;
        int **table;

};

#endif // DFA_H
