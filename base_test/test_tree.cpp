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

// “ест дл€ проверки добавлени€ полинома в пустую таблицу
TEST(PolynomialTableWithRedBlackTreeTest, AddPolynomialToEmptyTable) {
	PolynomialTableWithRedBlackTree table;
	Polynomial polynomial("3x^2 + 2y^1 - z^1");
	table.addPolynomial("poly1", polynomial);
	EXPECT_EQ(table.getPolynomial("poly1"), polynomial);
}

// “ест дл€ проверки получени€ полинома из таблицы
TEST(PolynomialTableWithRedBlackTreeTest, GetPolynomial) {
	PolynomialTableWithRedBlackTree table;
	Polynomial polynomial("3x^2 + 2y^1 - z^1");
	table.addPolynomial("poly", polynomial);
	EXPECT_EQ(table.getPolynomial("poly"), polynomial);
}

// “ест дл€ проверки получени€ несуществующего полинома из таблицы
TEST(PolynomialTableWithRedBlackTreeTest, GetNonexistentPolynomial) {
	PolynomialTableWithRedBlackTree table;
	EXPECT_THROW(table.getPolynomial("nonexistent_poly"), std::out_of_range);
}

// “ест дл€ проверки получени€ имени таблицы
TEST(PolynomialTableWithRedBlackTreeTest, GetTableName) {
	PolynomialTableWithRedBlackTree table;
	EXPECT_EQ(table.getTableName(), "PolynomialTableWithRedBlackTree");
}

// “ест дл€ проверки печати пустой таблицы
TEST(PolynomialTableWithRedBlackTreeTest, PrintEmptyTable) {
	PolynomialTableWithRedBlackTree table;
	std::ostringstream oss;
	table.print(oss);
	std::string expected_output = "PolynomialTableWithRedBlackTree:\n-----------\n-----------\n";
	EXPECT_EQ(oss.str(), expected_output);
}

// “ест дл€ проверки печати таблицы с одним полиномом
TEST(PolynomialTableWithRedBlackTreeTest, PrintTableWithOnePolynomial) {
	PolynomialTableWithRedBlackTree table;
	Polynomial polynomial("3x^2 + 2y^1 - z^1");
	table.addPolynomial("poly", polynomial);
	std::ostringstream oss;
	table.print(oss);
	std::string expected_output = "PolynomialTableWithRedBlackTree:\n-----------\npoly: -z + 2y + 3x^2\n\n-----------\n";
	EXPECT_EQ(oss.str(), expected_output);
}
