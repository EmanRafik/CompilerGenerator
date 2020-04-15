//
// Created by DELL on 14-Apr-20.
//
#include "Parser_generator.h"
#include<vector>
#include<string>
#include<map>
#include<set>
#include"Production.h"

using namespace std;

Parser_generator::Parser_generator()
{

}

void Parser_generator::read_rules(string file_name)
{

}

void Parser_generator::generate_parser()
{

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
                            if (s.find("") == s.end())
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
                        }
                    }
                }
            }
            if (add_epsilon)
            {
                first.insert("");
            }
        }
    }
    first_set.insert(make_pair(non_terminal, first));
    computed[non_terminal] = true;
    return first;
}

void Parser_generator::construct_parser_table()
{

}
