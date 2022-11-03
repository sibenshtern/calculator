#include <iostream>

#include "token.h"
#include "grammar.h"
#include "variable.h"

void clean_up_mess(Token_stream &ts) {
    ts.ignore(print);
}

void print_help(Token_stream &ts) {
    std::cout << "HELP HELP" << '\n';
}

void calculate(Token_stream &ts, Symbol_table &variables) {
    while (std::cin) {
        try {
            if (std::cin.peek() == '\n')
                std::cout << prompt;
            Token t = ts.get();
            while (t.kind == print)
                t = ts.get();

            if (t.kind == quit)
                return;
            if (t.kind == help) {
                print_help(ts);
                t = ts.get();
            }
            else {
                ts.putback(t);
                std::cout << result << statement(ts, variables) << '\n';
            }
        }
        catch (std::runtime_error &e) {
            std::cerr << e.what() << '\n';
            clean_up_mess(ts);
        }
    }
}

int main() {
    Token_stream ts;
    Symbol_table variables;

    try {
        variables.define("pi", 3.141592653589793, true);
        variables.define("e", 2.718281828459045, true);

        calculate(ts, variables);
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