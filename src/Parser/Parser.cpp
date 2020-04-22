//
// Created by DELL on 14-Apr-20.
//

#include <iostream>
#include <fstream>
#include "Phase2_Parser/Parser_table.h"
#include "Phase2_Parser/Symbol.h"
#include "Phase2_Parser/Parser.h"
#include "Phase2_Parser/Production.h"

Parser::Parser(Parser_table parser_table, Symbol start_symbol) {
    this->parser_table = parser_table;
    stack.push(*new Symbol("$", true));
    stack.push(start_symbol);
    //clear parser output file
    std::ofstream ofs;
    ofs.open("parser_output.txt", std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

bool Parser::parse(Token token) {
    ofstream file;
    file.open("parser_output.txt", std::ios_base::app);
    if (file.is_open()) {
        Symbol current_symbol;
        Production production;
        int current_nonTerminal_index, current_terminal_index;

        while (!stack.top().isTerminal()) {
            current_symbol = stack.top();
            stack.pop();
            current_nonTerminal_index = parser_table.getNonTerminals().at(current_symbol.getSymbol());
            current_terminal_index = parser_table.getTerminals().at(token.getValue());
            production = parser_table.getTable()[current_nonTerminal_index][current_terminal_index];
            if (production.getTo().at(0).getSymbol() == "error") {
                file << "error" << endl;
                cout << "error" << endl;
                stack.push(current_symbol);
                return true;
            } else if (production.getTo().at(0).getSymbol() == "synch") {
                cout << "synch" << endl;
                file << "synch" << endl;
            } else if (production.getTo().at(0).getSymbol() == "epsilon") {
                cout << production.getFrom() << " --> epsilon" << endl;
                file << production.getFrom() << " --> epsilon" << endl;
                continue;
            } else {
                cout << production.getFrom() << " --> ";
                file << production.getFrom() << " --> ";
                for (int i = 0; i < production.getTo().size(); i++) {
                    cout << production.getTo().at(i).getSymbol() << " ";
                    file << production.getTo().at(i).getSymbol() << " ";
                }
                for (int i = production.getTo().size()-1; i >= 0; i--) {
                    stack.push(production.getTo().at(i));
                }
                cout << endl;
                file << endl;
            }

        }

        //here we reached a non-terminal symbol on the stack
        current_symbol = stack.top();
        stack.pop();
        //if matched --> non terminal already removed from stack then continue
        //if non-matched --> if stack is empty compilation failed else matching failed
        if (current_symbol.getSymbol() != token.getValue()) {
            if (stack.empty()) {
                cout << "parsing failed" << endl;
                file << "parsing failed" << endl;
                return false;
            } else {
                cout << "matching " << token.getValue() << " failed" << endl;
                file << "matching " << token.getValue() << " failed" << endl;
            }
        } else {
            cout << "match '" << token.getValue() << "'" << endl;
            file << "match '" << token.getValue() << "'" << endl;
            if (current_symbol.getSymbol() == "$") {
                //parsing done successfully
                cout << "parsing done successfully" << endl;
                file << "parsing done successfully" << endl;
                return false;
            }
        }

    }
    file.close();

    return true;
}
