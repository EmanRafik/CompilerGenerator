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
int main()
{

/*   Lexical_analyzer_generator *generator = new Lexical_analyzer_generator();
    generator->read_lexical_rules("rules.txt");
    generator->generate_lexical_analyzer();
    Lexical_analyzer *lexical = new Lexical_analyzer();
    lexical->setDFA(generator->get_minimal_dfa());
    lexical->execute("input.txt");

    Symbol *nt1 = new Symbol("E", false);
    Symbol *nt2 = new Symbol("E-", false);
    Symbol *nt3 = new Symbol("T", false);
    Symbol *nt4 = new Symbol("T-", false);
    Symbol *nt5 = new Symbol("F", false);

    Symbol *t1 = new Symbol("epsilon", true);
    Symbol *t2 = new Symbol("synch", true);
    Symbol *t3 = new Symbol("(", true);
    Symbol *t4 = new Symbol(")", true);
    Symbol *t5 = new Symbol("+", true);
    Symbol *t6 = new Symbol("*", true);
    Symbol *t7 = new Symbol("id", true);

    Production *p1 = new Production("E");
    p1->addSymbol(*nt3);
    p1->addSymbol(*nt2);

    Production *p2 = new Production("E-");
    p2->addSymbol(*t5);
    p2->addSymbol(*nt3);
    p2->addSymbol(*nt2);

    Production *p3 = new Production("E-");
    p3->addSymbol(*t1);

    Production *p4 = new Production("T");
    p4->addSymbol(*nt5);
    p4->addSymbol(*nt4);

    Production *p5 = new Production("T-");
    p5->addSymbol(*t6);
    p5->addSymbol(*nt5);
    p5->addSymbol(*nt4);

    Production *p6 = new Production("T-");
    p6->addSymbol(*t1);

    Production *p7 = new Production("F");
    p7->addSymbol(*t3);
    p7->addSymbol(*nt1);
    p7->addSymbol(*t4);

    Production *p8 = new Production("F");
    p8->addSymbol(*t7);

    map <string, int> terminals;
    map <string, int> non_terminals;

    non_terminals.insert(pair<string, int>("E",0));
    non_terminals.insert(pair<string, int>("E-",1));
    non_terminals.insert(pair<string, int>("T",2));
    non_terminals.insert(pair<string, int>("T-",3));
    non_terminals.insert(pair<string, int>("F",4));

    terminals.insert(pair<string, int>("id",0));
    terminals.insert(pair<string, int>("+",1));
    terminals.insert(pair<string, int>("*",2));
    terminals.insert(pair<string, int>("(",3));
    terminals.insert(pair<string, int>(")",4));
    terminals.insert(pair<string, int>("$",5));

    Production *p;
    Parser_table *parserTable = new Parser_table(non_terminals, terminals);
//    parserTable->printTable();

    parserTable->getTable()[0][0] = *p1;
    parserTable->getTable()[0][3] = *p1;
    p = new Production("E");
    p->addSymbol(*new Symbol("synch", true));
    parserTable->getTable()[0][4] = *p;
    parserTable->getTable()[0][5] = *p;

    parserTable->getTable()[1][1] = *p2;
    p = new Production("E-");
    p->addSymbol(*new Symbol("epsilon", true));
    parserTable->getTable()[1][4] = *p;
    parserTable->getTable()[1][5] = *p;

    parserTable->getTable()[2][0] = *p4;
    p = new Production("T");
    p->addSymbol(*new Symbol("synch", true));
    parserTable->getTable()[2][1] = *p;
    parserTable->getTable()[2][3] = *p4;
    parserTable->getTable()[2][4] = *p;
    parserTable->getTable()[2][5] = *p;

    p = new Production("T-");
    p->addSymbol(*new Symbol("epsilon", true));
    parserTable->getTable()[3][1] = *p;
    parserTable->getTable()[3][2] = *p5;
    parserTable->getTable()[3][4] = *p;
    parserTable->getTable()[3][5] = *p;

    parserTable->getTable()[4][0] = *p8;
    p = new Production("F");
    p->addSymbol(*new Symbol("synch", true));
    parserTable->getTable()[4][1] = *p;
    parserTable->getTable()[4][2] = *p;
    parserTable->getTable()[4][3] = *p7;
    parserTable->getTable()[4][4] = *p;
    parserTable->getTable()[4][5] = *p;

    parserTable->printTable();

/*    MyParser *myParser = new MyParser(*parserTable, *nt1);
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
    }*/

   Parser_generator *generator = new Parser_generator();
   generator->generate_parser("cfg.txt").build_table().printTable();

    return 0;
}
