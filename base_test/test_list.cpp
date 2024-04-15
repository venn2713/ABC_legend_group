#include <gtest.h>
#include "Polinom.h"

TEST(TList, CreateList) {
	TList<int> myList;

	EXPECT_EQ(myList.getSize(), 0);
	EXPECT_TRUE(myList.isEmpty());
}

TEST(TList, popFront) {
	TList<int> myList;

	myList.pushBack(42);
	myList.popFront();

	EXPECT_TRUE(myList.isEmpty());
}

TEST(TList, clear) {
	TList<int> myList;
	myList.pushBack(42);
	myList.pushBack(99);

	EXPECT_EQ(myList.getSize(), 2);

	myList.clear();

	EXPECT_TRUE(myList.isEmpty());
	EXPECT_EQ(myList.getSize(), 0);
}

TEST(TList, pushBack) {
	TList<int> myList;
	myList.pushBack(1);
	myList.pushBack(2);

	EXPECT_EQ(myList.getSize(), 2);
	EXPECT_EQ(myList.getValueAtPosition(1), 2);
}

TEST(TList, pushFront) {
	TList<int> myList;
	myList.pushFront(1);
	myList.pushFront(2);

	EXPECT_EQ(myList.getSize(), 2);
	EXPECT_EQ(myList.getFront(), 2);
}

TEST(TList, insertNodeAfter) {
	TList<int> myList;
	myList.pushBack(1);
	myList.pushBack(3);

	myList.insertNodeAfter(0, 2);

	EXPECT_EQ(myList.getSize(), 3);
	EXPECT_EQ(myList.getValueAtPosition(1), 2);

	myList.insertNodeAfter(2, 4);

	EXPECT_EQ(myList.getSize(), 4);
	EXPECT_EQ(myList.getValueAtPosition(3), 4);
}

TEST(TList, removeNodeAfter) {
	TList<int> myList;
	myList.pushBack(1);
	myList.pushBack(2);
	myList.pushBack(3);

	myList.removeNodeAfter(0);

	EXPECT_EQ(myList.getSize(), 2);
	EXPECT_EQ(myList.getValueAtPosition(1), 3);

	myList.removeNodeAfter(0);

	EXPECT_EQ(myList.getSize(), 1);
}

TEST(TList, CopyConstructor) {
	TList<int> originalList;
	originalList.pushBack(1);
	originalList.pushBack(2);
	originalList.pushBack(3);

	TList<int> copiedList(originalList);

	EXPECT_EQ(originalList.getSize(), copiedList.getSize());
	EXPECT_EQ(originalList.getFront(), copiedList.getFront());

	originalList.pushBack(4);

	EXPECT_NE(originalList.getSize(), copiedList.getSize());
}
