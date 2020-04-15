#include "Non_terminal.h"

Non_terminal::Non_terminal()
{
    //ctor
    first_computed = false;
}

Non_terminal::~Non_terminal()
{
    //dtor
}

void Non_terminal::set_symbol(string symbol)
{
    this->symbol = symbol;
}

string Non_terminal::get_symbol()
{
    return this->symbol;
}

set<string> Non_terminal::get_first()
{
    return this->first;
}

set<string> Non_terminal::get_follow()
{
    return this->follow;
}

void Non_terminal::add_production(Production production)
{
    production.push_back(production);
}

void Non_terminal::compute_first()
{
    for (unsigned int i = 0; i < productions.size(); i++)
    {
        Production production = productions[i];
        Symbol first_symbol = production.getTo()[0];
        if (first_symbol.isTerminal())
        {
            first.insert(first_symbol.getSymbol())
        }
        else
        {

        }
    }
}

bool Non_terminal::is_first_computed()
{
    return this->first_computed;
}
