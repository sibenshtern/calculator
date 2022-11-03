#include "grammar.h"
#include <stdexcept>
#include <cmath>

template<class R, class A> R narrow_cast(const A &a) {
    R r = R(a);
    if (A(r) != a)
        throw std::runtime_error("info loss");
    return r;
}

double primary(Token_stream &ts, Symbol_table &variables) {
    Token t = ts.get();
    switch (t.kind) {
        case '(': {
            double d = expression(ts, variables);
            t = ts.get();
            if (t.kind != ')')
                throw std::runtime_error("'(' expected");
            return d;
        }
        case '-':
            return -primary(ts, variables);
        case '+':
            return primary(ts, variables);
        case number:
            return t.value;
        case name:
            return variables.get(t.name);
        default:
            throw std::runtime_error("primary expected");
    }
}

double term(Token_stream &ts, Symbol_table &variables) {
    double left = primary(ts, variables);
    while (true) {
        Token t = ts.get();
        switch (t.kind) {
            case '^': {
                left = std::pow(left, primary(ts, variables));
                break;
            }
            case '*':
                left *= primary(ts, variables);
                break;
            case '/': {
                double d = primary(ts, variables);
                if (d == 0)
                    throw std::runtime_error("Division by zero");
                left /= d;
                break;
            }
            case '%': {
                int i1 = narrow_cast<int>(left);
                int i2 = narrow_cast<int>(primary(ts, variables));

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

double expression(Token_stream &ts, Symbol_table &variables) {
    double left = term(ts, variables);

    while (true) {
        Token t = ts.get();
        switch (t.kind) {
            case '+':
                left += term(ts, variables);
                break;
            case '-':
                left -= term(ts, variables);
                break;
            default:
                ts.putback(t);
                return left;
        }
    }
}

double declaration(Token_stream &ts, Symbol_table &variables, bool is_const) {
    Token t = ts.get();
    if (t.kind != name)
        throw std::runtime_error("name expected in declaration");

    std::string var = t.name;
    if (variables.is_declared(var) && variables.is_const(var) && !is_const)
        throw std::runtime_error("variable '" + var + "' already defined as const");
    if (variables.is_declared(var) && !variables.is_const(var) && is_const)
        throw std::runtime_error("variable '" + var + "' already defined as usual variable");
    if (variables.is_declared(var) && variables.is_const(var) && is_const)
        throw std::runtime_error("can't change const variable");

    t = ts.get();
    if (t.kind != '=')
        throw std::runtime_error("'=' missing in declaration of " + var);

    if (variables.is_declared(var) && !is_const)
        return variables.define(var, expression(ts, variables));

    return variables.define(var, expression(ts, variables), is_const);
}

double statement(Token_stream &ts, Symbol_table &variables) {
    Token t = ts.get();
    switch (t.kind) {
        case let:
            return declaration(ts, variables);
        case clet:
            return declaration(ts, variables, true);
        default:
            ts.putback(t);
            return expression(ts, variables);
    }
}
