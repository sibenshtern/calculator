#include "token.h"
#include <iostream>

void Token_stream::putback(Token t) {
    if (full)
        throw std::runtime_error("putback(): buffer is full");

    buffer = t;
    full = true;
}

Token Token_stream::get() {
    if (full) {
        full = false;
        return buffer;
    }

    char ch;
    std::cin.get(ch);

    while (std::isblank(ch))
        std::cin.get(ch);

    switch (ch) {
        case '\n':
            return Token{';'};

        case '(':
        case ')':
        case '+':
        case '-':
        case '*':
        case '/':
        case '%':
        case '=':
        case print:
            return Token{ch};

        case '.':
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9': {
            std::cin.putback(ch);

            double val;
            std::cin >> val;

            return Token{number, val};
        }
        default:
            if (std::isalpha(ch)) {
                std::string s;
                s += ch;

                while (std::cin.get(ch) &&
                       (std::isalpha(ch) || std::isdigit(ch) || ch == '_'))
                    s += ch;

                std::cin.putback(ch);

                if (s == declkey)
                    return Token{let};
                if (s == cdeclkey)
                    return Token{clet};
                if (s == quitkey)
                    return Token{quit};
                if (s == helpkey)
                    return Token{help};
                return Token{name, s};
            }
            throw std::runtime_error("Bad token");
    }
}

void Token_stream::ignore(char c) {
    if (full && c == buffer.kind) {
        full = false;
        return;
    }
    full = false;

    char ch;
    while (std::cin >> ch)
        if (ch == c)
            return;
}