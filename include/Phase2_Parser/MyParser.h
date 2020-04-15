//
// Created by DELL on 14-Apr-20.
//

#ifndef COMPILERGENERATOR_MYPARSER_H
#define COMPILERGENERATOR_MYPARSER_H

#include <Phase1_LexicalAnalyzer/Token.h>
#include <stack>
#include "Parser_table.h"
#include "Symbol.h"

class MyParser{
public:
    MyParser(Parser_table parserTable, Symbol start_symbol);
    bool parse(Token token);

private:
    Parser_table parser_table;
    Symbol start_symbol;
    stack<Symbol> stack;
};

#endif //COMPILERGENERATOR_MYPARSER_H
