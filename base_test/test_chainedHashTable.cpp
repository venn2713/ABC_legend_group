#include <gtest.h>
#include "Polinom.h"


TEST(ChainedHashTable, DefaultConstructor) {
	ChainedHashTable table;
	ASSERT_EQ(table.size(), 0);
}

TEST(ChainedHashTable, CopyConstructor) {
	ChainedHashTable table1;
	table1.insert("key1", TList<Monom>());

	ChainedHashTable table2 = table1;

	ASSERT_EQ(table1.size(), table2.size());
	ASSERT_EQ(table1.find("key1")->getSize(), table2.find("key1")->getSize());
}

TEST(ChainedHashTable, AssignmentOperator) {
	ChainedHashTable table1;
	table1.insert("key1", TList<Monom>());

	ChainedHashTable table2;
	table2 = table1;

	ASSERT_EQ(table1.size(), table2.size());
	ASSERT_EQ(table1.find("key1")->getSize(), table2.find("key1")->getSize());
}

TEST(ChainedHashTable, DeleteData) {
	ChainedHashTable table;
	table.insert("key1", TList<Monom>());
	ASSERT_EQ(table.size(), 1);

	table.deleteData("key1");

	ASSERT_EQ(table.size(), 0);
}

TEST(ChainedHashTable, Find) {
	ChainedHashTable table;
	table.insert("key1", TList<Monom>());

	ASSERT_TRUE(table.find("key1") != nullptr);
}

TEST(ChainedHashTable, Insert) {
	ChainedHashTable table;
	table.insert("key1", TList<Monom>());

	ASSERT_EQ(table.size(), 1);
}

TEST(ChainedHashTable, ChangeKey) {
	ChainedHashTable table;
	table.insert("key2", TList<Monom>());
	table.changeKey("key2", "newKey");

	ASSERT_TRUE(table.find("newKey") == nullptr);
}

TEST(ChainedHashTable, Print) {
	ChainedHashTable table;
	table.insert("key1", TList<Monom>());

	testing::internal::CaptureStdout();
	table.print(std::cout, "key1");
	std::string output = testing::internal::GetCapturedStdout();
	ASSERT_FALSE(output.empty());
}

TEST(ChainedHashTable, PrintMissingKey) {
	ChainedHashTable table;
	table.insert("key1", TList<Monom>());

	testing::internal::CaptureStdout();
	table.print(std::cout, "missingKey");
	std::string output = testing::internal::GetCapturedStdout();
	ASSERT_TRUE(output.empty());
}

TEST(ChainedHashTable, DeleteDataMissingKey) {
	ChainedHashTable table;
	table.insert("key1", TList<Monom>());
	table.deleteData("missingKey");

	ASSERT_EQ(table.size(), 1);
}