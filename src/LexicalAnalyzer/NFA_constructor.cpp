#include "Phase1_LexicalAnalyzer/NFA_constructor.h"
#include"Phase1_LexicalAnalyzer/NFA.h"
#include<string>
#include<vector>
#include<map>
#include<iostream>
#include <cstdio>
#include"Phase1_LexicalAnalyzer/Regular_definition.h"
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
    ///check if the expression is enclosed between brackets
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
            ///kleene closured expression
            if (expression.at(n-1) == '*')
            {
                return kleene_closure(nfa);
            }
            ///positive closured expression
            else if (expression.at(n-1) == '+')
            {
                return positive_closure(nfa);
            }
        }
    }
    ///Search for or operation, neglecting operators enclosed between brackets
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
            NFA nfa1 = constructNFA(expr1);
            NFA nfa2 = constructNFA(expr2);
            return oring(nfa1, nfa2);
        }
    }
    ///Search for concatenate operation
    for (int i = 0; i < n; i++)
    {
        char c = expression.at(i);
        if (c == ' ')
        {
            string expr1 = expression.substr(0, i);
            string expr2 = expression.substr(i+1, expression.length()-i);
            NFA nfa1 = constructNFA(expr1);
            NFA nfa2 = constructNFA(expr2);
            return concatinating(nfa1, nfa2);
        }
    }
    int closure = -1;
    ///kleene closured expression
    if (expression.length() > 1 && expression.at(n-1) == '*' && expression.at(n-2) != '\\')
    {
        closure = 0;
        expression = expression.substr(0,n-1);
    }
    ///positive closured expression
    else if (expression.length() > 1 && expression.at(n-1) == '+' && expression.at(n-2) != '\\')
    {
        closure = 1;
        expression = expression.substr(0,n-1);
    }
    bool found = false;
    NFA nfa;
    ///check if term is regular definition
    for (int i = 0; i < regular_definitions.size(); i++)
    {
        if (regular_definitions[i].getName() == expression)
        {
            ///get NFA of regular definition
            nfa = regular_definitions[i].getNFA(regular_definitions);
            found = true;
            break;
        }
    }
    if (!found)
    {
        ///construct NFA for the term
        nfa = termNFA(expression);
    }
    ///adjust constructed NFA to term closure
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
    NFA *nfa = new NFA();
    vector<map<vector<char>,vector<int>>> newNFAtable;
    map<vector<char>,vector<int>> firstMap;
    vector<int> firstVector;
    vector<char> inputVector;
    inputVector.push_back(' ');
    firstVector.push_back(1);
    firstVector.push_back(original_nfa.getNFATable().size()+1);
    firstMap.insert(std::pair<vector<char>,vector<int>>(inputVector,firstVector));
    newNFAtable.push_back(firstMap);
    std::vector<map<vector<char>,vector<int>>>::iterator it1 = nfa->getNFATable().begin();

    //inserting NFAs states
    int i=0;
    while(i <= original_nfa.getAcceptState() && it1 != original_nfa.getNFATable().end())
    {
        map<vector<char>,vector<int>> currentMap = original_nfa.getNFATable()[i];
        std::map<vector<char>,vector<int>>::iterator mapIt = currentMap.begin();
        while(mapIt != currentMap.end() )
        {
            vector<int> newVec;
            if(i == original_nfa.getAcceptState())
            {
                newVec.push_back(original_nfa.getNFATable().size()+1);
                newVec.push_back(1);
            }
            else
            {
                for(int state : mapIt->second)
                {
                    newVec.push_back(state + 1);
                }
            }
            currentMap[mapIt->first] = newVec;
            mapIt++;
        }
        newNFAtable.push_back(currentMap);
        it1++;
        i++;
    }

    //inserting an empty entry for the final state
    nfa->setAcceptState(original_nfa.getNFATable().size()+1);
    vector<int> finalStateVector;
    map<vector<char>,vector<int>> finalStateMap;
    finalStateMap.insert(std::pair<vector<char>,vector<int>>(inputVector,finalStateVector));
    newNFAtable.push_back(finalStateMap);
    nfa->setNFATable(newNFAtable);
    return *nfa;
}

