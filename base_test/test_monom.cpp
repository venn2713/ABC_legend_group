#include <gtest.h>
#include "Monom.h"

TEST(Monom, CreatMonom) {
	Monom monom(2.0, 321);

	EXPECT_DOUBLE_EQ(monom.coef, 2.0);
	EXPECT_EQ(monom.degree, 321);
}

TEST(Monom, Calculation) {
	Monom monom(2.0, 321);

	EXPECT_DOUBLE_EQ(monom.calculationMonomial(2.0, 3.0, 4.0), 2.0 * pow(2.0, 3) * pow(3.0, 2) * pow(4.0, 1));
}

TEST(Monom, GetDegree) {
	Monom monom(2.0, 321);

	EXPECT_EQ(monom.getDegree(), 321);
}

TEST(Monom, GetCoef) {
	Monom monom(2.0, 321);

	EXPECT_DOUBLE_EQ(monom.getCoef(), 2.0);
}

TEST(Monom, Equality) {
	Monom monom1(2.0, 321);
	Monom monom2(2.0, 321);

	ASSERT_TRUE(monom1 == monom2);
}

TEST(Monom, Inequality) {
	Monom monom1(2.0, 321);
	Monom monom2(2.0, 421);

	ASSERT_TRUE(monom1 != monom2);
}

TEST(Monom, Addition) {
	Monom monom1(2.0, 321);
	Monom monom2(3.0, 321);

	Monom result = monom1 + monom2;

	EXPECT_EQ(result.coef, 5.0);
	EXPECT_EQ(result.degree, 321);
}

TEST(Monom, Subtraction) {
	Monom monom1(3.0, 321);
	Monom monom2(2.0, 321);

	Monom result = monom1 - monom2;

	EXPECT_EQ(result.coef, 1.0);
	EXPECT_EQ(result.degree, 321);
}

TEST(Monom, Multiplication) {
	Monom monom1(2.0, 321);
	Monom monom2(3.0, 321);

	Monom result = monom1 * monom2;

	EXPECT_EQ(result.coef, 6.0);
	EXPECT_EQ(result.degree, 642);
}

TEST(Monom, LessThan) {
	Monom monom1(2.0, 321);
	Monom monom2(2.0, 421);

	ASSERT_TRUE(monom1 < monom2);
}

TEST(Monom, OutputOperator) {
	Monom monom(2.0, 321);
	std::ostringstream oss;
	oss << monom;

	EXPECT_EQ(oss.str(), "2x^3y^2z");
}