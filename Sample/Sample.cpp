#include <iostream>
#include <map>
#include <cmath>
#include <regex>
#include <sstream>
#include <unordered_map>
#include <stdexcept>
#include <stack>
#include "TableManager.h"
#include "StackAndPostfix.h"


int main() {
    TableManager manager; // Создание менеджера таблиц

    // Добавление полиномов во все таблицы
    manager.addPolynomialToAllTables("pol1", Polynomial("3.2x^2y^3z^1 - 1.3x^1z^4"));
    manager.addPolynomialToAllTables("pol2", Polynomial("-3.2x^2y^3z^1 + 1.3x^1z^4"));
    manager.addPolynomialToAllTables("q", Polynomial("4.0x^2"));
    manager.addPolynomialToAllTables("const6", Polynomial("6"));

    std::vector<std::string> tables_name = {
        "PolynomialListTable",
        "PolynomialArrayTable",
        "PolynomialOrderedTable",
        "PolynomialHashTable",
        "PolynomialRBTreeTable"
    };

    for (int i = 0; i < 5; i++)
        std::cout << i + 1 << ". " << tables_name[i] << std::endl;

    int t;

    std::cout << "Input your choice: ";
    std::cin >> t;

    system("cls");

    std::cout << "You use table: " << tables_name[t - 1] << std::endl;

    // Установка активной таблицы по имени (предполагается, что у вас есть такая таблица)
    manager.setActiveTableByName(tables_name[t - 1]);

    // Создание и использование PostfixCalculator с TableManager
    PostfixCalculator calc(manager);
    try {
        std::string infix_string = "2 * pol1 + 2 * pol2 + 3.6 * q - const6";
        std::cout << "Infix: \"" << infix_string << "\"" << std::endl;
        std::string postfix_string = calc.infixToPostfix(infix_string);
        std::cout << "Postfix: \"" << postfix_string << "\"" << std::endl;
        Polynomial result = calc.evaluate(postfix_string);
        std::cout << "Result: ";
        result.print(std::cout);
    }
    catch (const std::exception& e) {
        std::cout << "An error occurred: " << e.what() << std::endl;
    }
    return 0;
}