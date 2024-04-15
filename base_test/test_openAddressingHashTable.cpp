#include <gtest.h>
#include "Polinom.h"

TEST(OpenAddressingHashTable, DefaultConstructor) {
	OpenAddressingHashTable table;

	ASSERT_EQ(table.size(), 0);
}

TEST(OpenAddressingHashTable, CopyConstructor) {
	OpenAddressingHashTable table1;
	table1.insert("key1", TList<Monom>());

	OpenAddressingHashTable table2 = table1;

	ASSERT_EQ(table1.size(), table2.size());
	ASSERT_EQ(table1.find("key1")->getSize(), table2.find("key1")->getSize());
}

TEST(OpenAddressingHashTable, AssignmentOperator) {
	OpenAddressingHashTable table1;
	table1.insert("key1", TList<Monom>());

	OpenAddressingHashTable table2;
	table2 = table1;

	ASSERT_EQ(table1.size(), table2.size());
	ASSERT_EQ(table1.find("key1")->getSize(), table2.find("key1")->getSize());
}

TEST(OpenAddressingHashTable, DeleteData) {
	OpenAddressingHashTable table;
	table.insert("key1", TList<Monom>());
	ASSERT_EQ(table.size(), 1);

	table.deleteData("key1");

	ASSERT_EQ(table.size(), 0);
}

TEST(OpenAddressingHashTable, Find) {
	OpenAddressingHashTable table;
	table.insert("key1", TList<Monom>());

	ASSERT_TRUE(table.find("key1") != nullptr);
}

TEST(OpenAddressingHashTable, Insert) {
	OpenAddressingHashTable table;
	table.insert("key1", TList<Monom>());

	ASSERT_EQ(table.size(), 1);
}

TEST(OpenAddressingHashTable, ChangeKey) {
	OpenAddressingHashTable table;
	table.insert("key1", TList<Monom>());
	table.changeKey("key1", "newKey");

	ASSERT_TRUE(table.find("newKey") != nullptr);
}

TEST(OpenAddressingHashTable, Print) {
	OpenAddressingHashTable table;
	table.insert("key1", TList<Monom>());

	testing::internal::CaptureStdout();
	table.print(std::cout, "key1");
	std::string output = testing::internal::GetCapturedStdout();
	ASSERT_FALSE(output.empty());
}

TEST(OpenAddressingHashTable, PrintMissingKey) {
	OpenAddressingHashTable table;
	table.insert("key1", TList<Monom>());

	testing::internal::CaptureStdout();
	table.print(std::cout, "missingKey");
	std::string output = testing::internal::GetCapturedStdout();
	ASSERT_TRUE(output.empty());
}

TEST(OpenAddressingHashTable, DeleteDataMissingKey) {
	OpenAddressingHashTable table;
	table.insert("key1", TList<Monom>());
	table.deleteData("missingKey");

	ASSERT_EQ(table.size(), 1);
}
