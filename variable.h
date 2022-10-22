#ifndef CALCULATOR_VARIABLE_H
#define CALCULATOR_VARIABLE_H

#include <string>
#include <vector>

class Variable {
public:
    std::string name;
    double value;

    Variable(std::string n, double v) : name{n}, value{v} {};
};

double get_value(std::string s, std::vector <Variable> &var_table);

void set_value(std::string s, double d, std::vector <Variable> &var_table);

double define_name(std::string var, double val, std::vector <Variable> &var_table);

bool is_declared(std::string s, std::vector <Variable> &var_table);

#endif //CALCULATOR_VARIABLE_H
