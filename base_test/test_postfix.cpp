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

// “ест дл€ вычислени€ выражени€ с двум€ числами
TEST(PostfixCalculatorTest, Evaluate_TwoNumbers) {
	TableManager tableManager;
	PostfixCalculator calculator(tableManager);

	std::string postfixExpression = "5 3 +";
	Polynomial expected("8");

	Polynomial result = calculator.evaluate(postfixExpression);

	EXPECT_EQ(result, expected);
}

// “ест дл€ вычислени€ выражени€ с использованием переменной из таблицы
TEST(PostfixCalculatorTest, Evaluate_WithVariableFromTable) {
	TableManager tableManager;
	PostfixCalculator calculator(tableManager);

	// ƒобавл€ем полином "2x" в таблицу
	tableManager.addPolynomialToAllTables("2x", Polynomial("2x"));

	std::string postfixExpression = "3 2x *";
	Polynomial expected("6x");

	Polynomial result = calculator.evaluate(postfixExpression);

	EXPECT_EQ(result, expected);
}

// “ест дл€ проверки делени€ полиномов (ожидаемое исключение)
TEST(PostfixCalculatorTest, Division_NotImplemented) {
	TableManager tableManager;
	PostfixCalculator calculator(tableManager);

	// ƒобавл€ем полиномы в таблицу
	tableManager.addPolynomialToAllTables("x", Polynomial("x"));
	tableManager.addPolynomialToAllTables("x^2", Polynomial("x^2"));

	std::string postfixExpression = "x x^2 /";

	EXPECT_THROW(calculator.evaluate(postfixExpression), std::runtime_error);
}

// “ест дл€ проверки вычислени€ выражени€ с отрицательным числом
TEST(PostfixCalculatorTest, Evaluate_NegativeNumber) {
	TableManager tableManager;
	PostfixCalculator calculator(tableManager);

	std::string postfixExpression = "-5";
	Polynomial expected("-5");

	Polynomial result = calculator.evaluate(postfixExpression);

	EXPECT_EQ(result, expected);
}

// “ест дл€ проверки вычислени€ выражени€ с оператором "-"
TEST(PostfixCalculatorTest, Evaluate_Subtraction) {
	TableManager tableManager;
	PostfixCalculator calculator(tableManager);

	std::string postfixExpression = "10 7 -";
	Polynomial expected("3");

	Polynomial result = calculator.evaluate(postfixExpression);

	EXPECT_EQ(result, expected);
}

// “ест дл€ проверки вычислени€ выражени€ с оператором "*"
TEST(PostfixCalculatorTest, Evaluate_Multiplication) {
	TableManager tableManager;
	PostfixCalculator calculator(tableManager);

	std::string postfixExpression = "10 3 *";
	Polynomial expected("30");

	Polynomial result = calculator.evaluate(postfixExpression);

	EXPECT_EQ(result, expected);
}

// “ест дл€ проверки вычислени€ выражени€ с переменной из таблицы и числом
TEST(PostfixCalculatorTest, Evaluate_VariableAndNumber) {
	TableManager tableManager;
	PostfixCalculator calculator(tableManager);

	// ƒобавл€ем полином "2x" в таблицу
	tableManager.addPolynomialToAllTables("2x", Polynomial("2x"));

	std::string postfixExpression = "2 2x *";
	Polynomial expected("4x");

	Polynomial result = calculator.evaluate(postfixExpression);

	EXPECT_EQ(result, expected);
}

// “ест дл€ проверки вычислени€ сложного выражени€
TEST(PostfixCalculatorTest, Evaluate_ComplexExpression) {
	TableManager tableManager;
	PostfixCalculator calculator(tableManager);

	std::string postfixExpression = "2 3 + 5 *";
	Polynomial expected("25");

	Polynomial result = calculator.evaluate(postfixExpression);

	EXPECT_EQ(result, expected);
}

// “ест дл€ проверки вычислени€ выражени€ с большим количеством операций
TEST(PostfixCalculatorTest, Evaluate_LargeExpression) {
	TableManager tableManager;
	PostfixCalculator calculator(tableManager);

	std::string postfixExpression = "2 3 * 5 6 + -";
	Polynomial expected("-5");

	Polynomial result = calculator.evaluate(postfixExpression);

	EXPECT_EQ(result, expected);
}

