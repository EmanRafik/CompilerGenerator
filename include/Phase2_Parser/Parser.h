//
// Created by DELL on 14-Apr-20.
//

#ifndef COMPILERGENERATOR_PARSER_H
#define COMPILERGENERATOR_PARSER_H

#include <Phase1_LexicalAnalyzer/Token.h>
#include <stack>
#include "Parser_table.h"
#include "Symbol.h"

class Parser{
public:
    Parser(Parser_table parserTable, Symbol start_symbol);
    bool parse(Token token);

private:
    Parser_table parser_table;
    stack<Symbol> stack;
};

#endif //COMPILERGENERATOR_PARSER_H
