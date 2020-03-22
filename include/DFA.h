#ifndef DFA_H
#define DFA_H

#include <vector>

class DFA
{
    public:
        DFA();
        virtual ~DFA();

    protected:

    private:
        int number_of_states, number_of_inputs;
        int **table;
        std::vector <int> accept_states;

};

#endif // DFA_H
