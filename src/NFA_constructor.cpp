#include "NFA_constructor.h"
#include"NFA.h"
#include<string>
#include<vector>
#include<map>
#include<iostream>
#include"Regular_definition.h"

using namespace std;

NFA_constructor::NFA_constructor()
{
    //ctor
}

NFA_constructor::~NFA_constructor()
{
    //dtor
}


void NFA_constructor::setRegular_definitions(vector<Regular_definition> regular_definitions)
{
    this->regular_definitions = regular_definitions;
}


NFA NFA_constructor::constructNFA(string expression)
{
    expression = trim(expression);
    int n = expression.length();
    if (expression.at(0) == '(')
    {
        if (expression.at(n-1) == ')')
        {
            expression = expression.substr(1, n-2);
            return constructNFA(expression);
        }
        else if (expression.at(n-2) == ')')
        {
            NFA nfa = constructNFA(expression.substr(1,n-3));
            if (expression.at(n-1) == '*')
            {
                return kleene_closure(nfa);
            }
            else if (expression.at(n-1) == '+')
            {
                return positive_closure(nfa);
            }
        }
    }
    int open = 0;
    for (int i = 0; i < n; i++)
    {
        char c = expression.at(i);
        if (c == '(')
        {
            open++;
        }
        else if (c == ')')
        {
            open--;
        }
        else if (c == '|')
        {
            if (open == 0)
            {
                NFA nfa1 = constructNFA(expression.substr(0, i-1));
                NFA nfa2 = constructNFA(expression.substr(i+1, expression.length()-i));
                return oring(nfa1, nfa2,false);
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        char c = expression.at(i);
        if (c == ' ')
        {
            NFA nfa1 = constructNFA(expression.substr(0, i-1));
            NFA nfa2 = constructNFA(expression.substr(i+1, expression.length()-i));
            return concatinating(nfa1, nfa2);
        }
    }
    int closure = -1;
    if (expression.at(n-1) == '*')
    {
        closure = 0;
        expression = expression.substr(0,n-1);
    }
    else if (expression.at(n-1) == '+')
    {
        closure = 1;
        expression = expression.substr(0,n-1);
    }
    bool found = false;
    NFA nfa;
    for (int i = 0; i < regular_definitions.size(); i++)
    {
        if (regular_definitions[i].getName() == expression)
        {
            nfa = regular_definitions[i].getNFA();
            found = true;
            break;
        }
    }
    if (!found)
    {
        nfa = termNFA(expression);
    }
    if (closure == 0)
    {
        return kleene_closure(nfa);
    }
    else if (closure == 1)
    {
        return positive_closure(nfa);
    }
    else
    {
        return nfa;
    }
}

NFA NFA_constructor::kleene_closure(NFA original_nfa)
{
    NFA nfa;
    State* originalStartState = original_nfa.getStartState();
    State* originalAcceptState = original_nfa.getAcceptState();
    State newFirst;
    State* newFirstPtr = newFirst.getInstance();
    nfa.setStartState(newFirstPtr);
    State newFinal;
    State* newFinalPtr=newFinal.getInstance();
    nfa.setAcceptState(newFinalPtr);
    map<char,vector<State*>> firstMap;
    vector<State*> firstVector;
    firstVector.push_back(originalStartState);
    firstVector.push_back(newFinalPtr);
    firstMap.insert(std::pair<char,vector<State*>>(' ',firstVector));
    map<State*,map<char,vector<State*>>> newNFAmap;
    newNFAmap.insert(std::pair<State*,map<char,vector<State*>>>(newFirstPtr,firstMap));
    std::map<State*,map<char,vector<State*>>>::iterator it1 = original_nfa.getNFATable().begin();

    //inserting NFAs states
    while(it1 != original_nfa.getNFATable().end()){
        State* currentState = it1->first;
        map<char,vector<State*>> currentMap = it1->second;
        if(currentState == originalAcceptState){
            vector<State*> vec;
            vec.push_back(newFinalPtr);
            vec.push_back(originalStartState);
            currentMap.insert(std::pair<char,vector<State*>>(' ',vec));
        }
            newNFAmap.insert(std::pair<State*,map<char,vector<State*>>>(currentState,currentMap));
    }

    //inserting an empty entry for the final state
    vector<State*> finalVector;
    map<char,vector<State*>> finalMap;
    finalMap.insert(std::pair<char,vector<State*>>(' ',finalVector));
    newNFAmap.insert(std::pair<State*,map<char,vector<State*>>>(newFinalPtr,finalMap));
    nfa.setNFATable(newNFAmap);
    return nfa;
}

NFA NFA_constructor::positive_closure(NFA original_nfa)
{
    NFA nfa;
    State* originalStartState = original_nfa.getStartState();
    State* originalAcceptState = original_nfa.getAcceptState();
    nfa.setStartState(originalStartState);
    State newFinal;
    State* newFinalPtr=newFinal.getInstance();
    nfa.setAcceptState(newFinalPtr);
    map<State*,map<char,vector<State*>>> newNFAmap;
    std::map<State*,map<char,vector<State*>>>::iterator it1 = original_nfa.getNFATable().begin();
    while(it1 != original_nfa.getNFATable().end()){
        State* currentState = it1->first;
        map<char,vector<State*>> currentMap = it1->second;
        if(currentState == originalAcceptState){
            vector<State*> vec;
            vec.push_back(newFinalPtr);
            vec.push_back(originalStartState);
            currentMap.insert(std::pair<char,vector<State*>>(' ',vec));
        }
        newNFAmap.insert(std::pair<State*,map<char,vector<State*>>>(currentState,currentMap));

        //inserting an empty entry for the final state
        vector<State*> finalVector;
        map<char,vector<State*>> finalMap;
        finalMap.insert(std::pair<char,vector<State*>>(' ',finalVector));
        newNFAmap.insert(std::pair<State*,map<char,vector<State*>>>(newFinalPtr,finalMap));
        nfa.setNFATable(newNFAmap);
        return nfa;
    }
}

NFA NFA_constructor::oring(NFA original1, NFA original2,bool combine)
{
    NFA nfa;
    State* startState1 = original1.getStartState();
    State* acceptState1 = original1.getAcceptState();
    State* startState2 = original2.getStartState();
    State* acceptState2 = original2.getAcceptState();
    State newFirst;
    State* newFirstPtr = newFirst.getInstance();
    nfa.setStartState(newFirstPtr);
    State newFinal;
    State* newFinalPtr=newFinal.getInstance();

    //connecting new start state to the 2 start states of the NFAs
    map<char,vector<State*>> firstMap;
    vector<State*> firstVector;
    firstVector.push_back(startState1);
    firstVector.push_back(startState2);
    firstMap.insert(std::pair<char,vector<State*>>(' ',firstVector));

    //inserting the new state into the new NFA table
    map<State*,map<char,vector<State*>>> newNFAmap;
    newNFAmap.insert(std::pair<State*,map<char,vector<State*>>>(newFirstPtr,firstMap));
    std::map<State*,map<char,vector<State*>>>::iterator it1 = original1.getNFATable().begin();
    std::map<State*,map<char,vector<State*>>>::iterator it2 = original2.getNFATable().begin();
    //inserting NFAs states
    while(it1 != original1.getNFATable().end()){
        State* currentState = it1->first;
        map<char,vector<State*>> currentMap = it1->second;
        if(currentState == acceptState1){
            if(!combine){
                vector<State*> vec;
                vec.push_back(newFinalPtr);
                currentMap.insert(std::pair<char,vector<State*>>(' ',vec));
            }
            else{
                //add state pointer and token to nfa->acceptStatesList
            }
        }
        if(currentState != startState1 ){
            newNFAmap.insert(std::pair<State*,map<char,vector<State*>>>(currentState,currentMap));
        }
    }
    while(it2 != original2.getNFATable().end()){
        State* currentState = it2->first;
        map<char,vector<State*>> currentMap = it2->second;
        if(currentState == acceptState2){
            if(!combine){
                vector<State*> vec;
                vec.push_back(newFinalPtr);
                currentMap.insert(std::pair<char,vector<State*>>(' ',vec));
            }
            else{
                //add state pointer and token to nfa->acceptStatesList
            }
        }
        if(currentState != startState2 ){
            newNFAmap.insert(std::pair<State*,map<char,vector<State*>>>(currentState,currentMap));
        }
    }
    //inserting an empty entry for the final state
    if(!combine){
        nfa.setAcceptState(newFinalPtr);
        vector<State*> finalVector;
        map<char,vector<State*>> finalMap;
        finalMap.insert(std::pair<char,vector<State*>>(' ',finalVector));
        newNFAmap.insert(std::pair<State*,map<char,vector<State*>>>(newFinalPtr,finalMap));
    }
    nfa.setNFATable(newNFAmap);
    return nfa;
}

NFA NFA_constructor::concatinating(NFA original1, NFA original2)
{
    NFA nfa;
    State* startState1 = original1.getStartState();
    State* acceptState1 = original1.getAcceptState();
    State* startState2 = original2.getStartState();
    State* acceptState2 = original2.getAcceptState();
    nfa.setStartState(startState1);
    nfa.setAcceptState(acceptState2);
    map<State*,map<char,vector<State*>>> newNFAmap;
    std::map<State*,map<char,vector<State*>>>::iterator it1 = original1.getNFATable().begin();
    std::map<State*,map<char,vector<State*>>>::iterator it2 = original2.getNFATable().begin();
    //add states of the first NFA
    while(it1 != original1.getNFATable().end()){
        State* currentState = it1->first;
        map<char,vector<State*>> currentMap = it1->second;
        //connect the 2 NFAs
        if(currentState == acceptState1){
            //get the states that are connected to the beginning of the second NFA and connect them to the end
            //of the first NFA
            map<char,vector<State*>> nextMap = original2.getNFATable().at(startState2);
            std::map<char,vector<State*>>::iterator nextIt = nextMap.begin();
            while(nextIt != nextMap.end()){
                currentMap.insert(std::pair<char,vector<State*>>(nextIt->first,nextIt->second));
            }
        }
            newNFAmap.insert(std::pair<State*,map<char,vector<State*>>>(currentState,currentMap));
    }
    //add states of the second NFA
    while(it2 != original2.getNFATable().end()){
        State* currentState = it2->first;
        map<char,vector<State*>> currentMap = it2->second;
        if(currentState != startState2){
            newNFAmap.insert(std::pair<State*,map<char,vector<State*>>>(currentState,currentMap));
        }
    }
    nfa.setNFATable(newNFAmap);
    return nfa;
}

NFA NFA_constructor::termNFA(string term)
{
    size_t f = term.find("(");
    if (f == std::string::npos)
        //handleBrackets(term);
    vector<map<char, vector<int>>> table;
    for (int i = 0; i < term.length(); i++)
    {
        if (term.at(i) != '\\')
        {
            vector<int> v;
            v.push_back(i+1);
            map<char, vector<int>> m;
            m.insert(pair<char, vector<int>>(term.at(i), v));
            //table.push_back(m);
        }
    }
}

string NFA_constructor::trim(string s)
{
    while (s.at(0) == ' ')
    {
        s = s.substr(1);
    }
    while (s.at(s.length()-1)== ' ')
    {
        s = s.substr(0, s.length()-1);
    }
    return s;
}
