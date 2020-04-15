//
// Created by DELL on 14-Apr-20.
//

#ifndef COMPILERGENERATOR_PARSER_TABLE_H
#define COMPILERGENERATOR_PARSER_TABLE_H

#include <map>
#include <string>
#include <vector>
#include "Symbol.h"
#include "Production.h"

using namespace std;

class Parser_table {
public:
    Parser_table();
    void addTerminal (Production p);
    void addNonTerminal (Production p);
    Production **getTable();
    map<string, int> getTerminals();
    map<string, int> getNonTerminals();

private:
    Production **table;
    map <string, int> terminals;

private:
    map <string, int> non_terminals;

};

#endif //COMPILERGENERATOR_PARSER_TABLE_H

