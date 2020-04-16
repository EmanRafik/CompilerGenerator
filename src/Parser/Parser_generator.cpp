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

}

void Parser_generator::convert_grammar_to_LL1()
{

}

void Parser_generator::compute_first_and_follow()
{
    int non_terminals_count = non_terminals_map.size();

    /**compute first**/
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

    /**compute follow**/
    for (int i = 0; i < non_terminals_count; i++)
    {
        computed[i] = false;
    }
    map<string,int>::iterator it2 = non_terminals_map.begin();
    while (it2 != non_terminals_map.end())
    {
        string non_terminal = it2->first;
        int non_terminal_mapping = it2->second;
        if (!computed[non_terminal_mapping])
        {
            non_terminal_follow(non_terminal, non_terminal_mapping, computed);
        }
        it2++;
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
                        map<int, set<string>>::iterator it2 = first_sets.find(mapping);
                        if (it2 != first_sets.end())
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
    first_sets.insert(pair<int, set<string>>(non_terminal, first));
    computed[non_terminal] = true;
    return first;
}

set<string> Parser_generator::non_terminal_follow(string non_terminal, int non_terminal_mapping, bool computed[])
{
    set<string> follow;
    if (non_terminal_mapping == 0)
    {
        follow.insert("$");
    }
    map<int, vector<Production>>::iterator it = non_terminals.begin();
    while (it != non_terminals.end())
    {
        vector<Production> productions = it->second;
        for (unsigned int i = 0; i < productions.size(); i++)
        {
            Production production = productions[i];
            vector<Symbol> symbols = production.getTo();
            for (unsigned int j = 0; j < symbols.size() - 1; j++)
            {
                if (symbols[j].getSymbol() == non_terminal)
                {
                    unsigned int k = j + 1;
                    while (k < symbols.size())
                    {
                        if (symbols[k].isTerminal())
                        {
                            follow.insert(symbols[k].getSymbol());
                            break;
                        }
                        map<string, int>::iterator i = non_terminals_map.find(symbols[k].getSymbol());
                        if (i != non_terminals_map.end())
                        {
                            int mapping = i->second;
                            map<int,set<string>>::iterator i2 = first_sets.find(mapping);
                            if (i2 != first_sets.end())
                            {
                                set<string> first = i2->second;
                                follow.insert(first.begin(), first.end());
                                set<string>::iterator follow_it = follow.find(epsilon);
                                if (follow_it != follow.end())
                                {
                                    follow.erase(follow_it);
                                    k++;
                                }
                                else
                                {
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            if (non_terminal_mapping != it->first)
            {
                for (unsigned int j = symbols.size() - 1; j >= 0; j--)
                {
                    Symbol symbol = symbols[j];
                    if (symbol.isTerminal())
                    {
                        break;
                    }
                    if (symbol.getSymbol() == non_terminal)
                    {
                        set<string> s;
                        if (computed[it->first])
                        {
                            map<int, set<string>>::iterator i2 = follow_sets.find(it->first);
                            if (i2 != follow_sets.end())
                            {
                                s = i2->second;
                            }
                        }
                        else
                        {
                            s = non_terminal_follow(production.getFrom(), it->first, computed);
                        }
                        follow.insert(s.begin(), s.end());
                        break;
                    }
                    map<string, int>::iterator i = non_terminals_map.find(symbol.getSymbol());
                    if (i != non_terminals_map.end())
                    {
                        int mapping = i->second;
                        map<int, set<string>>::iterator i2 = first_sets.find(mapping);
                        if (i2 != first_sets.end())
                        {
                            set<string> first = i2->second;
                            if (first.find(epsilon) == first.end())
                            {
                                break;
                            }
                        }
                    }
                }
            }
        }
        it++;
    }
    follow_sets.insert(pair<int,set<string>>(non_terminal_mapping, follow));
    computed[non_terminal_mapping] = true;
    return follow;
}

void Parser_generator::construct_parser_table()
{

}
