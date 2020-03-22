#ifndef REGULAR_EXPRESSION_H
#define REGULAR_EXPRESSION_H

#include"NFA.h"
#include"Regular_definition.h"
#include<string>
#include<vector>

using namespace std;

class Regular_expression
{
    public:
        Regular_expression();
        virtual ~Regular_expression();
        NFA constructNFA();
        void setName(string name);
        void setValue(string value);
        string getName();
        void setRegular_definitions(vector<Regular_definition> regular_definitions);
        bool isDefinition();
        bool isSymbol();
        int getRelation();
        int getClosure();
        void setClosure(int closure);
        void setDefinition(bool defenition);
        void setSymbol(bool symbol);
        void setRelation(int relation);

    protected:

    private:
        string name;
        string value;
        vector<Regular_definition> regular_definitions;
        bool definition;
        bool symbol;
        int relation_with_next;
        int closure;
};

#endif // REGULAR_EXPRESSION_H
