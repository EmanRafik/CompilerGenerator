#ifndef TOKEN_H
#define TOKEN_H
#include<string>

using namespace std;

class Token
{
    public:
        Token();
        virtual ~Token();
        void setToken_class(string token_class);
        void setValue(string value);
        void setPriority(int priority);
        string getToken_class();
        string getValue();
        int getPriority();

    protected:

    private:
        string token_class;
        string value;
        int priority;
};

#endif // TOKEN_H
