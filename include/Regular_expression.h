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
        NFA getNFA();
        void setName(string name);
        void setValue(string value);
        string getName();
        string getValue();

    protected:

    private:
        string name;
        string value;
        vector<Regular_definition> regular_definitions;
};

#endif // REGULAR_EXPRESSION_H
