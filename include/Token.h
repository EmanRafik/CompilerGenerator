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
        string getToken_class();
        string getValue();

    protected:

    private:
        string token_class;
        string value;
};

#endif // TOKEN_H
