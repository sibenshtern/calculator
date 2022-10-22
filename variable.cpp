#include <stdexcept>
#include "variable.h"

double get_value(std::string s, std::vector<Variable> &var_table) {
    for (int i = 0; i < var_table.size(); ++i)
        if (var_table[i].name == s)
            return var_table[i].value;

    throw std::runtime_error("get: undefined name " + s);
}

void set_value(std::string s, double d, std::vector<Variable> &var_table) {
    for (int i = 0; i <= var_table.size(); ++i) {
        if (var_table[i].name == s) {
            var_table[i].value = d;
            return;
        }
    }
    throw std::runtime_error("set: undefined name " + s);
}

bool is_declared(std::string s, std::vector<Variable> &var_table) {
    for (int i = 0; i < var_table.size(); ++i)
        if (var_table[i].name == s)
            return true;
    return false;
}

double define_name(std::string var, double val, std::vector<Variable> &var_table) {
    if (is_declared(var, var_table))
        throw std::runtime_error(var + " declated twice");

    var_table.push_back(Variable{var, val});
    return val;
}
