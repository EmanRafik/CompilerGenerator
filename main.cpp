#include <iostream>
#include "Phase1_LexicalAnalyzer/DFA.h"
#include"Phase1_LexicalAnalyzer/Lexical_analyzer_generator.h"
#include"Phase1_LexicalAnalyzer/Lexical_analyzer.h"
#include "Phase1_LexicalAnalyzer/NFA.h"
#include <vector>
#include "Phase2_Parser/MyParser.h"
#include "Phase2_Parser/Parser_table.h"
#include "Production.h"
#include "Symbol.h"
#include "Parser_generator.h"


using namespace std;
void printNFA(NFA nfa);
int main() {

    Lexical_analyzer_generator *generator = new Lexical_analyzer_generator();
    generator->read_lexical_rules("rules.txt");
    generator->generate_lexical_analyzer();
    Lexical_analyzer *lexical = new Lexical_analyzer();
    lexical->setDFA(generator->get_minimal_dfa());
    lexical->execute("input.txt");

    Parser_generator *parserGenerator = new Parser_generator();
    Parser_table parserTable = parserGenerator->generate_parser("cfg.txt");
    parserTable.build_table().printTable();

    MyParser *myParser = new MyParser(parserTable.build_table(), parserGenerator->getFirstNonTerminal());

    Token t = lexical->getNextToken();
    bool error_flag = false;
    while (t.getValue() != "$") {
        if (myParser->parse(t)) {
            t = lexical->getNextToken();
        } else {
            error_flag = true;
            break;
        }
    }
    while (!error_flag) {
        error_flag = !myParser->parse(t);
    }

    return 0;
}
