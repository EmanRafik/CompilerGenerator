#include <iostream>
#include "DFA.h"

DFA::DFA(int number_of_states, int number_of_inputs, map<int, Token> accept_states) {
    this->number_of_states = number_of_states;
    this->number_of_inputs = number_of_inputs;
    this->accept_states = accept_states;
    //initialize table 2D array
    this->table = new int *[number_of_states];
    for (int i = 0; i < number_of_states; i++)
        this->table[i] = new int[number_of_inputs];

    map<int, Token>::iterator itr;
    for (itr =  accept_states.begin(); itr !=  accept_states.end(); ++itr) {
        cout  << itr->first << endl;
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

 map<int, Token> DFA::getAcceptStates() {
    return accept_states;
}

void DFA::setAcceptStates(const map<int, Token> acceptStates) {
    accept_states = acceptStates;
}


