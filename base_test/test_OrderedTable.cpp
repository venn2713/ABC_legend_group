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


TEST(PolynomialOrderedTableTest, AddPolynomial) {
    PolynomialOrderedTable table;
    Polynomial poly("x^2 + 2x + 1");
    table.addPolynomial("poly1", poly);
    EXPECT_EQ(table.getPolynomial("poly1"), poly);
}

TEST(PolynomialOrderedTableTest, GetPolynomial) {
    PolynomialOrderedTable table;
    Polynomial poly("3x^2 - 2x");
    table.addPolynomial("poly2", poly);
    EXPECT_EQ(table.getPolynomial("poly2"), poly);
}

TEST(PolynomialOrderedTableTest, RemovePolynomial) {
    PolynomialOrderedTable table;
    Polynomial poly("4x^3 - 3x^2 + 2x - 1");
    table.addPolynomial("poly3", poly);
    table.removePolynomial("poly3");
    EXPECT_THROW(table.getPolynomial("poly3"), std::out_of_range);
}

TEST(PolynomialOrderedTableTest, GetTableName) {
    PolynomialOrderedTable table;
    EXPECT_EQ(table.getTableName(), "PolynomialOrderedTable");
}

TEST(PolynomialOrderedTableTest, PrintEmptyTable) {
    PolynomialOrderedTable table;
    testing::internal::CaptureStdout();
    table.print(std::cout);
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "PolynomialOrderedTable:\n-----------\n-----------\n");
}

TEST(PolynomialOrderedTableTest, AddDuplicatePolynomial) {
    PolynomialOrderedTable table;
    Polynomial poly("3x^2 + 2x + 1");
    table.addPolynomial("duplicate_poly", poly);
    table.addPolynomial("duplicate_poly", poly); // adding duplicate
    EXPECT_EQ(table.getPolynomial("duplicate_poly"), poly);
}
