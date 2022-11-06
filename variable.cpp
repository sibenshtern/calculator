#include <stdexcept>
#include <string>
#include <algorithm>

#include "variable.h"

double SymbolTable::get(std::string name) {
    for (const Variable &variable: var_table)
        if (variable.name == name)
            return variable.value;

    throw std::runtime_error("get: undefined name " + name);
}

void SymbolTable::set(std::string name, double value) {
    for (int i = 0; i <= var_table.size(); ++i) {
        if (var_table[i].name == name) {
            var_table[i].value = value;
            return;
        }
    }

    throw std::runtime_error("set: undefined name " + name);
}

bool SymbolTable::is_declared(std::string name) {
    for (const Variable &variable: var_table)
        if (variable.name == name)
            return true;

    return false;
}

double SymbolTable::define(std::string name, double value, bool _is_const) {
    if (is_declared(name) && !is_const(name))
        set(name, value);
    else if (is_declared(name) && is_const(name))
        throw std::runtime_error("can't change const variable");

    var_table.push_back(Variable{name, value, _is_const});

    return value;
}

bool SymbolTable::is_const(std::string name) {
    for (const Variable &variable: var_table)
        if (variable.name == name && variable.is_const())
            return true;

    return false;
}