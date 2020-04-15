#ifndef NON_TERMINAL_H
#define NON_TERMINAL_H


class Non_terminal
{
    public:
        Non_terminal();
        virtual ~Non_terminal();
        void set_symbol(string symbol);
        string get_symbol();
        set<string> get_first();
        set<string> get_follow();
        void add_production(Production production);
        void compute_first();
        bool is_first_computed();

    protected:

    private:
        string symbol;
        vector<Production> productions;
        set<string> first;
        set<string> follow;
        bool first_computed;
};

#endif // NON_TERMINAL_H
