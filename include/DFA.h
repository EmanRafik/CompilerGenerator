#ifndef DFA_H
#define DFA_H

#include <vector>
#include "Token.h"
#include <map>

using namespace std;

class DFA {
    public:
        DFA(int number_of_states, int number_of_inputs, map<int, Token> accept_states);
        virtual ~DFA();
        int getNumberOfStates() const;
        void setNumberOfStates(int numberOfStates);

        int getNumberOfInputs() const;
        void setNumberOfInputs(int numberOfInputs);

        map<int, Token> getAcceptStates();
        void setAcceptStates(map<int, Token> acceptStates);

        int **getTable() const;
        void setTable(int **table);

    private:
        int number_of_states, number_of_inputs;
        map<int, Token> accept_states;
        int **table;

};

#endif // DFA_H
