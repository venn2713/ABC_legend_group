#include <gtest.h>
#include "Polinom.h"
#include "Polinom.cpp"

TEST(Polinom, DefConstructor) {
	Polinom polinom;

	ASSERT_TRUE(polinom.isEmpty());
}

TEST(Polinom, StrConstructor) {
	Polinom polinom("pol-3", "3x^2y^5z^5+2x^3y^3");

	ASSERT_FALSE(polinom.isEmpty());
}

TEST(Polinom, CopyConstructor) {
	Polinom polinom1("pol-2", "3x^2y^5z^5+2x^3y^3");
	Polinom polinom2 = polinom1;

	ASSERT_EQ(polinom1.Calculation(1, 2, 3), polinom2.Calculation(1, 2, 3));
}

TEST(Polinom, Assignment) {
	Polinom polinom1("pol-1", "3x^2y^5z^5+2x^3y^3");
	Polinom polinom2;
	polinom2 = polinom1;

	ASSERT_EQ(polinom1.Calculation(1, 2, 3), polinom2.Calculation(1, 2, 3));
}


TEST(Polinom, Addition) {
	Polinom polinom1("pol0", "3x^2y^2+2x^3z^2");
	Polinom polinom2("pol1", "4x^2y^2+3x^3y^2");
	Polinom res = polinom1 + polinom2;

	ASSERT_EQ(res.Calculation(1, 1, 1), 12);
}

TEST(Polinom, ChangeName) {
	Polinom polinom("pol2", "3x^2y^5z^5+2x^3y^3");
	polinom.setName("pol3", "newName");

	ASSERT_EQ(polinom.getName(), "newName");
}

TEST(Polinom, CombineLikeTerms) {
	Polinom polinom("pol4", "3x^2y^5z^5+2x^3y^3+3x^2y^5z^5");

	ASSERT_EQ(polinom.getSize(), 2);
}

TEST(Polinom, Subtraction) {
	Polinom polinom3("pol5", "4x^2y^2+3x^3y^2");
	Polinom polinom4("pol6", "3x^2y^2+2x^3z^2");
	Polinom res_1 = polinom3 - polinom4;

	ASSERT_EQ(res_1.Calculation(1, 1, 1), 2);
}

TEST(Polinom, Multiplication) {
	Polinom polinom1("pol7", "2x^3z^2");
	Polinom polinom2("pol8", "3x^3y^2");
	Polinom res = polinom1 * polinom2;

	ASSERT_EQ(res.Calculation(1, 2, 2), 96);
}

TEST(Polinom, MultiplyByConst) {
	Polinom polinom("pol9", "3x^2y^5z^5+2x^3y^3");
	Polinom res = polinom.MultiplyByConst(5);

	ASSERT_EQ(res.Calculation(1, 1, 1), 25);
}

TEST(Polinom, Calculation) {
	Polinom polinom("pol10", "3x^2y^5z^5+2x^3y^3");

	ASSERT_DOUBLE_EQ(polinom.Calculation(1, 2, 2), 3088);
}