#include <stdexcept>
#include <string>
#include <algorithm>

#include "variable.h"

double Symbol_table::get(std::string name) {
    for (const Variable &variable: var_table)
        if (variable.name == name)
            return variable.value;

    throw std::runtime_error("get: undefined name" + name);
}

void Symbol_table::set(std::string name, double value) {
    for (int i = 0; i <= var_table.size(); ++i) {
        if (var_table[i].name == name) {
            var_table[i].value = value;
            return;
        }
    }

    throw std::runtime_error("set: undefined name " + name);
}

bool Symbol_table::is_declared(std::string name) {
    for (const Variable &variable: var_table)
        if (variable.name == name)
            return true;

    return false;
}

double Symbol_table::define(std::string name, double value) {
    if (is_declared(name) && is_const(name))
        set(name, value);
    else
        var_table.push_back(Variable{name, value});

    return value;
}

bool Symbol_table::is_const(std::string name) {
    for (const Variable &variable: var_table)
        if (variable.name == name && variable.is_const())
            return true;

    return false;
}