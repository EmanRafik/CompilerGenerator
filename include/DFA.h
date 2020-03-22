#ifndef DFA_H
#define DFA_H

#include <vector>

using namespace std;

class DFA {
    public:
        DFA(int number_of_states, int number_of_inputs, int acceptStates[]);
        virtual ~DFA();
        int getNumberOfStates() const;
        void setNumberOfStates(int numberOfStates);

        int getNumberOfInputs() const;
        void setNumberOfInputs(int numberOfInputs);

        int *getAcceptStates() const;
        void setAcceptStates(int *acceptStates);

        int **getTable() const;
        void setTable(int **table);

    private:
        int number_of_states, number_of_inputs;
        int *accept_states;
        int **table;

};

#endif // DFA_H
