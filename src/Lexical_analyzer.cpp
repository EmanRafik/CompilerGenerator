#include "Lexical_analyzer.h"
#include "DFA.h"
#include <fstream>
#include<string>
#include<iostream>

using namespace std;

const int phai = -1;

Lexical_analyzer::Lexical_analyzer() {

}

Lexical_analyzer::~Lexical_analyzer() {
    //dtor
}

void Lexical_analyzer::setDFA(DFA *dfa) {
    this->dfa = dfa;
}

void Lexical_analyzer::set_input_code(vector<char> input_code) {
    this->input_code = input_code;
}

vector<char> Lexical_analyzer::get_input_code() {
    return input_code;
}

vector<Token> Lexical_analyzer::getTokens() {
    return tokens;
}

void Lexical_analyzer::read_input(string file_name) {

    vector<char> input_code;
    ifstream file;
    file.open(file_name, ios::in);
    if (file.is_open()) {
        for (char c; file.get(c);) {
            if (c != '\n') {
                input_code.push_back(c);
            }
        }
    }
    set_input_code(input_code);
}

void Lexical_analyzer::analyze(vector<char> input_code) {
    int current_state = 0;
    int input;
    //info about the total analyzer state when last match occured
    // they have to be reset when state is accepted by resetting last_accepted_output to empty character
    string last_accepted_output = "";
    int last_accepted_state = 0;
    int last_accepted_character_index;

    char c;
    for (int i = 0; input_code.size(); i++) {
        c = input_code[i];
        input = c - 32;
        if (dfa->isAcceptState(current_state)) {
            last_accepted_state = current_state;
            last_accepted_character_index = i;
            if (dfa->getAcceptStates()[current_state].getToken_class() == "id" ||
                dfa->getAcceptStates()[current_state].getToken_class() == "num" ) {
                last_accepted_output = dfa->getAcceptStates()[current_state].getToken_class();
            } else {
                last_accepted_output = dfa->getAcceptStates()[current_state].getValue();
            }
            tokens.push_back(dfa->getAcceptStates()[current_state]);

        } else if (current_state == phai) {
            if (last_accepted_output != "") {
                cout << c << " --> " << last_accepted_output;
                last_accepted_output == "";
                i = last_accepted_character_index;
                current_state = last_accepted_state;
            } else {
                //no matches happened and phai state reached
                cout << "error";
            }

        }
        cout << endl;
        current_state = dfa->getTable()[current_state][input];
    }
}

