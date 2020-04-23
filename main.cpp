#include "Phase1_LexicalAnalyzer/DFA.h"
#include"Phase1_LexicalAnalyzer/Lexical_analyzer_generator.h"
#include"Phase1_LexicalAnalyzer/Lexical_analyzer.h"
#include <vector>
#include "Phase2_Parser/Parser.h"
#include "Phase2_Parser/Parser_table.h"
#include "Symbol.h"
#include "Parser_generator.h"


using namespace std;
int main() {
    Lexical_analyzer_generator *generator = new Lexical_analyzer_generator();
    generator->read_lexical_rules("rules.txt");
    generator->generate_lexical_analyzer();
    Lexical_analyzer *lexical = new Lexical_analyzer();
    lexical->setDFA(generator->get_minimal_dfa());
    lexical->execute("input.txt");

    Parser_generator *parserGenerator = new Parser_generator();
    Parser_table parserTable = parserGenerator->generate_parser("cfg.txt");
    bool ambig = parserTable.build_table();
    if(!ambig){
        return 0;
    }
    parserTable.printTable();

    Parser *myParser = new Parser(parserTable, parserGenerator->getFirstNonTerminal());
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
