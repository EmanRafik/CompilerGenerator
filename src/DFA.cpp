#include <iostream>
#include "DFA.h"

DFA::DFA(int number_of_states, int number_of_inputs, int acceptStates[]) {
    this->number_of_states = number_of_states;
    this->number_of_inputs = number_of_inputs;
    this->accept_states = acceptStates;
    //initialize table 2D array
    this->table = new int *[number_of_states];
    for (int i = 0; i < number_of_states; i++)
        this->table[i] = new int[number_of_inputs];

    for (int i = 0; i < 3; i++) {
        cout << this->accept_states[i] << endl;
    }
}

DFA::~DFA() {
    //dtor
}

int DFA::getNumberOfStates() const {
    return number_of_states;
}

void DFA::setNumberOfStates(int numberOfStates) {
    number_of_states = numberOfStates;
}

int DFA::getNumberOfInputs() const {
    return number_of_inputs;
}

void DFA::setNumberOfInputs(int numberOfInputs) {
    number_of_inputs = numberOfInputs;
}

int **DFA::getTable() const {
    return table;
}

void DFA::setTable(int **table) {
    DFA::table = table;
}

int *DFA::getAcceptStates() const {
    return accept_states;
}

void DFA::setAcceptStates(int *acceptStates) {
    accept_states = acceptStates;
}

