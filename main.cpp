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

    Терм:
        Первичное_выражение
        Терм * Первичное_выражение
        Терм / Первичное_выражение
        Терм % Первичное_выражение
        Терм ^ Первичное_выражение

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

void clean_up_mess(Token_stream &ts) {
    ts.ignore(print);
}

void print_help(Token_stream &ts) {
    std::cout << "HELP HELP" << '\n';
}

void calculate(Token_stream &ts, Symbol_table &variables) {
    while (std::cin) {
        try {
            if (std::cin.peek() == '\n')
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
    Token_stream ts;
    Symbol_table variables;

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