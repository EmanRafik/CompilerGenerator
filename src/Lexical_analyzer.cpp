#include "Lexical_analyzer.h"
#include "DFA.h"
#include <fstream>
#include<string>
#include<iostream>

using namespace std;

Lexical_analyzer::Lexical_analyzer() {

}

Lexical_analyzer::~Lexical_analyzer() {
    //dtor
}

void Lexical_analyzer::setDFA(DFA *dfa) {
    this->dfa = dfa;
}

void Lexical_analyzer::read_input(string file_name) {
    int current_state = 0;
    int input;
    string last_accepted_output = "";

    ifstream file;
    file.open(file_name, ios::in);
    if (file.is_open()) {
        for (char c; file.get(c);) {
            if (c != '\n') {
                cout << c << " --> ";
                input = c - 32;
                if (dfa->isAcceptState(current_state)) {
                    if (dfa->getAcceptStates()[current_state].getToken_class() == "id" ||
                        dfa->getAcceptStates()[current_state].getToken_class() == "num" ) {
                        last_accepted_output = dfa->getAcceptStates()[current_state].getToken_class();
                    } else {
                        last_accepted_output = dfa->getAcceptStates()[current_state].getValue();
                    }

                } else if (current_state == -1) {
                    if (last_accepted_output != "") {
                        cout << last_accepted_output;
                        last_accepted_output == "";
                    } else {
                        cout << "error";
                    }

                }
                cout << endl;
                current_state = dfa->getTable()[current_state][input];
            }
        }
    }
}
