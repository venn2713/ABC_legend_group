#ifndef OPEN_HASH_POLYNOMIAL_TABLE_H
#define OPEN_HASH_POLYNOMIAL_TABLE_H

#include "PolynomialTable.h"
#include <vector>
#include <optional>
#include <functional>
#include <iostream>

// Реализация хеш-таблицы с открытым адресованием для полиномов
class OpenHashPolynomialTable : public PolynomialTable {
private:
    struct HashEntry {
        std::string name;
        std::shared_ptr<Polynomial> polynomial;
        bool isActive;

        HashEntry() : isActive(false) {}
        HashEntry(const std::string& name, std::shared_ptr<Polynomial> polynomial)
            : name(name), polynomial(polynomial), isActive(true) {}
    };

    std::vector<HashEntry> table;
    size_t activeEntries = 0;

    // Простая хеш-функция для демонстрации
    size_t hashFunction(const std::string& key, size_t tableSize) const {
        std::hash<std::string> hasher;
        return hasher(key) % tableSize;
    }

    // Реаллокация таблицы для расширения размера и рехеширования элементов
    void rehash() {
        auto oldTable = table;
        table.clear();
        table.resize(oldTable.size() * 2);
        activeEntries = 0;

        for (auto& entry : oldTable) {
            if (entry.isActive) {
                insert(*entry.polynomial);
            }
        }
    }

public:
    OpenHashPolynomialTable(size_t size = 101) : table(size) {}

    void insert(const Polynomial& polynomial) override {
        if ((activeEntries + 1) * 2 >= table.size()) {
            rehash(); // Расширяем таблицу при достижении порога заполненности
        }

        size_t index = hashFunction(polynomial.getName(), table.size());
        while (table[index].isActive && table[index].name != polynomial.getName()) {
            index = (index + 1) % table.size();
        }

        table[index] = HashEntry(polynomial.getName(), std::make_shared<Polynomial>(polynomial));
        activeEntries++;
    }

    bool remove(const std::string& name) override {
        size_t index = hashFunction(name, table.size());
        while (table[index].isActive) {
            if (table[index].name == name) {
                table[index].isActive = false;
                activeEntries--;
                return true;
            }
            index = (index + 1) % table.size();
        }
        return false;
    }

    std::shared_ptr<Polynomial> find(const std::string& name) const override {
        size_t index = hashFunction(name, table.size());
        while (table[index].isActive) {
            if (table[index].name == name) {
                return table[index].polynomial;
            }
            index = (index + 1) % table.size();
        }
        return nullptr;
    }

    void display() const override {
        for (const auto& entry : table) {
            if (entry.isActive) {
                std::cout << "Name: " << entry.name << ", Polynomial: " << *(entry.polynomial) << std::endl;
            }
        }
    }

    std::vector<std::string> getNames() const override {
        std::vector<std::string> names;
        for (const auto& entry : table) {
            if (entry.isActive) {
                names.push_back(entry.name);
            }
        }
        return names;
    }
};

#endif // OPEN_HASH_POLYNOMIAL_TABLE_H
