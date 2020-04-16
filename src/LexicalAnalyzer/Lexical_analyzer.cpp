#include "Phase1_LexicalAnalyzer/Lexical_analyzer.h"
#include "Phase1_LexicalAnalyzer/DFA.h"
#include <fstream>
#include<string>
#include<iostream>
#include <Phase1_LexicalAnalyzer/Lexical_analyzer.h>

using namespace std;

const int phai = -1;

Lexical_analyzer::Lexical_analyzer() {
    this->current_token_index = 0;
}

Lexical_analyzer::~Lexical_analyzer() {
    //dtor
}

void Lexical_analyzer::setDFA(DFA *dfa) {
    this->current_token_index = 0;
    this->dfa = dfa;
}

void Lexical_analyzer::set_input_code(vector<char> input_code) {
    this->input_code = input_code;
}

void Lexical_analyzer::execute(string file_name) {
    read_input(file_name);
    analyze(input_code);
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
    ofstream file;
    file.open("output.txt", std::ofstream::trunc);
    int current_state = 0;
    int input;
    int last = 0;
    //info about the total analyzer state when last match occured
    // they have to be reset when state is accepted by resetting last_accepted_output to empty character
    string last_accepted_output = "";
    int last_accepted_state = 0;
    int last_accepted_character_index = 0;
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
            if (dfa->getAcceptStates()[current_state].getToken_class() == "keyword"
            || dfa->getAcceptStates()[current_state].getToken_class() == "punctuation") {
                last_accepted_output = dfa->getAcceptStates()[current_state].getValue();
            } else {
                last_accepted_output = dfa->getAcceptStates()[current_state].getToken_class();
            }
//            tokens.push_back(dfa->getAcceptStates()[current_state]);
        }
        if (current_state == phai || c == 32 || i == input_code.size()-1) {
            if (last_accepted_output != "") {
                //remove last (i - last_accepted_character_index) characters which are extra than the last match
                id = id.substr(0, id.size()-(i-last_accepted_character_index));
                cout << id << " --> " << last_accepted_output << endl;
                file << id << " --> " << last_accepted_output << endl;

                // add the recognized token to the vector of tokens
                Token *t = new Token();
//                *t = dfa->getAcceptStates()[current_state];
                t->setToken_class(dfa->getAcceptStates()[current_state].getToken_class());
                t->setValue(id);
                tokens.push_back(*t);
                //add the matched ids to a symbol table
                if (dfa->getAcceptStates()[current_state].getToken_class() == "id") {
                    symbol_table.push_back(dfa->getAcceptStates()[current_state].getValue());
                }
                last_accepted_output = "";
                //backtrack to last matched state and character
                i = last_accepted_character_index;
                if (c == 32) {
                    i++;
                }

            } else {
                if (last == 0) {
                    i = last;
                    last++;
                } else {
                    i = last+1;
                    last++;
                }
                //If no matches happened and phai state reached and current character is not a space so error occured
                if (c != 32) {
                    cout << id << " --> " << "Lexical error" << endl;
                    file << id << " --> " << "Lexical error" << endl;
                }
            }
            //reset state again to start searching for tokens
            last = i;
            id = "";
            current_state = 0;
        }
        i++;
    }
}

Token Lexical_analyzer::getNextToken () {
    if (current_token_index != tokens.size()) {
        Token token = tokens.at(current_token_index);
        current_token_index++;
        return token;
    } else {
        Token *token = new Token();
        token->setValue("$");
        return *token;
    }
}

