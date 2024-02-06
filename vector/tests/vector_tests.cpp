#include "tests.h"

using namespace s21;

void printVec(vector<int> vec) {
  std::cout << "size: " << vec.size() << std::endl;
  std::cout << "capacity: " << vec.capacity() << std::endl;
  std::cout << "{";
  for (size_t i = 0; i < vec.size() - 1; i++) {
    std::cout << vec.at(i) << ", ";
  }
  std::cout << vec.at(vec.size() - 1) << "}\n";
  std::cout << std::endl;
}

TEST(Constructors, constructor1) { vector<int> v; }

TEST(Constructors, constructor2) { vector<int> v(5); }

TEST(Constructors, constructor3) { vector<int> v{1, 2, 3, 4, 5}; }

TEST(Constructors, constructor4) {
  vector<int> v1{1, 2, 3, 4, 5};
  vector<int> v2(v1);
}

TEST(Constructors, constructor5) {
  vector<int> v1{1, 2, 3, 4, 5};
  vector<int> v2(std::move(v1));
}

TEST(Constructors, constructor6) {
  vector<int> v1{1, 2, 3, 4, 5};
  vector<int> v2 = v1;
  printVec(v2);
}

//  -------------------------------------------

TEST(ElementAccess, element_access1) {
  vector<int> v{1, 2, 3, 4, 5};
  EXPECT_EQ(v.at(3), 4);
}

TEST(ElementAccess, element_access2) {
  vector<int> v{1, 2, 3, 4, 5};
  EXPECT_EQ(v[3], 4);
}

TEST(ElementAccess, element_access3) {
  vector<int> v{1, 2, 3, 4, 5};
  EXPECT_EQ(v.front(), 1);
}

TEST(ElementAccess, element_access4) {
  vector<int> v{1, 2, 3, 4, 5};
  EXPECT_EQ(v.back(), 5);
}

TEST(ElementAccess, element_access5) {
  vector<int> v{1, 2, 3, 4, 5};
  int *v_ptr = v.data();
  *v_ptr = 20;
  EXPECT_EQ(v.front(), 20);
}

//  -------------------------------------------

TEST(Iterators, iterator1) {
  int i = 1;
  vector<int> v{1, 2, 3, 4, 5};
  for (auto vec = v.begin(); vec != v.end(); vec++) {
    EXPECT_EQ(*vec, i++);
  }
}

//  -------------------------------------------

TEST(Capacity, capacity1) {
  vector<int> v;
  ASSERT_TRUE(v.empty());
}

TEST(Capacity, capacity2) {
  vector<int> v{1, 2, 3, 4, 5};
  ASSERT_FALSE(v.empty());
}

TEST(Capacity, capacity3) {
  vector<int> v{1, 2, 3, 4, 5};
  EXPECT_EQ(v.size(), 5);
}

TEST(Capacity, capacity4) {
  vector<int> v;
  EXPECT_EQ(v.size(), 0);
}

// TEST(Capacity, capacity5) {
//   vector<int> v;
//   vector::vector<int> V;
//   EXPECT_EQ(v.max_size(), V.max_size());
// }

TEST(Capacity, capacity6) {
  vector<int> v{1, 2, 3, 4, 5};
  v.reserve(10);
  EXPECT_EQ(v.capacity(), 10);
  EXPECT_EQ(v.size(), 5);
}

TEST(Capacity, capacity7) {
  vector<int> v{1, 2, 3, 4, 5};
  v.reserve(2);
  EXPECT_EQ(v.capacity(), 2);
  EXPECT_EQ(v.size(), 2);
}

TEST(Capacity, capacity8) {
  vector<int> v{1, 2, 3, 4, 5};
  v.reserve(10);
  EXPECT_EQ(v.capacity(), 10);
  EXPECT_EQ(v.size(), 5);
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), 5);
  EXPECT_EQ(v.size(), 5);
}

TEST(Modifiers, modifier1) {
  vector<int> v{1, 2, 3, 4, 5};
  v.clear();
  EXPECT_EQ(v.size(), 0);
}

TEST(Modifiers, modifier2) {
  vector<int> v{1, 2, 3, 4, 5};
  v.erase(v.begin() + 2);
  EXPECT_EQ(v.at(2), 4);
}

// TEST(Modifiers, modifier3) {
//   vector<int> v{1, 2, 3, 4, 5};
//   v.erase(v.begin() + v.size() + 10);
//   EXPECT_EQ(v.at(2), 5);
// }

TEST(Modifiers, modifier4) {
  vector<int> v{1, 2, 3, 4, 5};
  v.push_back(6);
  v.push_back(610);
  EXPECT_EQ(v.at(5), 6);
  EXPECT_EQ(v.at(6), 610);
}

TEST(Modifiers, modifier5) {
  vector<int> v{1, 2, 3, 4, 5};
  v.push_back(6);
  v.push_back(610);
  EXPECT_EQ(v.at(5), 6);
  EXPECT_EQ(v.at(6), 610);
  v.pop_back();
  EXPECT_EQ(v.back(), 6);
  v.pop_back();
  EXPECT_EQ(v.back(), 5);
  v.push_back(1337);
  v.push_back(228);
  EXPECT_EQ(v.at(5), 1337);
  EXPECT_EQ(v.at(6), 228);
}

TEST(Modifiers, modifier6) {
  vector<int> v1{1, 2, 3, 4, 5};
  vector<int> v2{6, 7, 8};

  v1.swap(v2);

  EXPECT_EQ(v1.size(), 3);
  EXPECT_EQ(v2.size(), 5);

  EXPECT_EQ(v1.capacity(), 3);
  EXPECT_EQ(v2.capacity(), 5);

  EXPECT_EQ(v1.at(1), 7);
  EXPECT_EQ(v2.at(1), 2);
}

TEST(Modifiers, modifier7) {
  vector<int> v{1, 2, 3, 4, 5};
  v.insert(v.begin() + 1, 111111);
  EXPECT_EQ(v.at(1), 111111);
}

TEST(Modifiers, modifier8) {
  vector<int> v{1, 2, 3, 4, 5};
  v.insert(v.begin() + 1, 111111);
  v.insert(v.begin() + 3, 222222);
  EXPECT_EQ(v.at(1), 111111);
}

// TEST(Modifiers, modifier9) {
//   vector<int> v{1, 2, 3, 4, 5};
//   v.insert(v.begin() - 2, 6);
//   EXPECT_EQ(v.at(1), 6);
//   printVec(v);
// }
