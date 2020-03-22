#include "Lexical_analyzer_generator.h"
#include <map>
#include "NFA.h"
#include <vector>
Lexical_analyzer_generator::Lexical_analyzer_generator()
{
    //ctor
}

Lexical_analyzer_generator::~Lexical_analyzer_generator()
{
    //dtor
}

vector<NFA> Lexical_analyzer_generator:: getNFAList(){
    return NFAlist;
}
void Lexical_analyzer_generator:: setNFAList(vector<NFA> list) {
    this->NFAlist = list;
}
void Lexical_analyzer_generator:: addNFA(NFA nfa){
    vector<NFA> list = getNFAList();
    list.push_back(nfa);
    setNFAList(list);
}
NFA Lexical_analyzer_generator::combineNFA(vector<NFA> list){
    
}
