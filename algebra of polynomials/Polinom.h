#ifndef POLYNOMIALS_H
#define POLYNOMIALS_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <cmath> 
#include <regex>
#include "Monom.h"
#include "TablesControl.h"


class Polinom {
private:
    string name;
    TList<Monom> monoms;
    static tablesControl tables;
    static int dublicate;

    void AddMonom(const Monom& monom);

public:
    Polinom() {}
    Polinom(const Polinom& other);
    Polinom(const string& name, const string& polinomStr);

    string getName();
    void setName(string oldName, string newName);
    void combineLikeTerms();
    void deletePolinom();
    bool isEmpty();
    double Ñalculation(double x, double y, double z) const;
    Polinom MultiplyByConst(int constant) const;

    Polinom& operator=(const Polinom& other);
    Polinom operator-(const Polinom& other) const;
    Polinom operator+(const Polinom& other) const;
    Polinom operator*(const Polinom& other) const;

    friend ostream& operator<<(ostream& stream, const Polinom& source) {

        activeName = source.name;
        stream << source.tables;
        return stream;
    }
};
#endif