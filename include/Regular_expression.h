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
        NFA getNFA(vector<Regular_definition> regular_definitions);
        void setName(string name);
        void setValue(string value);
        void setPriority(int priority);
        string getName();
        string getValue();
        int getPriority();

    protected:

    private:
        string name;
        string value;
        vector<Regular_definition> regular_definitions;
        int priority;
};

#endif // REGULAR_EXPRESSION_H
