#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "Monomial.h"
#include <vector>
#include <iostream>
#include <string>

class Polynomial {
private:
    std::vector<Monomial> monomials; // Вектор одночленов, составляющих полином
    std::string name; // Имя полинома для удобства идентификации

public:
    // Конструктор с именем полинома
    explicit Polynomial(const std::string& name = "") : name(name) {}

    // Добавление одночлена к полиному
    void addMonomial(const Monomial& monomial) {
        for (auto& m : monomials) {
            // Если степени одночленов совпадают, сложить их коэффициенты
            if (m.getDegreeX() == monomial.getDegreeX() && m.getDegreeY() == monomial.getDegreeY() && m.getDegreeZ() == monomial.getDegreeZ()) {
                m = m + monomial;
                return;
            }
        }
        // Если одночлен с такими степенями не найден, добавляем новый
        monomials.push_back(monomial);
    }

    // Геттеры и сеттеры
    std::string getName() const { return name; }
    void setName(const std::string& newName) { name = newName; }

    // Операторы для работы с полиномами
    Polynomial operator+(const Polynomial& other) const;
    Polynomial operator-(const Polynomial& other) const;
    Polynomial operator*(const Polynomial& other) const;

    // Вывод полинома в поток
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& polynomial);
};

// Реализация операторов и функций
Polynomial Polynomial::operator+(const Polynomial& other) const {
    Polynomial result(*this); // Копирование текущего полинома
    for (const auto& monomial : other.monomials) {
        result.addMonomial(monomial); // Добавление одночленов из другого полинома
    }
    return result;
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    Polynomial result(*this); // Копирование текущего полинома
    for (const auto& monomial : other.monomials) {
        // Создание одночлена с отрицательным коэффициентом для вычитания
        result.addMonomial(Monomial(-monomial.getCoefficient(), monomial.getDegreeX(), monomial.getDegreeY(), monomial.getDegreeZ()));
    }
    return result;
}

Polynomial Polynomial::operator*(const Polynomial& other) const {
    Polynomial result;
    for (const auto& monomial1 : this->monomials) {
        for (const auto& monomial2 : other.monomials) {
            result.addMonomial(monomial1 * monomial2); // Перемножение одночленов
        }
    }
    return result;
}

std::ostream& operator<<(std::ostream& os, const Polynomial& polynomial) {
    for (const auto& monomial : polynomial.monomials) {
        os << monomial << " + ";
    }
    return os;
}

#endif // POLYNOMIAL_H
