//
// Created by DELL on 14-Apr-20.
//

#ifndef COMPILERGENERATOR_PARSERTABLE_H
#define COMPILERGENERATOR_PARSERTABLE_H

#include <map>
#include <string>
#include <vector>
#include "Symbol.h"
#include "Production.h"

using namespace std;

class ParserTable {
public:
    ParserTable();

    void addTerminal (Production p);
    void addNonTerminal (Production p);


private:
    Production **table;
    map <string, int> terminals;
    map <string, int> non_terminals;

};

#endif COMPILERGENERATOR_PARSERTABLE_H

