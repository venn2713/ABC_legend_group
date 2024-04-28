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

// Тест для проверки добавления полинома в пустую таблицу
TEST(PolynomialTableWithRedBlackTreeTest, AddPolynomialToEmptyTable) {
	PolynomialTableWithRedBlackTree table;
	Polynomial polynomial("3x^2 + 2y^1 - z^1");
	table.addPolynomial("poly1", polynomial);
	EXPECT_EQ(table.getPolynomial("poly1"), polynomial);
}

// Тест для проверки получения полинома из таблицы
TEST(PolynomialTableWithRedBlackTreeTest, GetPolynomial) {
	PolynomialTableWithRedBlackTree table;
	Polynomial polynomial("3x^2 + 2y^1 - z^1");
	table.addPolynomial("poly", polynomial);
	EXPECT_EQ(table.getPolynomial("poly"), polynomial);
}

// Тест для проверки получения несуществующего полинома из таблицы
TEST(PolynomialTableWithRedBlackTreeTest, GetNonexistentPolynomial) {
	PolynomialTableWithRedBlackTree table;
	EXPECT_THROW(table.getPolynomial("nonexistent_poly"), std::out_of_range);
}

// Тест для проверки удаления существующего полинома из таблицы
TEST(PolynomialTableWithRedBlackTreeTest, RemoveExistingPolynomial) {
	PolynomialTableWithRedBlackTree table;
	Polynomial polynomial({ 3, 2, -1 });
	table.addPolynomial("poly1", polynomial);
	table.addPolynomial("poly2", Polynomial({ 1, 2, 3 }));
	table.removePolynomial("poly1");
	EXPECT_THROW(table.getPolynomial("poly1"), std::out_of_range);
	EXPECT_EQ(table.getPolynomial("poly2"), Polynomial({ 1, 2, 3 }));
}

// Тест для проверки удаления несуществующего полинома из таблицы
TEST(PolynomialTableWithRedBlackTreeTest, RemoveNonexistentPolynomial) {
	PolynomialTableWithRedBlackTree table;
	EXPECT_THROW(table.removePolynomial("nonexistent_poly"), std::out_of_range);
}

// Тест для проверки получения имени таблицы
TEST(PolynomialTableWithRedBlackTreeTest, GetTableName) {
	PolynomialTableWithRedBlackTree table;
	EXPECT_EQ(table.getTableName(), "PolynomialTableWithRedBlackTree");
}

// Тест для проверки печати пустой таблицы
TEST(PolynomialTableWithRedBlackTreeTest, PrintEmptyTable) {
	PolynomialTableWithRedBlackTree table;
	std::ostringstream oss;
	table.print(oss);
	std::string expected_output = "PolynomialTableWithRedBlackTree:\n-----------\n-----------\n";
	EXPECT_EQ(oss.str(), expected_output);
}

// Тест для проверки печати таблицы с одним полиномом
TEST(PolynomialTableWithRedBlackTreeTest, PrintTableWithOnePolynomial) {
	PolynomialTableWithRedBlackTree table;
	Polynomial polynomial("3x^2 + 2y^1 - z^1");
	table.addPolynomial("poly", polynomial);
	std::ostringstream oss;
	table.print(oss);
	std::string expected_output = "PolynomialTableWithRedBlackTree:\n-----------\npoly: -z + 2y + 3x^2\n\n-----------\n";
	EXPECT_EQ(oss.str(), expected_output);
}

// Тест для проверки удаления полинома из таблицы с несколькими полиномами
TEST(PolynomialTableWithRedBlackTreeTest, RemovePolynomialWithMultiplePolynomials) {
	PolynomialTableWithRedBlackTree table;
	Polynomial polynomial1("3x^2 + 2y^1 - z^1");
	Polynomial polynomial2("x^1 + y^1 + z^1");
	table.addPolynomial("poly1", polynomial1);
	table.addPolynomial("poly2", polynomial2);
	table.removePolynomial("poly1");
	EXPECT_THROW(table.getPolynomial("poly1"), std::out_of_range);
	EXPECT_EQ(table.getPolynomial("poly2"), polynomial2);
}



// Тест для проверки удаления несуществующего полинома из таблицы
TEST(PolynomialTableWithRedBlackTreeTest, RemoveNonexistentPolynomial1) {
	PolynomialTableWithRedBlackTree table;
	Polynomial polynomial("3x^2 + 2y^1 - z^1");
	Polynomial polynomial1("x^1 + y^1 + z^1");
	table.addPolynomial("poly1", polynomial);
	table.addPolynomial("poly2", polynomial1);
	// Удаляем несуществующий полином
	EXPECT_THROW(table.removePolynomial("nonexistent_poly"), std::out_of_range);
	// Проверяем, что состояние таблицы не изменилось
	EXPECT_EQ(table.getPolynomial("poly1"), polynomial);
	EXPECT_EQ(table.getPolynomial("poly2"), polynomial1);
}
