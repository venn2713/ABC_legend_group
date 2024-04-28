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

TEST(StackTest, PushToEmptyStack) {
	Stack<int> stack;
	stack.push(5);
	EXPECT_EQ(stack.top(), 5);
}

TEST(StackTest, PushMultipleElements) {
	Stack<int> stack;
	stack.push(5);
	stack.push(10);
	stack.push(15);
	EXPECT_EQ(stack.top(), 15);
}

TEST(StackTest, PopFromStack) {
	Stack<int> stack;
	stack.push(5);
	stack.push(10);
	int popped = stack.pop();
	EXPECT_EQ(popped, 10);
	EXPECT_EQ(stack.top(), 5);
}

TEST(StackTest, PopFromEmptyStack) {
	Stack<int> stack;
	EXPECT_THROW(stack.pop(), std::runtime_error);
}

TEST(StackTest, TopOfEmptyStack) {
	Stack<int> stack;
	EXPECT_THROW(stack.top(), std::runtime_error);
}

TEST(StackTest, IsEmptyAfterPush) {
	Stack<int> stack;
	stack.push(5);
	EXPECT_FALSE(stack.isEmpty());
}

TEST(StackTest, IsEmptyAfterPopAll) {
	Stack<int> stack;
	stack.push(5);
	stack.pop();
	EXPECT_TRUE(stack.isEmpty());
}

TEST(StackTest, TopWithoutPop) {
	Stack<int> stack;
	stack.push(5);
	EXPECT_EQ(stack.top(), 5);
	EXPECT_FALSE(stack.isEmpty());
}

TEST(StackTest, PushPopStrings) {
	Stack<std::string> stack;
	stack.push("hello");
	stack.push("world");
	EXPECT_EQ(stack.pop(), "world");
	EXPECT_EQ(stack.top(), "hello");
}

TEST(StackTest, PushPopStructs) {
	struct Point { int x; int y; };
	Stack<Point> stack;
	Point p1 = { 1, 2 };
	stack.push(p1);
	EXPECT_EQ(stack.top().x, 1);
	EXPECT_EQ(stack.top().y, 2);
}
