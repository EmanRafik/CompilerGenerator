//
// Created by DELL on 14-Apr-20.
//

#ifndef COMPILERGENERATOR_PARSER_GENERATOR_H
#define COMPILERGENERATOR_PARSER_GENERATOR_H

#include<vector>
#include<string>
#include<map>
#include<set>
#include"Phase2_Parser/Production.h"

using namespace std;

class Parser_generator
{
    public:
        Parser_generator();
        void read_rules(string file_name);
        void generate_parser();
        void read_cfg(string file_name);
        void convert_grammar_to_LL1();
    private:
        string handleLHS(string s, int i);
        void handleRHS(string s, string from);
        void handleToken(string s, string from);
        void leftRecursion(set<string> &updated, set<string> &epsilonSet, Symbol symbol, int i);
        void compute_first_and_follow();
        set<string> non_terminal_first(int non_terminal, vector<Production> productions, bool computed[]);
        set<string> non_terminal_follow(string non_terminal, int non_terminal_mapping, bool computed[]);
        void construct_parser_table();
        vector<Production> grammar;
        set<string> terminals;
        map<string, int> non_terminals_map;
        map<int, vector<Production>> non_terminals;
        map<int,set<string>> first_sets;
        map<int, set<string>> follow_sets;
        map<string, vector<Production>> recursionMap;

};
#endif //COMPILERGENERATOR_PARSER_GENERATOR_H
