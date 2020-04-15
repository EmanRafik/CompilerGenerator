#include <iostream>
#include "Phase1_LexicalAnalyzer/DFA.h"
#include "Phase1_LexicalAnalyzer/Lexical_analyzer_generator.h"
#include "Phase1_LexicalAnalyzer/Lexical_analyzer.h"
#include "Phase1_LexicalAnalyzer/NFA.h"
#include <vector>
#include "Phase2_Parser/Production.h"
#include "Phase2_Parser/Symbol.h"


using namespace std;
void printNFA(NFA nfa);
int main()
{
//    Lexical_analyzer_generator *generator = new Lexical_analyzer_generator();
//    generator->read_lexical_rules("rules.txt");
//    generator->generate_lexical_analyzer();
//    Lexical_analyzer *lexical = new Lexical_analyzer();
//    lexical->setDFA(generator->get_minimal_dfa());
//    lexical->execute("input.txt");

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



    return 0;
}
