#ifndef CALCULATOR_GRAMMAR_H
#define CALCULATOR_GRAMMAR_H

#include <vector>

#include "token.h"
#include "variable.h"

template<class R, class A> R narrow_cast(const A &a);

double statement(TokenStream &ts, SymbolTable &variables);

double primary(TokenStream &ts, SymbolTable &variables);

double term(TokenStream &ts, SymbolTable &variables);

double expression(TokenStream &ts, SymbolTable &variables);

double declaration(TokenStream &ts, SymbolTable &variables, bool = false);

void clean_up_mess(TokenStream &ts);

#endif //CALCULATOR_GRAMMAR_H
