#include <gtest.h>
#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <cmath>
#include <string>
#include <regex>
#include <sstream>
#include <unordered_map>
#include <stdexcept>
#include <stack>
#include "StackAndPostfix.h"


// Тест проверки добавления полинома и его получения
TEST(PolynomialArrayTableTest, AddAndGetPolynomial) {
    PolynomialArrayTable table;
    Polynomial p1("2x+5y");
    table.addPolynomial("poly1", p1);

    // Получаем полином по имени
    Polynomial retrieved = table.getPolynomial("poly1");

    // Проверяем, что полученный полином совпадает с добавленным
    ASSERT_EQ(retrieved, p1);
}

// Тест проверки удаления полинома
TEST(PolynomialArrayTableTest, RemovePolynomial) {
    PolynomialArrayTable table;
    Polynomial p1("2x+5y");
    table.addPolynomial("poly1", p1);

    // Удаляем полином
    ASSERT_NO_THROW(table.removePolynomial("poly1"));

    // Попытка получить удаленный полином должна вызвать исключение
    ASSERT_THROW(table.getPolynomial("poly1"), std::out_of_range);
}

// Тест проверки получения несуществующего полинома
TEST(PolynomialArrayTableTest, GetNonexistentPolynomial) {
    PolynomialArrayTable table;

    // Попытка получить несуществующий полином должна вызвать исключение
    ASSERT_THROW(table.getPolynomial("nonexistent_poly"), std::out_of_range);
}

// Тест проверки обновления полинома
TEST(PolynomialArrayTableTest, UpdatePolynomial) {
    PolynomialArrayTable table;
    Polynomial p1("2x+5y");
    Polynomial p2("3x+6y");

    // Добавляем полином
    table.addPolynomial("poly1", p1);

    // Обновляем полином
    table.addPolynomial("poly1", p2);

    // Получаем обновленный полином
    Polynomial retrieved = table.getPolynomial("poly1");

    // Проверяем, что полученный полином совпадает с новым полиномом
    ASSERT_EQ(retrieved, p2);
}

// Тест проверки получения имени таблицы
TEST(PolynomialArrayTableTest, GetTableName) {
    PolynomialArrayTable table;

    // Проверяем, что имя таблицы корректно возвращается
    ASSERT_EQ(table.getTableName(), "PolynomialArrayTable");
}
