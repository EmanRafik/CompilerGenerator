//
// Created by DELL on 14-Apr-20.
//
#include "Phase2_Parser/Parser_generator.h"
#include <vector>
#include <string>
#include <map>
#include <set>
#include "Symbol.h"
#include "Production.h"
#include <iostream>

using namespace std;


const string epsilon = "epsilon";

Parser_generator::Parser_generator()
{

}

void Parser_generator::read_rules(string file_name)
{

}

void Parser_generator::generate_parser()
{
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

    non_terminals_map.insert(pair<string, int>("E",0));
    non_terminals_map.insert(pair<string, int>("E-",1));
    non_terminals_map.insert(pair<string, int>("T",2));
    non_terminals_map.insert(pair<string, int>("T-",3));
    non_terminals_map.insert(pair<string, int>("F",4));

    vector<Production> v1;
    v1.push_back(*p1);
    non_terminals.insert(pair<int, vector<Production>>(0,v1));

    vector<Production> v2;
    v2.push_back(*p2);
    v2.push_back(*p3);
    non_terminals.insert(pair<int, vector<Production>>(1,v2));

    vector<Production> v3;
    v3.push_back(*p4);
    non_terminals.insert(pair<int, vector<Production>>(2,v3));

    vector<Production> v4;
    v4.push_back(*p5);
    v4.push_back(*p6);
    non_terminals.insert(pair<int, vector<Production>>(3,v4));

    vector<Production> v5;
    v5.push_back(*p7);
    v5.push_back(*p8);
    non_terminals.insert(pair<int, vector<Production>>(4,v5));

    compute_first_and_follow();
}

void Parser_generator::convert_grammar_to_LL1()
{

}

void Parser_generator::compute_first_and_follow()
{
    int non_terminals_count = non_terminals_map.size();
    bool computed[non_terminals_count];
    for (int i = 0; i < non_terminals_count; i++)
    {
        computed[i] = false;
    }
    map<int, vector<Production>>::iterator it = non_terminals.begin();
    while(it != non_terminals.end())
    {
        int non_terminal = it->first;
        if (!computed[non_terminal])
        {
            vector<Production> productions = it->second;
            non_terminal_first(non_terminal, productions, computed);
        }
        it++;
    }

//    map<int, set<string>>::iterator i=first_set.begin();
//    while (i != first_set.end())
//    {
//        cout << i->first << "--> ";
//        set<string> test = i->second;
//        set<string>::iterator ii = test.begin();
//        while (ii != test.end())
//        {
//            cout << *ii << " ";
//            ii++;
//        }
//        cout << endl;
//        i++;
//    }
}

set<string> Parser_generator::non_terminal_first(int non_terminal, vector<Production> productions, bool computed[])
{
    set<string> first;
    for (unsigned int i = 0; i < productions.size(); i++)
    {
        Production production = productions[i];
        Symbol first_symbol = production.getTo()[0];
        if (first_symbol.isTerminal())
        {
            first.insert(first_symbol.getSymbol());
        }
        else
        {
            vector<Symbol> to_vector = production.getTo();
            bool add_epsilon = true;
            for (unsigned int i = 0; i < to_vector.size(); i++)
            {
                Symbol symbol = to_vector[i];
                if (symbol.isTerminal())
                {
                    first.insert(symbol.getSymbol());
                    add_epsilon = false;
                    break;
                }
                map<string,int>::iterator it;
                it = non_terminals_map.find(symbol.getSymbol());
                if (it != non_terminals_map.end())
                {
                    int mapping = it->second;
                    if (computed[i])
                    {
                        map<int, set<string>>::iterator it2 = first_set.find(mapping);
                        if (it2 != first_set.end())
                        {
                            set<string> s = it2->second;
                            first.insert(s.begin(), s.end());
                            if (s.find(epsilon) == s.end())
                            {
                                add_epsilon = false;
                                break;
                            }
                        }
                    }
                    else
                    {
                        map<int, vector<Production>>::iterator it2 = non_terminals.find(mapping);
                        if (it2 != non_terminals.end())
                        {
                            vector<Production> p = it2->second;
                            set<string> s = non_terminal_first(mapping, p, computed);
                            first.insert(s.begin(), s.end());
                            if (s.find(epsilon) == s.end())
                            {
                                add_epsilon = false;
                                break;
                            }
                        }
                    }
                }
            }
            if (add_epsilon)
            {
                first.insert(epsilon);
            }
        }
    }
    first_set.insert(pair<int, set<string>>(non_terminal, first));
    computed[non_terminal] = true;
    return first;
}

void Parser_generator::construct_parser_table()
{

}
