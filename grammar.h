#ifndef CALCULATOR_GRAMMAR_H
#define CALCULATOR_GRAMMAR_H

#include <vector>

#include "token.h"
#include "variable.h"

template<class R, class A> R narrow_cast(const A &a);

double statement(Token_stream &ts, std::vector<Variable> &var_table);

double primary(Token_stream &ts, std::vector<Variable> &var_table);

double term(Token_stream &ts, std::vector<Variable> &var_table);

double expression(Token_stream &ts, std::vector<Variable> &var_table);

double declaration(Token_stream &ts, std::vector<Variable> &var_table);

void clean_up_mess(Token_stream &ts);

#endif //CALCULATOR_GRAMMAR_H
