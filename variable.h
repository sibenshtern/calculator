#ifndef CALCULATOR_VARIABLE_H
#define CALCULATOR_VARIABLE_H

#include <string>
#include <vector>

class Variable {
public:
    std::string name;
    double value;

    Variable(std::string n, double v): name{n}, value{v}, _is_const{false} {};
    Variable(std::string n, double v, bool ic): name{n}, value{v}, _is_const{ic} {};

    bool is_const() const {return _is_const;};
private:
    bool _is_const {false};
};

class Symbol_table {
public:
    Symbol_table(): var_table{{}} {};

    double get(std::string);
    void set(std::string, double);
    double define(std::string, double);
    bool is_declared(std::string);
private:
    std::vector<Variable> var_table;

    bool is_const(std::string);
};

#endif //CALCULATOR_VARIABLE_H
