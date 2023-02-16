
#include "../includes/stack.hpp"

#include <gtest/gtest.h>

#include <iostream>
#include <stack>
#include <vector>

using ft::stack;
using std::vector;  // Change to vector when it's tested

// explicit stack(const Container& cont = Container());
TEST(StackConstructors, Constructor) {
  {
    vector<int> v(10, 10);
    stack<int>  s(v);
    EXPECT_EQ(s.size(), 10);
  }
}

// stack(const stack& other) : c(other.c);
TEST(StackConstructors, CopyConstructor) {
  {
    vector<int>    v(10, 10);
    stack<int> s1(v);
    stack<int> s2(s1);
    EXPECT_EQ(s1.size(), s2.size());
  }
}

// stack& operator=(const stack& other);
TEST(StackAssignment, CopyAssignment) {
  {  // TODO check for deep/shallow copy
    vector<int> vec_1(10);
    for (vector<int>::iterator it = vec_1.begin(); it != vec_1.end(); ++it) {
      *it = 24;
    }
    vector<int> vec_2(vec_1);
    vec_2.push_back(42);

    stack<int> stack_1(vec_1);
    stack<int> stack_2 = stack_1;
    stack<int> stack_3(vec_2);

    EXPECT_EQ(stack_1.size(), stack_2.size());
    EXPECT_TRUE(stack_1 == stack_2);
    EXPECT_TRUE(stack_1 < stack_3);
  }
}

// reference top();
TEST(StackElementAccess, Top) {
  {
    vector<int> v(10, 3);
    v.push_back(3);
    stack<int> s(v);
    EXPECT_EQ(s.top(), v.back());
  }
}

// bool empty() const;
TEST(StackCapacity, Empty) {
  {
    stack<int> s;
    EXPECT_TRUE(s.empty());
  }
  {
    vector<int> v(10, 3);
    v.push_back(3);
    stack<int> s(v);
    EXPECT_EQ(s.empty(), v.empty());
  }
}

// size_type size() const;
TEST(StackCapacity, Size) {
  {
    stack<int> s;
    EXPECT_EQ(s.size(), 0);
  }
  {
    vector<int> v(10, 3);
    v.push_back(3);
    stack<int> s(v);
    EXPECT_EQ(s.size(), v.size());
  }
}

// void push(const value_type& value)
TEST(StackModifiers, Push) {
  {
    stack<int> s;
    s.push(3);
    EXPECT_EQ(s.top(), 3);
  }
}

// void pop()
TEST(StackModifiers, Pop) {
  {
    stack<int> s;
    s.push(3);
    s.push(2);
    s.pop();
    EXPECT_EQ(s.top(), 3);
  }
}
