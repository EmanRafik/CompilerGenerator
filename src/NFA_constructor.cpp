#include "NFA_constructor.h"
#include"NFA.h"
#include<string>
#include<vector>
#include<map>
#include<iostream>
#include <cstdio>
#include"Regular_definition.h"
#include <stdio.h>

using namespace std;

static const char epsilon = ' ';

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
            cout << "between bracket " <<expression << "--> no closure" << endl;
            return constructNFA(expression);
        }
        else if (expression.at(n-2) == ')')
        {
            cout << "between bracket " <<expression.substr(1,n-3) << "--> ";
            NFA nfa = constructNFA(expression.substr(1,n-3));
           /* if (expression.at(n-1) == '*')
            {
                cout << "kleene closure " << endl;
                return kleene_closure(nfa);
            }
            else if (expression.at(n-1) == '+')
            {
                cout << "positive closure " << endl;
                return positive_closure(nfa);
            }*/
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
        else if (c == '|' && open ==0)
        {
            string expr1 = expression.substr(0, i);
            string expr2 = expression.substr(i+1, expression.length()-i);
            cout << "OR --> expr1: " << expr1 << "\nexpr2:  " << expr2 << endl;
            NFA nfa1 = constructNFA(expr1);
            NFA nfa2 = constructNFA(expr2);
//            return oring(nfa1, nfa2);
        }
    }
    for (int i = 0; i < n; i++)
    {
        char c = expression.at(i);
        if (c == ' ')
        {
            string expr1 = expression.substr(0, i);
            string expr2 = expression.substr(i+1, expression.length()-i);
            cout << "CONC --> expr1: " << expr1 << "\nexpr2:  " << expr2 << endl;
            NFA nfa1 = constructNFA(expr1);
            NFA nfa2 = constructNFA(expr2);
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
            cout << "Regular Definition --> " << expression << " --> ";
            break;
        }
    }
    /*if (!found)
    {
        cout << "Term --> " << expression << " --> ";
        nfa = termNFA(expression);
    }
    if (closure == 0)
    {
        cout << "kleene closure" << endl;
        return kleene_closure(nfa);
    }
    else if (closure == 1)
    {
        cout << "positive closure" << endl;
        return positive_closure(nfa);
    }
    else*/
    {
        cout << "no closure" << endl;
        return nfa;
    }
}
/*
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
NFA NFA_constructor::oringList(vector<NFA> list, bool combine){
    NFA nfa;
    State newFirst;
    State* newFirstPtr = newFirst.getInstance();
    State newFinal;
    State* newFinalPtr = newFirst.getInstance();
    nfa.setStartState(newFirstPtr);
    map<char,vector<State*>> firstMap;
    vector<State*> firstVector;
    map<State*,map<char,vector<State*>>> newNFAmap;
    //connecting the new start state
    for(NFA nfa:list){
        State* oldFirst = nfa.getStartState();
        firstVector.push_back(oldFirst);
    }
    firstMap.insert(std::pair<char,vector<State*>>(' ',firstVector));
    for(NFA nfa:list){
        std::map<State*,map<char,vector<State*>>>::iterator it1 = nfa.getNFATable().begin();
        State* currentAcceptState = nfa.getAcceptState();
        //inserting NFAs states
        while(it1 != nfa.getNFATable().end()){
            State* currentState = it1->first;
            map<char,vector<State*>> currentMap = it1->second;
            if(currentState == currentAcceptState){
                if(!combine){
                    vector<State*> vec;
                    vec.push_back(newFinalPtr);
                    currentMap.insert(std::pair<char,vector<State*>>(' ',vec));
                }
                else{
                    map<State*,Token> acceptStatesList = nfa.getAcceptStatesList();
                    nfa.addAcceptStateToList(currentState,acceptStatesList.at(currentState));
                }
            }
            newNFAmap.insert(std::pair<State*,map<char,vector<State*>>>(currentState,currentMap));
        }
    }
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

NFA NFA_constructor::oring(NFA original1, NFA original2)
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
                vector<State*> vec;
                vec.push_back(newFinalPtr);
                currentMap.insert(std::pair<char,vector<State*>>(' ',vec));
        }
            newNFAmap.insert(std::pair<State*,map<char,vector<State*>>>(currentState,currentMap));
    }
    while(it2 != original2.getNFATable().end()){
        State* currentState = it2->first;
        map<char,vector<State*>> currentMap = it2->second;
        if(currentState == acceptState2){
                vector<State*> vec;
                vec.push_back(newFinalPtr);
                currentMap.insert(std::pair<char,vector<State*>>(' ',vec));
        }
            newNFAmap.insert(std::pair<State*,map<char,vector<State*>>>(currentState,currentMap));
    }
    //inserting an empty entry for the final state
        nfa.setAcceptState(newFinalPtr);
        vector<State*> finalVector;
        map<char,vector<State*>> finalMap;
        finalMap.insert(std::pair<char,vector<State*>>(' ',finalVector));
        newNFAmap.insert(std::pair<State*,map<char,vector<State*>>>(newFinalPtr,finalMap));
    nfa.setNFATable(newNFAmap);
    return nfa;
}
*/
NFA NFA_constructor::concatinating(NFA original1, NFA original2)
{
    NFA *nfa = new NFA();
    vector<map<char,vector<int>>> newNFAtable;
    std::vector<map<char,vector<int>>>::iterator it1 = original1.getNFATable().begin();
    std::vector<map<char,vector<int>>>::iterator it2 = original2.getNFATable().begin();
    //add states of the first NFA
    int i=0;
    while(i != original1.getAcceptState() && it1 != original1.getNFATable().end()){
        map<char,vector<int>> currentMap = original1.getNFATable()[i];
            newNFAtable.push_back(currentMap);
            it1++;
            i++;
    }
    //add states of the second NFA
    int sizeOfFirstNFA = original1.getNFATable().size() - 1;
    i=0;
    while(i <= original2.getAcceptState() && it2 != original2.getNFATable().end()){
        map<char,vector<int>> currentMap = original2.getNFATable()[i];
        std::map<char,vector<int>>::iterator mapIt = currentMap.begin();
        while(mapIt != currentMap.end() ){
            vector<int> newVec;
            for(int state : mapIt->second){
                if(state == original2.getAcceptState()){
                    nfa->setAcceptState(state + sizeOfFirstNFA);
                }
                newVec.push_back(state + sizeOfFirstNFA);
            }
            currentMap[mapIt->first]=newVec;
            mapIt++;
        }
        newNFAtable.push_back(currentMap);
        it2++;
        i++;
    }

    nfa->setNFATable(newNFAtable);
    return *nfa;
}
NFA NFA_constructor::signleCharNFA(char input){
    NFA *nfa = new NFA();
    nfa->setStartState(0);
    nfa->setAcceptState(1);
    vector<int> vec;
    vec.push_back(1);
    map<char,vector<int>> firstStateMap;
    firstStateMap.insert(std::pair<char,vector<int>>(input,vec));
    vector<map<char,vector<int>>> newNFAtable;
    //insert the start state
    newNFAtable.push_back(firstStateMap);
    vector<int> finalStateVector;
    map<char,vector<int>> finalStateMap;
    finalStateMap.insert(std::pair<char,vector<int>>(' ',finalStateVector));
    //insert empty final state
    newNFAtable.push_back(finalStateMap);
    nfa->setNFATable(newNFAtable);
    return *nfa;
}
/*
NFA NFA_constructor::termNFA(string term)
{
    term = trim(term);
    size_t f = term.find("-");
    if (f != std::string::npos && term.at(f-1)!='\\')
    {
        vector<NFA> NFAList;
        char c1 = term.at(f-1);
        char c2 = term.at(f+1);
        for (char c = c1; c <= c2; c++)
        {
            NFA nfa = signleCharNFA(c);
            NFAList.push_back(nfa);
        }
        return oringList(NFAList, false);
    }
    if (term.length() == 2 && term.at(0) =='\\' && term.at(1) =='L')
    {
        return signleCharNFA(epsilon);
    }
    char c = term.at(0);
    int j = 1;
    if (term.length() > 1 && c =='\\')
    {
        c = term.at(1);
        j = 2;
    }
    NFA nfa = signleCharNFA(c);
    for (int i = j; i < term.length(); i++)
    {
        c = term.at(i);
        if (c == '\\')
        {
            c = term.at(i+1);
            i++;
        }
        NFA nfa2 = signleCharNFA(c);
        nfa = concatinating(nfa, nfa2);
    }
    return nfa;
}
*/
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
