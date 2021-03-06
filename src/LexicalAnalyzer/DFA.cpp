#include <iostream>
#include <fstream>
#include <sstream>
#include "Phase1_LexicalAnalyzer/DFA.h"

const int phai = -1;

DFA::DFA(int number_of_inputs) {
    this->number_of_states = 0;
    this->number_of_inputs = number_of_inputs;
}

DFA::DFA(int number_of_states, int number_of_inputs) {
    this->number_of_states = number_of_states;
    this->number_of_inputs = number_of_inputs;
    //initialize table 2D array with -2s
    this->table = new int *[number_of_states];
    for (int i = 0; i < number_of_states; i++)
        this->table[i] = new int[number_of_inputs];

    for (int i = 0; i < number_of_states; i++) {
        for (int j = 0; j < number_of_inputs; j++) {
            table[i][j] = phai;
        }
    }

}

DFA::~DFA() {
    //dtor
}

int DFA::getNumberOfStates() const {
    return number_of_states;
}

int DFA::getNumberOfInputs() const {
    return number_of_inputs;
}

int **DFA::getTable() const {
    return table;
}

void DFA::addTransition(int from, int input, int to) {
    DFA::table[from][input] = to;
}

void DFA::addState() {
    number_of_states++;
    int **new_table = new int *[number_of_states];

    for (int i = 0; i < number_of_states; i++)
        new_table[i] = new int[number_of_inputs];

    for (int i = 0; i < number_of_states; i++) {
        for (int j = 0; j < number_of_inputs; j++) {
            if (i < number_of_states - 1) {
                new_table[i][j] = table[i][j];
            } else {
                new_table[i][j] = phai;
            }
        }
    }
    this->table = new_table;
}

map<int, Token> DFA::getAcceptStates() {
    return accept_states;
}

void DFA::addAcceptState(int state,Token token) {
    if (accept_states.count(state)) {
        if (token.getPriority() < accept_states.at(state).getPriority()) {
            accept_states.at(state) = token;
        }
    } else {
        accept_states.insert(pair<int, Token>(state, token));
    }
}

bool DFA::isAcceptState (int state) {
    if (accept_states.size() == 0) {
        return false;
    }
    map<int, Token>::iterator itr;
    for (itr =  accept_states.begin(); itr !=  accept_states.end(); ++itr) {
        if (itr->first == state) {
            return true;
        }
    }
    return false;
}

bool DFA::areCompatibleStates (int state1, int state2, vector<int> states_partitions) {
    for (int i = 0; i < number_of_inputs; i++) {
        if (table[state1][i] >= 0 && table[state2][i] >= 0) {
            if (states_partitions[table[state1][i]] != states_partitions[table[state2][i]]) {
                return false;
            }
        } else if ((table[state1][i]  < 0 && table[state2][i] >= 0) || ((table[state1][i] ) >= 0 && table[state2][i] < 0)){
            return false;
        }

    }
    return true;
}

DFA* DFA::minimize() {
    vector< vector<int> > partitions;
    //partition states into one partition for all non-acceptance states
    // and one partition for each acceptance state.
    vector<int> nonAcceptStates;
    int counter = 0;
    vector <int> states_partitions(number_of_states, -1);

    for (int i = 0; i < number_of_states; i++) {
        if (!isAcceptState(i)) {
            nonAcceptStates.push_back(i);
        } else {
            vector<int> v;
            v.push_back(i);
            partitions.push_back(v);
        }
    }
    partitions.insert(partitions.begin(),nonAcceptStates);

    for (int i = 0; i < partitions.size(); i++) {
        for (int j = 0; j < partitions[i].size(); j++) {
            states_partitions[partitions[i][j]] = i;
        }
    }

    vector< vector<int> > old_partitions = partitions;
    partitions.erase(partitions.begin(), partitions.end());
    vector< vector<int> > new_partitions;
    bool flag = true;
    while (flag) {
        for (int i = 0; i < old_partitions.size(); i++) {
            //we are inside one partition here
            if (old_partitions[i].size() > 1) {
                //partition has more than one state
                // so it can be broken down into more states
                //put the 1st state of this partition into separate partition
                vector<int> v;
                v.push_back(old_partitions[i][0]);
                partitions.push_back(v);
                for (int j = 1; j < old_partitions[i].size(); j++) {
                    bool isCompatiple = false;
                    for (int k = 0; k < partitions.size(); k++) {
                        if (areCompatibleStates(partitions[k][0], old_partitions[i][j], states_partitions)) {
                            partitions[k].push_back(old_partitions[i][j]);
                            isCompatiple = true;
                        }
                    }
                    if (!isCompatiple) {
                        vector<int> t;
                        t.push_back(old_partitions[i][j]);
                        partitions.push_back(t);
                    }
                }
                //erase partitions vector to be filled by partitions of another broken one
                for (int k = 0; k < partitions.size(); k++) {
                    new_partitions.push_back(partitions[k]);
                }
                partitions.erase(partitions.begin(), partitions.end());
            } else {
                //partition has one state so insert it in partitions
                new_partitions.push_back(old_partitions[i]);
            }
        }
        for (int i = 0; i < new_partitions.size(); i++) {
            for (int j = 0; j < new_partitions[i].size(); j++) {
                states_partitions[new_partitions[i][j]] = i;
            }
        }

        flag = (old_partitions.size() != new_partitions.size());
        old_partitions = new_partitions;
        new_partitions.erase(new_partitions.begin(), new_partitions.end());

    }

    if (number_of_states == old_partitions.size()) {
        return this;
    }
    DFA *dfa = new DFA(old_partitions.size(), number_of_inputs);

    //add transitions relative to new partitions
    for (int i = 0; i < dfa->getNumberOfStates(); i++) {
        for (int j = 0; j < dfa->getNumberOfInputs(); j++) {
            if (table[ old_partitions[i][0] ] [j] != phai) {
                dfa->addTransition(i, j, states_partitions[table[old_partitions[i][0]][j]]);
            }
        }
    }

    //add accept states relative to new partitions
    map<int, Token>::iterator itr;
    for (itr =  accept_states.begin(); itr != accept_states.end(); ++itr) {
        dfa->addAcceptState(states_partitions[itr->first], itr->second);
    }

    return dfa;
}

void DFA::print_dfa() {
    if (number_of_states == 0)
        return;
    ofstream file;
    file.open("minimized transition table.txt", std::ofstream::trunc);
    if (file.is_open()) {
        file << "state       ";
//        cout << "state       ";
        for (int i = 0; i < number_of_inputs; i++) {
            char c = i + 32;
            file << " '" << c << "' ";
//            cout << " '" << c << "' ";
        }
        file << endl;
//        cout << endl;

        for (int i = 0; i < number_of_states; i++) {
            if (isAcceptState(i)) {
                if (i < 10) {
                    file << "   *" << i << "     ";
//                    cout << "   *" << i << "     ";
                } else {
                    file << "  *" << i << "     ";
//                    cout << "  *" << i << "     ";
                }
            } else {
                if (i < 10) {
                    file << "    " << i << "     ";
//                    cout << "    " << i << "     ";
                } else {
                    file << "   " << i << "     ";
//                    cout << "   " << i << "     ";
                }
            }
            for (int j = 0; j < number_of_inputs; j++) {
                file << printHelper(table[i][j], 5);
            }
            file << endl;
//            cout << endl;
        }
    }
    file.close();
}

string DFA::printHelper(const int x, const int width) {
    stringstream ss;
    ss << fixed << right;
    ss.fill(' ');        // fill space around displayed #
    ss.width(width);     // set  width around displayed #
    ss << x;
    return ss.str();
}