NFA NFA_constructor::positive_closure(NFA original_nfa)
{
    NFA *nfa = new NFA();
    vector<map<vector<char>,vector<int>>> newNFAtable;
    std::vector<map<vector<char>,vector<int>>>::iterator it1 = nfa->getNFATable().begin();
    //inserting NFAs states
    int i=0;
    while(i <= original_nfa.getAcceptState() && it1 != original_nfa.getNFATable().end())
    {
        map<vector<char>,vector<int>> currentMap = original_nfa.getNFATable()[i];
        std::map<vector<char>,vector<int>>::iterator mapIt = currentMap.begin();
        while(mapIt != currentMap.end() )
        {
            vector<int> newVec;
            if(i == original_nfa.getAcceptState())
            {
                newVec.push_back(original_nfa.getNFATable().size());
                newVec.push_back(0);
            }
            else
            {
                for(int state : mapIt->second)
                {
                    newVec.push_back(state);
                }
            }
            currentMap[mapIt->first] = newVec;
            mapIt++;
        }
        newNFAtable.push_back(currentMap);
        it1++;
        i++;
    }

    //inserting an empty entry for the final state
    nfa->setAcceptState(original_nfa.getNFATable().size());
    vector<int> finalStateVector;
    map<vector<char>,vector<int>> finalStateMap;
    vector<char> inputVector;
    inputVector.push_back(' ');
    finalStateMap.insert(std::pair<vector<char>,vector<int>>(inputVector,finalStateVector));
    newNFAtable.push_back(finalStateMap);
    nfa->setNFATable(newNFAtable);
    return *nfa;
}

NFA NFA_constructor::oringList(vector<NFA> list, bool combine)
{
    NFA *newNFA = new NFA();
    vector<map<vector<char>,vector<int>>> newNFAtable;
    map<vector<char>,vector<int>> firstMap;
    vector<int> firstVector;
    vector<char> inputVector;
    inputVector.push_back(' ');
    //connecting the new start state
    int i = 1;
    int lastState = 1;
    for(NFA nfa:list)
    {
        firstVector.push_back(i);
        i += nfa.getNFATable().size();
        lastState += nfa.getNFATable().size();
    }
    int lastIncrement = 1;
    firstMap.insert(std::pair<vector<char>,vector<int>>(inputVector,firstVector));
    newNFAtable.push_back(firstMap);
    for(NFA nfa:list)
    {
        int i=0;
        std::vector<map<vector<char>,vector<int>>>::iterator it1 = nfa.getNFATable().begin();
        int currentAcceptState = nfa.getAcceptState();
        //inserting NFAs states
        while(i <= nfa.getAcceptState() && it1 != nfa.getNFATable().end())
        {
            map<vector<char>,vector<int>> currentMap = nfa.getNFATable()[i];
            std::map<vector<char>,vector<int>>::iterator mapIt = currentMap.begin();
            while(mapIt != currentMap.end() )
            {
                vector<int> newVec;
                if(i == currentAcceptState)
                {
                    if(!combine)
                    {
                        newVec.push_back(lastState);
                    }
                    else
                    {
                        map<int,Token> acceptStatesList = nfa.getAcceptStatesList();
                        map<int, Token > nfaAcceptList ;
                        if(!newNFA->getAcceptStatesList().empty())
                        {
                            nfaAcceptList = newNFA->getAcceptStatesList();
                        }
                        nfaAcceptList.insert(pair<int,Token> (i + lastIncrement, acceptStatesList[currentAcceptState]));
                        newNFA->setAcceptStatesList(nfaAcceptList);
                    }
                }
                else
                {
                    for(int state : mapIt->second)
                    {
                        newVec.push_back(state + lastIncrement);
                    }
                }
                currentMap[mapIt->first] = newVec;
                mapIt++;
            }
            newNFAtable.push_back(currentMap);
            it1++;
            i++;
        }
        lastIncrement += nfa.getNFATable().size();
    }
    if(!combine)
    {
        newNFA->setAcceptState(lastState);
        vector<int> finalStateVector;
        map<vector<char>,vector<int>> finalStateMap;
        finalStateMap.insert(std::pair<vector<char>,vector<int>>(inputVector,finalStateVector));
        newNFAtable.push_back(finalStateMap);
    }
    newNFA->setNFATable(newNFAtable);
    return *newNFA;
}

