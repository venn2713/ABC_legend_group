#include <gtest.h>
#include "Polinom.h"


TEST(OrderedArrayTable, DefaultConstructor) {
	OrderedArrayTable table;

	ASSERT_EQ(table.size(), 0);
}

TEST(OrderedArrayTable, CopyConstructor) {
	OrderedArrayTable table1;
	table1.insert("key1", TList<Monom>());

	OrderedArrayTable table2 = table1;

	ASSERT_EQ(table1.size(), table2.size());
	ASSERT_EQ(table1.find("key1")->getSize(), table2.find("key1")->getSize());
}

TEST(OrderedArrayTable, AssignmentOperator) {
	OrderedArrayTable table1;
	table1.insert("key1", TList<Monom>());

	OrderedArrayTable table2;
	table2 = table1;

	ASSERT_EQ(table1.size(), table2.size());
	ASSERT_EQ(table1.find("key1")->getSize(), table2.find("key1")->getSize());
}

TEST(OrderedArrayTable, DeleteData) {
	OrderedArrayTable table;
	table.insert("key1", TList<Monom>());
	ASSERT_EQ(table.size(), 1);

	table.deleteData("key1");

	ASSERT_EQ(table.size(), 0);
}

TEST(OrderedArrayTable, Find) {
	OrderedArrayTable table;
	table.insert("key1", TList<Monom>());

	ASSERT_TRUE(table.find("key1") != nullptr);
}

TEST(OrderedArrayTable, Insert) {
	OrderedArrayTable table;
	table.insert("key1", TList<Monom>());

	ASSERT_EQ(table.size(), 1);
}

TEST(OrderedArrayTable, ChangeKey) {
	OrderedArrayTable table;
	table.insert("key1", TList<Monom>());
	table.changeKey("key1", "newKey");

	ASSERT_TRUE(table.find("newKey") != nullptr);
}

TEST(OrderedArrayTable, Print) {
	OrderedArrayTable table;
	table.insert("key1", TList<Monom>());

	testing::internal::CaptureStdout();
	table.print(std::cout, "key1");
	std::string output = testing::internal::GetCapturedStdout();
	ASSERT_FALSE(output.empty());
}

TEST(OrderedArrayTable, PrintMissingKey) {
	OrderedArrayTable table;
	table.insert("key1", TList<Monom>());

	testing::internal::CaptureStdout();
	table.print(std::cout, "missingKey");
	std::string output = testing::internal::GetCapturedStdout();
	ASSERT_TRUE(output.empty());
}

TEST(OrderedArrayTable, DeleteDataMissingKey) {
	OrderedArrayTable table;
	table.insert("key1", TList<Monom>());
	table.deleteData("missingKey");

	ASSERT_EQ(table.size(), 1);
}
