#ifndef REGULAR_DEFINITION_H
#define REGULAR_DEFINITION_H

#include<string>
#include"NFA.h"
using namespace std;

class Regular_definition
{
    public:
        Regular_definition();
        virtual ~Regular_definition();
        void setName(string name);
        void setValue(string value);
        string getName();
        string getValue();
        NFA getNFA(vector<Regular_definition> regular_definitions);

    protected:

    private:
        string name;
        string value;
};

#endif // REGULAR_DEFINITION_H
