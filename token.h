#ifndef CALCULATOR_TOKEN_H
#define CALCULATOR_TOKEN_H

#include <string>

class Token {
public:
    char kind;
    double value;
    std::string name;

    Token(char ch): kind{ch}, value{0} {};
    Token(char ch, double val): kind{ch}, value{val} {};
    Token(char ch, std::string n): kind{ch}, name{n} {};
};

class Token_stream {
public:
    Token_stream() {};

    Token get();

    void putback(Token t);
    void ignore(char c);
private:
    bool full {false};
    Token buffer {'\0'};
};

constexpr char quit = 'q';
constexpr char help = 'h';
constexpr char print = ';';
constexpr char number = '8';
constexpr char name = 'a';
constexpr char let = 'L';
constexpr char clet = 'C';

const std::string prompt = "> ";
const std::string result = "= ";
const std::string declkey = "let";
const std::string cdeclkey = "const";
const std::string quitkey = "quit";
const std::string helpkey = "help";

#endif //CALCULATOR_TOKEN_H
