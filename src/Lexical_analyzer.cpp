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

vector<string> Lexical_analyzer::getSymbolTable(){
    return symbol_table;
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
    analyze(input_code);
}

void Lexical_analyzer::analyze(vector<char> input_code) {
    int current_state = 0;
    int input;
    //info about the total analyzer state when last match occured
    // they have to be reset when state is accepted by resetting last_accepted_output to empty character
    string last_accepted_output = "";
    int last_accepted_state = 0;
    int last_accepted_character_index;

    string id = "";
    int id_counter = 0;

    char c;
    int i = 0;
    while (i < input_code.size()) {
        c = input_code[i];
        id += c;
        input = c - 32;
        current_state = dfa->getTable()[current_state][input];
        if (dfa->isAcceptState(current_state)) {
            last_accepted_state = current_state;
            last_accepted_character_index = i;
            if (dfa->getAcceptStates()[current_state].getToken_class() == "id" ||
                dfa->getAcceptStates()[current_state].getToken_class() == "num" ||
                dfa->getAcceptStates()[current_state].getToken_class() == "relop" ) {
                last_accepted_output = dfa->getAcceptStates()[current_state].getToken_class();
            } else {
                last_accepted_output = dfa->getAcceptStates()[current_state].getValue();
            }
            // add the recognized token to the vector of tokens
            tokens.push_back(dfa->getAcceptStates()[current_state]);
            current_state = dfa->getTable()[current_state][input];

        }
        if (current_state == phai || c == 32 || i == input_code.size()-1) {
            if (last_accepted_output != "") {
                cout << c << " --> " << last_accepted_output << endl;
                //add the matched ids to a symbol table
                if (dfa->getAcceptStates()[current_state].getToken_class() == "id") {
                    Token *t = new Token();
                    t->setToken_class("id");
                    //remove last (i - last_accepted_character_index) characters which are extra than the last match
                    t->setValue(id.substr(0, id.size()-(i-last_accepted_character_index)));
                    symbol_table.push_back(dfa->getAcceptStates()[current_state].getValue());
                }
                last_accepted_output = "";
                //backtrack to last matched state and character
                i = last_accepted_character_index;
                if (c == 32) {
                    i++;
                }

            } else {
                //no matches happened and phai state reached so error occured
                cout << c << " --> " << "Lexical error occurred" << endl;
            }
            //reset state again to start searching for tokens
            id = "";
            current_state = 0;
        }
        i++;
    }
}