NFA NFA_constructor::oring(NFA original1, NFA original2)
{
    NFA *nfa = new NFA();
    vector<map<vector<char>,vector<int>>> newNFAtable;
    //connecting new start state to the 2 start states of the NFAs
    map<vector<char>,vector<int>> firstMap;
    vector<int> firstVector;
    vector<char> inputVector;
    inputVector.push_back(' ');
    int firstVectorSize = original1.getNFATable().size();
    int secondVectorSize = original2.getNFATable().size();
    nfa->setAcceptState(firstVectorSize+secondVectorSize+1);
    firstVector.push_back(1);
    firstVector.push_back(firstVectorSize + 1);
    firstMap.insert(std::pair<vector<char>,vector<int>>(inputVector,firstVector));
    //inserting the new state into the new NFA table
    newNFAtable.push_back(firstMap);
    std::vector<map<vector<char>,vector<int>>>::iterator it1 = original1.getNFATable().begin();
    std::vector<map<vector<char>,vector<int>>>::iterator it2 = original2.getNFATable().begin();
    //inserting first NFA states
    int i=0;
    while(i <= original1.getAcceptState() && it1 != original1.getNFATable().end())
    {
        map<vector<char>,vector<int>> currentMap = original1.getNFATable()[i];
        std::map<vector<char>,vector<int>>::iterator mapIt = currentMap.begin();
        while(mapIt != currentMap.end() )
        {
            vector<int> newVec;
            if(i == firstVectorSize - 1)
            {
                newVec.push_back(firstVectorSize + secondVectorSize + 1);
            }
            else
            {
                for(int state : mapIt->second)
                {
                    newVec.push_back(state + 1);
                }
            }
            currentMap[mapIt->first] = newVec;
            mapIt++;
        }
        newNFAtable.push_back(currentMap);
        it1++;
        i++;
    }
    //inserting second NFA states
    i=0;
    while(i <= original2.getAcceptState() && it2 != original2.getNFATable().end())
    {
        map<vector<char>,vector<int>> currentMap = original2.getNFATable()[i];
        std::map<vector<char>,vector<int>>::iterator mapIt = currentMap.begin();
        while(mapIt != currentMap.end() )
        {
            vector<int> newVec;
            if(i == secondVectorSize - 1)
            {
                newVec.push_back(firstVectorSize + secondVectorSize + 1);
            }
            for(int state : mapIt->second)
            {
                newVec.push_back(state + firstVectorSize + 1);
            }
            currentMap[mapIt->first] = newVec;
            mapIt++;
        }
        newNFAtable.push_back(currentMap);
        it2++;
        i++;
    }
    //inserting an empty entry for the final state
    vector<int> finalStateVector;
    map<vector<char>,vector<int>> finalStateMap;
    finalStateMap.insert(std::pair<vector<char>,vector<int>>(inputVector,finalStateVector));
    newNFAtable.push_back(finalStateMap);
    nfa->setNFATable(newNFAtable);
    return *nfa;
}

NFA NFA_constructor::concatinating(NFA original1, NFA original2)
{
    NFA *nfa = new NFA();
    vector<map<vector<char>,vector<int>>> newNFAtable;
    std::vector<map<vector<char>,vector<int>>>::iterator it1 = original1.getNFATable().begin();
    std::vector<map<vector<char>,vector<int>>>::iterator it2 = original2.getNFATable().begin();
    //add states of the first NFA
    int i=0;
    while(i != original1.getAcceptState() && it1 != original1.getNFATable().end())
    {
        map<vector<char>,vector<int>> currentMap = original1.getNFATable()[i];
        newNFAtable.push_back(currentMap);
        it1++;
        i++;
    }
    //add states of the second NFA
    int sizeOfFirstNFA = original1.getNFATable().size() - 1;
    i=0;
    while(i <= original2.getAcceptState() && it2 != original2.getNFATable().end())
    {
        map<vector<char>,vector<int>> currentMap = original2.getNFATable()[i];
        std::map<vector<char>,vector<int>>::iterator mapIt = currentMap.begin();
        while(mapIt != currentMap.end() )
        {
            vector<int> newVec;
            for(int state : mapIt->second)
            {
                if(state == original2.getAcceptState())
                {
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
NFA NFA_constructor::signleCharNFA(vector<char> input)
{
    NFA *nfa = new NFA();
    nfa->setAcceptState(1);
    vector<int> vec;
    vec.push_back(1);
    map<vector<char>,vector<int>> firstStateMap;
    firstStateMap.insert(std::pair<vector<char>,vector<int>>(input,vec));
    vector<map<vector<char>,vector<int>>> newNFAtable;
    //insert the start state
    newNFAtable.push_back(firstStateMap);
    vector<int> finalStateVector;
    vector<char> inputVector;
    inputVector.push_back(' ');
    map<vector<char>,vector<int>> finalStateMap;
    finalStateMap.insert(std::pair<vector<char>,vector<int>>(inputVector,finalStateVector));
    //insert empty final state
    newNFAtable.push_back(finalStateMap);
    nfa->setNFATable(newNFAtable);
    return *nfa;
}

NFA NFA_constructor::termNFA(string term)
{
    term = trim(term);
    size_t f = term.find("-");
    if (f != std::string::npos && term.at(f-1)!='\\')
    {
        vector<char> vec;
        char c1 = term.at(f-1);
        char c2 = term.at(f+1);
        for (char c = c1; c <= c2; c++)
        {
            vec.push_back(c);
        }
        return signleCharNFA(vec);
    }
    if (term.length() == 2 && term.at(0) =='\\' && term.at(1) =='L')
    {
        vector<char> vec;
        vec.push_back(epsilon);
        return signleCharNFA(vec);
    }
    char c = term.at(0);
    int j = 1;
    if (term.length() > 1 && c =='\\')
    {
        c = term.at(1);
        j = 2;
    }
    vector<char> vec;
    vec.push_back(c);
    NFA nfa = signleCharNFA(vec);
    for (int i = j; i < term.length(); i++)
    {
        c = term.at(i);
        if (c == '\\')
        {
            c = term.at(i+1);
            i++;
        }
        vector<char> vec;
        vec.push_back(c);
        NFA nfa2 = signleCharNFA(vec);
        nfa = concatinating(nfa, nfa2);
    }
    return nfa;
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
