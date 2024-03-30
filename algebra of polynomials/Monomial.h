#ifndef MONOMIAL_H
#define MONOMIAL_H

#include <iostream>

class Monomial {
private:
    double coefficient; // Коэффициент одночлена
    int degreeX; // Степень по переменной x
    int degreeY; // Степень по переменной y
    int degreeZ; // Степень по переменной z

public:
    // Конструктор с параметрами по умолчанию
    Monomial(double coeff = 0.0, int x = 0, int y = 0, int z = 0)
        : coefficient(coeff), degreeX(x), degreeY(y), degreeZ(z) {}

    // Геттеры для членов данных класса
    double getCoefficient() const { return coefficient; }
    int getDegreeX() const { return degreeX; }
    int getDegreeY() const { return degreeY; }
    int getDegreeZ() const { return degreeZ; }

    // Сеттеры для членов данных класса
    void setCoefficient(double coeff) { coefficient = coeff; }
    void setDegreeX(int x) { degreeX = x; }
    void setDegreeY(int y) { degreeY = y; }
    void setDegreeZ(int z) { degreeZ = z; }

    // Оператор сравнения для упорядочивания одночленов
    bool operator<(const Monomial& other) const {
        if (degreeX == other.degreeX) {
            if (degreeY == other.degreeY) {
                return degreeZ < other.degreeZ;
            }
            return degreeY < other.degreeY;
        }
        return degreeX < other.degreeX;
    }

    // Операторы сложения, вычитания и умножения одночленов
    Monomial operator+(const Monomial& other) const;
    Monomial operator-(const Monomial& other) const;
    Monomial operator*(const Monomial& other) const;

    // Дружественная функция для вывода одночлена
    friend std::ostream& operator<<(std::ostream& os, const Monomial& monomial);
};

// Реализация дружественной функции вывода
std::ostream& operator<<(std::ostream& os, const Monomial& monomial) {
    os << monomial.coefficient << "x^" << monomial.degreeX << "y^" << monomial.degreeY << "z^" << monomial.degreeZ;
    return os;
}

// Реализация операторов сложения, вычитания и умножения
Monomial Monomial::operator+(const Monomial& other) const {
    // Предполагается, что операция допустима только для одночленов с одинаковыми степенями
    if (degreeX == other.degreeX && degreeY == other.degreeY && degreeZ == other.degreeZ) {
        return Monomial(coefficient + other.coefficient, degreeX, degreeY, degreeZ);
    } else {
        // В реальном применении здесь может быть логика обработки ошибки
        std::cerr << "Attempt to add monomials with different degrees" << std::endl;
        return *this;
    }
}

Monomial Monomial::operator-(const Monomial& other) const {
    // Аналогично операции сложения
    if (degreeX == other.degreeX && degreeY == other.degreeY && degreeZ == other.degreeZ) {
        return Monomial(coefficient - other.coefficient, degreeX, degreeY, degreeZ);
    } else {
        std::cerr << "Attempt to subtract monomials with different degrees" << std::endl;
        return *this;
    }
}

Monomial Monomial::operator*(const Monomial& other) const {
    return Monomial(coefficient * other.coefficient, degreeX + other.degreeX, degreeY + other.degreeY, degreeZ + other.degreeZ);
}

#endif // MONOMIAL_H
