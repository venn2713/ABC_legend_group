#ifndef LIST_POLYNOMIAL_TABLE_H
#define LIST_POLYNOMIAL_TABLE_H

#include "PolynomialTable.h"
#include <list>
#include <algorithm>
#include <memory>
#include <iostream>

// Конкретная реализация таблицы полиномов на основе связного списка
class ListPolynomialTable : public PolynomialTable {
private:
    // Структура для хранения полинома с его именем
    struct NamedPolynomial {
        std::string name;
        std::shared_ptr<Polynomial> polynomial;

        NamedPolynomial(const std::string& name, std::shared_ptr<Polynomial> polynomial)
            : name(name), polynomial(polynomial) {}

        // Оператор сравнения для поиска по имени
        bool operator==(const std::string& otherName) const {
            return name == otherName;
        }
    };

    std::list<NamedPolynomial> table; // Список для хранения именованных полиномов

public:
    // Итераторы
    typedef std::list<NamedPolynomial>::iterator iterator;
    typedef std::list<NamedPolynomial>::const_iterator const_iterator;

    iterator begin() { return table.begin(); }
    iterator end() { return table.end(); }
    const_iterator begin() const { return table.begin(); }
    const_iterator end() const { return table.end(); }

    // Деструктор
    virtual ~ListPolynomialTable() override {}

    // Вставка полинома в таблицу
    void insert(const Polynomial& polynomial) override {
        auto it = std::find_if(table.begin(), table.end(),
                               [&](const NamedPolynomial& item) { return item.name == polynomial.getName(); });
        if (it != table.end()) {
            // Если полином с таким именем уже существует, заменяем его
            it->polynomial = std::make_shared<Polynomial>(polynomial);
        } else {
            // Иначе добавляем новый полином в список
            table.push_back(NamedPolynomial(polynomial.getName(), std::make_shared<Polynomial>(polynomial)));
        }
    }

    // Удаление полинома из таблицы
    bool remove(const std::string& name) override {
        auto it = std::find_if(table.begin(), table.end(),
                               [&](const NamedPolynomial& item) { return item.name == name; });
        if (it != table.end()) {
            table.erase(it);
            return true;
        }
        return false;
    }

    // Поиск полинома по имени
    std::shared_ptr<Polynomial> find(const std::string& name) const override {
        auto it = std::find_if(table.begin(), table.end(),
                               [&](const NamedPolynomial& item) { return item.name == name; });
        if (it != table.end()) {
            return it->polynomial;
        }
        return nullptr;
    }

    // Вывод содержимого таблицы на экран
    void display() const override {
        for (const auto& item : table) {
            std::cout << "Name: " << item.name << ", Polynomial: " << *(item.polynomial) << std::endl;
        }
    }

    // Получение всех имен полиномов в таблице
    std::vector<std::string> getNames() const override {
        std::vector<std::string> names;
        std::transform(table.begin(), table.end(), std::back_inserter(names),
                       [](const NamedPolynomial& item) { return item.name; });
        return names;
    }

    // Батчевое добавление
    void insertBatch(const std::vector<Polynomial>& polynomials) override {
      for (const auto& polynomial : polynomials) {
        insert(polynomial);
      }
    }

    // Батчевое удаление
    void removeBatch(const std::vector<std::string>& names) override {
      for (const auto& name : names) {
        remove(name);
      }
    }
};

#endif // LIST_POLYNOMIAL_TABLE_H
