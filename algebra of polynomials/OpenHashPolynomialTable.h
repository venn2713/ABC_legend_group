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

    void rehash(size_t newSize) {
      std::vector<HashEntry> newTable(newSize);
      std::swap(table, newTable);
      activeEntries = 0;

      for (const auto& entry : newTable) {
        if (entry.isActive) {
          size_t newIndex = hashFunction(entry.name, newSize);
          while (table[newIndex].isActive) {
            newIndex = (newIndex + 1) % newSize;
          }
          table[newIndex] = entry; // Копируем активные элементы в новую таблицу
          ++activeEntries;
        }
      }
    }

    // Вставка полинома в таблицу
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

    // Удаление полинома из таблицы
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

    // Поиск полинома по имени
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

    // Вывод содержимого таблицы на экран
    void display() const override {
        for (const auto& entry : table) {
            if (entry.isActive) {
                std::cout << "Name: " << entry.name << ", Polynomial: " << *(entry.polynomial) << std::endl;
            }
        }
    }

    // Получение всех имен полиномов в таблице
    std::vector<std::string> getNames() const override {
        std::vector<std::string> names;
        for (const auto& entry : table) {
            if (entry.isActive) {
                names.push_back(entry.name);
            }
        }
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

#endif // OPEN_HASH_POLYNOMIAL_TABLE_H
