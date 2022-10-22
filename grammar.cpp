#include "grammar.h"
#include <stdexcept>

template<class R, class A> R narrow_cast(const A &a) {
    R r = R(a);
    if (A(r) != a)
        throw std::runtime_error("info loss");
    return r;
}

double primary(Token_stream &ts, std::vector<Variable> &var_table) {
    Token t = ts.get();
    switch (t.kind) {
        case '(': {
            double d = expression(ts, var_table);
            t = ts.get();
            if (t.kind != ')')
                throw std::runtime_error("'(' expected");
            return d;
        }
        case '-':
            return -primary(ts, var_table);
        case '+':
            return primary(ts, var_table);
        case number:
            return t.value;
        case name:
            return get_value(t.name, var_table);
        default:
            throw std::runtime_error("primary expected");
    }
}

double term(Token_stream &ts, std::vector<Variable> &var_table) {
    double left = primary(ts, var_table);
    while (true) {
        Token t = ts.get();
        switch (t.kind) {
            case '*':
                left *= primary(ts, var_table);
                break;
            case '/': {
                double d = primary(ts, var_table);
                if (d == 0)
                    throw std::runtime_error("Division by zero");
                left /= d;
                break;
            }
            case '%': {
                int i1 = narrow_cast<int>(left);
                int i2 = narrow_cast<int>(primary(ts, var_table));

                if (i2 == 0)
                    throw std::runtime_error("Division by zero");

                left = i1 % i2;
                break;
            }
            default:
                ts.putback(t);
                return left;
        }
    }
}

double expression(Token_stream &ts, std::vector<Variable> &var_table) {
    double left = term(ts, var_table);

    while (true) {
        Token t = ts.get();
        switch (t.kind) {
            case '+':
                left += term(ts, var_table);
                break;
            case '-':
                left -= term(ts, var_table);
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
}

double declaration(Token_stream &ts, std::vector<Variable> &var_table) {
    Token t = ts.get();
    if (t.kind != name)
        throw std::runtime_error("name expected in declaration");

    std::string var = t.name;
    if (is_declared(var, var_table))
        throw std::runtime_error(var + " declared twice");

    t = ts.get();
    if (t.kind != '=')
        throw std::runtime_error("'=' missing in declaration of " + var);

    return define_name(var, expression(ts, var_table), var_table);
}

double statement(Token_stream &ts, std::vector<Variable> &var_table) {
    Token t = ts.get();
    switch (t.kind) {
        case let:
            return declaration(ts, var_table);
        default:
            ts.putback(t);
            return expression(ts, var_table);
    }
}
