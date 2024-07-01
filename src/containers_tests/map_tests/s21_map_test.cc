#include <iostream>
#include <map>

#include "../test.h"

TEST(MapTests, TestMapFirst) {
  s21::map<int, int> m;
  EXPECT_EQ(m.insert(4, 5).second, true);
  EXPECT_EQ(m.insert(3, 3).second, true);
  EXPECT_EQ(m.insert(8, 1).second, true);
  EXPECT_EQ(m.insert(6, 6).second, true);
  EXPECT_EQ(m.insert(-5, -5).second, true);
  EXPECT_EQ(m.insert(7, -3).second, true);
  std::map<int, int> chm;
  chm.insert({4, 5});
  chm.insert({3, 3});
  chm.insert({8, 1});
  chm.insert({6, 6});
  chm.insert({-5, -5});
  chm.insert({7, -3});
  auto iter = chm.begin();
  auto it = m.begin();
  for (; it != m.end() && iter != chm.end(); it++, iter++) {
    EXPECT_EQ(it->second, iter->second);
  }
}

TEST(MapTests, TestMapSecond) {
  s21::map<int, int> m;
  EXPECT_EQ(m.insert({4, 5}).second, true);
  EXPECT_EQ(m.insert({3, 3}).second, true);
  EXPECT_EQ(m.insert({8, 1}).second, true);
  EXPECT_EQ(m.insert({6, 6}).second, true);
  EXPECT_EQ(m.insert({-5, -5}).second, true);
  EXPECT_EQ(m.insert({7, -3}).second, true);
  std::map<int, int> chm;
  chm.insert({4, 5});
  chm.insert({3, 3});
  chm.insert({8, 1});
  chm.insert({6, 6});
  chm.insert({-5, -5});
  chm.insert({7, -3});
  auto iter = chm.begin();
  auto it = m.begin();
  for (; it != m.end() && iter != chm.end(); it++, iter++) {
    EXPECT_EQ(it->second, iter->second);
  }
}

TEST(MapTests, TestMapConstIterator1) {
  s21::map<int, int> m1{{2, 2}, {3, 3}, {1, 1}, {5, 5}};
  s21::map m2{m1};
  s21::map m3(std::move(m1));
  int check[]{1, 2, 3, 5};
  auto it2 = m2.begin();
  auto it3 = m3.begin();
  EXPECT_EQ(m1.empty(), true);
  for (int i{}; i < 4; i++, it2++, it3++) {
    EXPECT_EQ(it2->first, check[i]);
    EXPECT_EQ(it2->second, check[i]);
    EXPECT_EQ(it3->first, check[i]);
    EXPECT_EQ(it3->second, check[i]);
  }
}

TEST(MapTests, TestMapConstIterator2) {
  s21::map<int, int> m1{{2, 2}, {3, 3}, {1, 1}, {5, 5}};
  int arr[]{1, 2, 3, 5};
  s21::map<int, int>::iterator it = m1.begin();
  s21::map<int, int>::const_iterator cit = m1.begin();
  for(int i{}; cit != m1.end(); cit++, i++, it++) {
    EXPECT_EQ(arr[i], cit->first);
    EXPECT_EQ(arr[i], it->first);
    EXPECT_EQ(cit->second, it->second);
  }
}

TEST(MapTests, TestMapErase) {
  s21::map<int, int> m{{1, 2}, {5, 5}};
  int key[]{1, 5, 6, 8};
  int val[]{2, 5, -5, 9};
  int i{};
  auto it = m.end();
  EXPECT_EQ(m.erase(m.begin())->first, 5);
  EXPECT_EQ(m.begin()->first, 5);
  m.insert({1, 2});
  m.insert({8, 9});
  it = m.insert({3, 3}).first;
  m.insert({6, -5});
  it = m.erase(it);
  EXPECT_EQ(it->first, 5);
  for(auto pr : m) {
    EXPECT_EQ(pr.first, key[i]);
    EXPECT_EQ(pr.second, val[i]);
    i++;
  }
  while (!m.empty()) {
    EXPECT_EQ(m.size(), i);
    m.erase(m.begin());
    i--;
  }
  EXPECT_EQ(m.empty(), true);
}

TEST(MapTests, TestMapInsertMany) {
  s21::map<int, int> m{{1, 2}, {5, 5}};
  int i{};
  bool check[]{false, true, false};
  auto v = m.insert_many(std::pair{1, 1}, std::pair{-3, 2}, std::pair{5, 6});
  for(auto& pr : v) {
    EXPECT_EQ(pr.second, check[i]);
    i++;
  }
}