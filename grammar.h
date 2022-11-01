#ifndef CALCULATOR_GRAMMAR_H
#define CALCULATOR_GRAMMAR_H

#include <vector>

#include "token.h"
#include "variable.h"

template<class R, class A> R narrow_cast(const A &a);

double statement(Token_stream &ts, Symbol_table &variables);

double primary(Token_stream &ts, Symbol_table &variables);

double term(Token_stream &ts, Symbol_table &variables);

double expression(Token_stream &ts, Symbol_table &variables);

double declaration(Token_stream &ts, Symbol_table &variables, bool = false);

void clean_up_mess(Token_stream &ts);

#endif //CALCULATOR_GRAMMAR_H
