#include <gtest.h>
#include "Polinom.h"

TEST(LinkedTable, DefaultConstructor) {
	LinkedTable table;

	ASSERT_EQ(table.size(), 0);
}

TEST(LinkedTable, CopyConstructor) {
	LinkedTable table1;
	table1.insert("key1", TList<Monom>());

	LinkedTable table2 = table1;

	ASSERT_EQ(table1.size(), table2.size());
	ASSERT_EQ(table1.find("key1")->getSize(), table2.find("key1")->getSize());
}

TEST(LinkedTable, AssignmentOperator) {
	LinkedTable table1;
	table1.insert("key1", TList<Monom>());

	LinkedTable table2;
	table2 = table1;

	ASSERT_EQ(table1.size(), table2.size());
	ASSERT_EQ(table1.find("key1")->getSize(), table2.find("key1")->getSize());
}

TEST(LinkedTable, DeleteData) {
	LinkedTable table;
	table.insert("key1", TList<Monom>());
	ASSERT_EQ(table.size(), 1);
   
	table.deleteData("key1");
	ASSERT_EQ(table.size(), 0);
}

TEST(LinkedTable, Find) {
	LinkedTable table;
	table.insert("key1", TList<Monom>());

	ASSERT_TRUE(table.find("key1") != nullptr);
}

TEST(LinkedTable, Insert) {
	LinkedTable table;
	table.insert("key1", TList<Monom>());

	ASSERT_EQ(table.size(), 1);
}

TEST(LinkedTable, ChangeKey) {
	LinkedTable table;
	table.insert("key1", TList<Monom>());
	table.changeKey("key1", "newKey");

	ASSERT_TRUE(table.find("newKey") != nullptr);
}

TEST(LinkedTable, Print) {
	LinkedTable table;
	table.insert("key1", TList<Monom>());

	testing::internal::CaptureStdout();
	table.print(std::cout, "key1");
	std::string output = testing::internal::GetCapturedStdout();
	ASSERT_FALSE(output.empty());
}

TEST(LinkedTable, PrintMissingKey) {
	LinkedTable table;
	table.insert("key1", TList<Monom>());

	testing::internal::CaptureStdout();
	table.print(std::cout, "missingKey");
	std::string output = testing::internal::GetCapturedStdout();
	ASSERT_TRUE(output.empty());
}

TEST(LinkedTable, DeleteDataMissingKey) {
	LinkedTable table;
	table.insert("key1", TList<Monom>());
	table.deleteData("missingKey");

	ASSERT_EQ(table.size(), 1);
}
