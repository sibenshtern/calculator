#include <iostream>

#include "token.h"
#include "grammar.h"
#include "variable.h"

void clean_up_mess(Token_stream &ts) {
    ts.ignore(print);
}

void calculate(Token_stream &ts, std::vector<Variable> &var_table) {
    while (std::cin) {
        try {
            std::cout << prompt;
            Token t = ts.get();
            while (t.kind == print)
                t = ts.get();
            if (t.kind == quit)
                return;

            ts.putback(t);
            std::cout << result << statement(ts, var_table) << '\n';
        }
        catch (std::runtime_error &e) {
            std::cerr << e.what() << '\n';
            clean_up_mess(ts);
        }
    }
}

int main() {
    Token_stream ts;
    std::vector<Variable> var_table;

    try {
        define_name("pi", 3.141592653589793, var_table);
        define_name("e", 2.718281828459045, var_table);

        calculate(ts, var_table);
        return 0;
    }
    catch (std::runtime_error &e) {
        std::cerr << "exception: " << e.what() << '\n';
        return 1;
    }
    catch (...) {
        std::cerr << "Oops, unknown exception" << '\n';
        return 2;
    }
}