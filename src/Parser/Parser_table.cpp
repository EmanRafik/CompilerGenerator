//
// Created by DELL on 14-Apr-20.
//

#include "Production.h"
#include "Parser_table.h"

Parser_table::Parser_table() {

}

Production **Parser_table::getTable() {
    return table;
}

std::map<string, int> Parser_table::getTerminals() {
    return terminals;
}

std::map<string, int> Parser_table::getNonTerminals() {
    return non_terminals;
}
