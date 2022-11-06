/*
    Простой калькулятор:

    История версий: github

    Эта программа реализует основные выражения калькулятора
    Ввод осуществляется из потока stdin, вывод в поток stdout

    Грамматика для ввода:

    Инструкция:
        Утверждение
        Вывод
        Выход
        Помощь

    Утверждение:
        Объявление
        Выражение

    Объявление:
        let Имя = Выражение
        const Имя = Выражение

    Вывод:
        ;
        \n

    Выход:
        quit

    Помощь:
        help

    Выражение:
        Терм
        Выражение + Терм
        Выражение - Терм

    Третичное_выражение:
        Первичное_выражение
        Первичное_выражение ^ Первичное_выражение

    Вторичное выражение:
        Третичное_выражение
        Третичное_выражение * Третичное_выражение
        Третичное_выражение / Третичное_выражение
        Третичное_выражение % Третичное_выражение

    Первичное_выражение:
        Число
        ( Выражение )
        - Первичное_выражение
        + Первичное_выражение

    Число:
        Литерал_с_плавающей_точкой

    Ввод из потока cin через Token_stream с именем ts
    Имя - слово без пробелов начинающееся с буквы, состоящее из букв, цифр и нижнего подчеркивания
*/

#include <iostream>

#include "token.h"
#include "grammar.h"
#include "variable.h"

void clean_up_mess(TokenStream &ts) {
    ts.ignore(print);
}

void print_help(TokenStream &ts) {
    std::cout << "Объявление переменной:" << '\n'
              << "let Имя = Выражение\nconst Имя = Выражение\n\n"
              << "Операции:\n+, -, /, %, ^, *\n\n"
              << "Вывод выражения: ;, \\n\n\n"
              << "Справка: help\n"
              << "Выход: quit\n";
}

void calculate(TokenStream &ts, SymbolTable &variables) {
    while (std::cin) {
        try {
            std::cout << prompt;
            Token t = ts.get();
            while (t.kind == print)
                t = ts.get();

            if (t.kind == quit)
                return;
            if (t.kind == help) {
                print_help(ts);
                t = ts.get();
            }
            else {
                ts.putback(t);
                std::cout << result << statement(ts, variables) << '\n';
            }
        }
        catch (std::runtime_error &e) {
            std::cerr << e.what() << '\n';
            clean_up_mess(ts);
        }
    }
}

int main() {
    TokenStream ts;
    SymbolTable variables;

    try {
        variables.define("pi", 3.141592653589793, true);
        variables.define("e", 2.718281828459045, true);

        calculate(ts, variables);
        return 0;
    }
    catch (std::runtime_error &e) {
        std::cerr << "exception: " << e.what() << '\n';
        return 1;
    }
    catch (...) {
        std::cerr << "Oops, unknown exception" << '\n';
        return 2;
    }
}