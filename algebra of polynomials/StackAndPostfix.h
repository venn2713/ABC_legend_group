#include "TableManager.h"


// Шаблонный класс стека, использующий std::vector для хранения элементов.
template<typename T>
class Stack {
private:
    std::vector<T> data;  // Вектор для хранения элементов стека

public:
    // Метод для добавления элемента в стек
    void push(const T& item) {
        data.push_back(item);  // Добавление элемента в конец вектора
    }

    // Метод для извлечения элемента из стека
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Pop from empty stack");  // Если стек пуст, бросается исключение
        }
        T item = data.back();  // Получение последнего элемента из вектора
        data.pop_back();  // Удаление последнего элемента из вектора
        return item;  // Возвращение извлечённого элемента
    }

    // Метод для получения верхнего элемента стека без его удаления
    T top() const {
        if (isEmpty()) {
            throw std::runtime_error("Top from empty stack");  // Если стек пуст, бросается исключение
        }
        return data.back();  // Возвращение последнего элемента из вектора
    }

    // Метод для проверки, пуст ли стек
    bool isEmpty() const {
        return data.empty();  // Проверка наличия элементов в векторе
    }
};


// Класс калькулятора для вычисления выражений в постфиксной нотации.
class PostfixCalculator {
private:
    TableManager& tableManager;  // Ссылка на менеджер таблиц, содержащий полиномы

public:
    // Конструктор, инициализирующий калькулятор с менеджером таблиц
    PostfixCalculator(TableManager& tableManager) : tableManager(tableManager) {}

    // Основной метод для вычисления выражения
    // Основной метод для вычисления выражения
    Polynomial evaluate(const std::string& expression) {
        IPolynomialTable* table = tableManager.getActiveTable();  // Получение активной таблицы
        std::istringstream iss(expression);
        std::string token;
        Stack<Polynomial> stack;  // Стек для хранения полиномов в процессе вычисления

        // Разбор и вычисление выражения
        while (iss >> token) {
            if (isOperator(token)) {  // Если токен - оператор, выполняем операцию
                Polynomial result = performOperation(token, stack);
                stack.push(result);
            }
            else if (std::regex_match(token, std::regex("^[-+]?[0-9]*\\.?[0-9]+$"))) {  // Если токен - число, преобразуем в полином
                double scalar = std::stod(token);
                Polynomial scalarPoly = Polynomial(std::to_string(scalar));
                stack.push(scalarPoly);
            }
            else {  // Иначе, токен - имя полинома, получаем полином из таблицы
                Polynomial& poly = table->getPolynomial(token);
                stack.push(poly);
            }
        }

        // Если стек пуст после обработки, выражение некорректно
        if (stack.isEmpty()) {
            throw std::runtime_error("Error in expression: no result on stack");
        }

        Polynomial finalResult = stack.pop();  // Результат вычисления выражения
        return finalResult;
    }

    // Преобразование инфиксного выражения в постфиксное
    std::string infixToPostfix(const std::string& infix) {
        std::stack<char> opStack;
        std::string postfix = "";
        for (size_t i = 0; i < infix.length(); i++) {
            char c = infix[i];
            if (c == ' ') continue;
            if (isdigit(c) || isalpha(c) || c == '.') {
                postfix += c;
                while (i + 1 < infix.length() && (isdigit(infix[i + 1]) || isalpha(infix[i + 1]) || infix[i + 1] == '.')) {
                    postfix += infix[++i];
                }
                postfix += " ";
            }
            else if (c == '(') {
                opStack.push(c);
            }
            else if (c == ')') {
                while (!opStack.empty() && opStack.top() != '(') {
                    postfix += opStack.top();
                    postfix += " ";
                    opStack.pop();
                }
                opStack.pop();
            }
            else if (isOperator(c)) {
                while (!opStack.empty() && precedence(opStack.top()) >= precedence(c)) {
                    postfix += opStack.top();
                    postfix += " ";
                    opStack.pop();
                }
                opStack.push(c);
            }
        }

        while (!opStack.empty()) {
            postfix += opStack.top();
            postfix += " ";
            opStack.pop();
        }

        return postfix;
    }

private:
    // Проверка, является ли строка оператором
    bool isOperator(std::string token) {
        return token == "+" || token == "-" || token == "*" || token == "/";
    }

    // Проверка, является ли символ оператором
    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    // Определение приоритета операторов
    int precedence(char op) {
        switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
        }
    }

    // Выполнение арифметической операции над двумя полиномами
    Polynomial performOperation(const std::string& op, Stack<Polynomial>& stack) {
        Polynomial right = stack.pop();  // Получение правого операнда
        Polynomial left = stack.pop();   // Получение левого операнда

        if (op == "+") {
            return left + right;
        }
        else if (op == "-") {
            return left - right;
        }
        else if (op == "*") {
            return left * right;
        }
        else if (op == "/") {
            throw std::runtime_error("Division of polynomials is not implemented");
        }

        throw std::runtime_error("Invalid operation");
    }
};
