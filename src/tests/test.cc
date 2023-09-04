#include <gtest/gtest.h>

#include <map>
#include <set>
#include <unordered_map>

#include "../my_map.h"
#include "../my_set.h"
#include "../my_multiset.h"


TEST(MultiSetConstructorTest, DefaultConstructor) {
  STL::multiset<int> defaultSet;

  EXPECT_EQ(defaultSet.size(), 0);
}

TEST(MultiSetConstructorTest, RangeConstructor) {
  STL::multiset<int> rangeSet{5, 10, 5, 7};
  EXPECT_EQ(rangeSet.size(), 4);
  EXPECT_EQ(rangeSet.count(5), 2);
  EXPECT_EQ(rangeSet.count(10), 1);
  EXPECT_EQ(rangeSet.count(7), 1);
}

TEST(MultiSetConstructorTest, CopyConstructor) {
  STL::multiset<int> originalSet{5, 10, 5, 7};
  STL::multiset<int> copySet(originalSet);

  EXPECT_EQ(copySet.size(), 3);
  EXPECT_EQ(*originalSet.begin(), *copySet.begin());
}

TEST(MultiSetTest, MoveConstructor) {
  STL::multiset<int> originalSet{5, 10, 5, 7};
  STL::multiset<int> movedSet(std::move(originalSet));

  EXPECT_EQ(movedSet.size(), 4);
  EXPECT_EQ(originalSet.size(), 0);
}

TEST(MultiSetTest, CopyAssignmentOperator) {
  STL::multiset<int> originalSet{5, 10, 5, 7};
  STL::multiset<int> assignedSet;

  assignedSet = originalSet;

  EXPECT_EQ(assignedSet.size(), 3);
  EXPECT_EQ(*assignedSet.begin(), *originalSet.begin());
}

TEST(MultiSetTest, MoveAssignmentOperator) {
  STL::multiset<int> originalSet{5, 10, 5, 7};
  STL::multiset<int> movedSet;

  movedSet = std::move(originalSet);

  EXPECT_EQ(movedSet.size(), 4);
  EXPECT_EQ(originalSet.size(), 0);
}

TEST(MultiSetTest, EmptyMethodOnEmptySet) {
  STL::multiset<int> emptySet;

  EXPECT_TRUE(emptySet.empty());
}

TEST(MultiSetTest, EmptyMethodOnNonEmptySet) {
  STL::multiset<int> nonEmptySet{5, 10, 5, 7};

  EXPECT_FALSE(nonEmptySet.empty());
}

TEST(MultiSetTest, InsertReturnValue) {
  STL::multiset<int> testSet;

  auto [it1, inserted1] = testSet.insert(5);
  EXPECT_EQ(*it1, 5);

  auto [it2, inserted2] = testSet.insert(10);
  EXPECT_EQ(*it2, 10);

  auto [it3, inserted3] = testSet.insert(5);
  EXPECT_EQ(*it3, 5);

  EXPECT_EQ(testSet.size(), 3);
}

TEST(MultiSetTest, EraseMethod) {
  STL::multiset<int> testSet{5, 10, 5, 7};

  auto it = testSet.begin();
  ++it;

  testSet.erase(it);

  EXPECT_EQ(testSet.size(), 3);
  EXPECT_EQ(testSet.count(10), 1);
}

TEST(MultiSetTest, SwapMethod) {
  STL::multiset<int> set1{5, 10, 5, 7};
  STL::multiset<int> set2{3, 8, 3};

  set1.swap(set2);

  EXPECT_EQ(set1.size(), 3);
  EXPECT_EQ(set1.count(3), 2);
  EXPECT_EQ(set1.count(8), 1);

  EXPECT_EQ(set2.size(), 4);
  EXPECT_EQ(set2.count(5), 2);
  EXPECT_EQ(set2.count(7), 1);
  EXPECT_EQ(set2.count(10), 1);
}

TEST(MultiSetTest, MergeMethod) {
  STL::multiset<int> set1{5, 10, 5, 7};
  STL::multiset<int> set2{3, 8, 3};

  set1.merge(set2);

  EXPECT_EQ(set1.size(), 7);
  EXPECT_EQ(set1.count(3), 2);
  EXPECT_EQ(set1.count(5), 2);
  EXPECT_EQ(set1.count(7), 1);
  EXPECT_EQ(set1.count(8), 1);
  EXPECT_EQ(set1.count(10), 1);

  EXPECT_EQ(set2.size(), 0);
}

TEST(MultiSetTest, FindMethod) {
  STL::multiset<int> testSet{5, 10, 5, 7};

  auto it1 = testSet.find(5);
  EXPECT_EQ(*it1, 5);

  auto it2 = testSet.find(10);
  EXPECT_EQ(*it2, 10);

  auto it3 = testSet.find(15);
  EXPECT_EQ(it3, testSet.end());
}

TEST(MultiSetTest, ContainsMethod) {
  STL::multiset<int> testSet{5, 10, 5, 7};

  EXPECT_TRUE(testSet.contains(5));
  EXPECT_TRUE(testSet.contains(10));
  EXPECT_FALSE(testSet.contains(15));
}

TEST(MultiSetTest, LowerBoundMethod) {
  STL::multiset<int> testSet{5, 10, 15, 20, 25};

  auto it1 = testSet.lower_bound(10);
  EXPECT_EQ(*it1, 10);

  auto it2 = testSet.lower_bound(17);
  EXPECT_EQ(*it2, 20);

  auto it3 = testSet.lower_bound(30);
  EXPECT_EQ(it3, testSet.end());
}

TEST(MultiSetTest, UpperBoundMethod) {
  STL::multiset<int> testSet{5, 10, 15, 20, 25};

  auto it1 = testSet.upper_bound(10);
  EXPECT_EQ(*it1, 15);

  auto it2 = testSet.upper_bound(17);
  EXPECT_EQ(*it2, 20);

  auto it3 = testSet.upper_bound(30);
  EXPECT_EQ(it3, testSet.end());
}

TEST(Map, Constructor_Default) {
  STL::map<int, std::string> STL_map;
  std::map<int, std::string> std_map;
  EXPECT_EQ(STL_map.size(), std_map.size());
  EXPECT_EQ(STL_map.empty(), std_map.empty());
}

TEST(Map, Constructor_Initializer_list) {
  STL::map<int, std::string> STL_map{
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  std::map<int, std::string> std_map = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  EXPECT_EQ(STL_map.size(), std_map.size());
  EXPECT_EQ(STL_map.empty(), std_map.empty());
}

TEST(Map, Constructor_Copy) {
  STL::map<int, std::string> STL_map_1{
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  std::map<int, std::string> std_map_1 = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  STL::map<int, std::string> STL_map_2 = STL_map_1;
  std::map<int, std::string> std_map_2 = std_map_1;

  EXPECT_EQ(STL_map_1.size(), STL_map_2.size());
  EXPECT_EQ(std_map_1.size(), std_map_2.size());
  auto it1 = STL_map_1.begin();
  auto it2 = STL_map_2.begin();
  while (it1 != STL_map_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
}

TEST(Map, Constructor_Move) {
  STL::map<int, std::string> STL_map_1{
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  std::map<int, std::string> std_map_1 = {
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  STL::map<int, std::string> STL_map_2 = std::move(STL_map_1);
  std::map<int, std::string> std_map_2 = std::move(std_map_1);

  EXPECT_EQ(STL_map_2.size(), std_map_2.size());
  EXPECT_EQ(STL_map_1.size(), std_map_1.size());
  EXPECT_EQ(STL_map_1.empty(), std_map_1.empty());
  auto it1 = STL_map_2.begin();
  auto it2 = std_map_2.begin();

  while (it1 != STL_map_2.end()) {
    // auto it_res = *it1.operator*().first;

    EXPECT_EQ(it1.operator*().first, it2.operator*().first);
    EXPECT_EQ(it1.operator*().second, it2.operator*().second);

    ++it1, ++it2;
  }
}

TEST(Map, Modifier_Insert) {
  STL::map<char, int> STL_map_1{{'b', 228}, {'c', 1337}};
  STL::map<char, int> STL_map_2{
      {'b', 228},
      {'c', 1337},
      {'d', 322},
      {'a', 5},
  };

  EXPECT_EQ(STL_map_1.insert('d', 322).second, true);

  std::pair<char, int> pair1('a', 5);
  std::pair<char, int> pair2('a', 28);

  EXPECT_EQ(STL_map_1.insert(pair1).second, true);
  EXPECT_EQ(STL_map_1.insert(pair2).second, false);

  auto it1 = STL_map_1.begin();
  auto it2 = STL_map_2.begin();
  while (it1 != STL_map_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(STL_map_1.size(), STL_map_2.size());
}

TEST(Map, Rehash_And_Insert_In_Collision) {
  STL::map<std::string, int> STL_map;
  STL_map.insert("asd", 0);
  STL_map.insert("asa", 1);
  STL_map.insert("asf", 2);
  STL_map.insert("asg", 3);
  STL_map.insert("ash", 4);
  STL_map.insert("aqw", 5);
  STL_map.insert("fgh", 6);
  STL_map.insert("ghf", 7);
  STL_map.insert("dghfg", 8);
  STL_map.insert("dghfdsg", 9);
  STL_map.insert("dghfgfsadfsd", 10);
  STL_map.insert("dghfgfsadfsdasd", 11);
  STL_map.insert("dghfgfsadfsasdasdd", 12);
  STL_map.insert("dghfgfsadfsdasdasd", 13);
  STL_map.insert("dghfgfdsasadfdsasasdsadsad", 14);
  STL_map.insert("dghdsafgfsadfdsasasdsadsad", 15);
  STL_map.insert("ådsdghfgfsadfdsasasdsadsad", 16);
  STL_map.insert("dghfgfsadfdsasasdsaddsasad", 17);
  STL_map.insert("dghfgfsadfdsasassadadsadsad", 18);
  STL_map.insert("dghfgfsadfdsasdasasdsadsad", 19);
  STL_map.insert("dghasdaasdfgfsadfsasdsadsad", 20);
  STL_map.insert("asddghfgfsadfsasaß∂asdsadsad", 21);
  STL_map.insert("dghfgfsadfasdsasdsadsad", 22);
  STL_map.insert("dghfgfsadfsasdsadsad", 23);
  STL_map.insert("dghfgfsasdadfsasdsadsad", 24);
  STL_map.insert("asdsadadghfgfsadfsasdsadsad", 25);

  std::unordered_map<std::string, int> std_map;
  std_map.insert(std::pair<std::string, int>("asd", 0));
  std_map.insert(std::pair<std::string, int>("asa", 1));
  std_map.insert(std::pair<std::string, int>("asf", 2));
  std_map.insert(std::pair<std::string, int>("asg", 3));
  std_map.insert(std::pair<std::string, int>("ash", 4));
  std_map.insert(std::pair<std::string, int>("aqw", 5));
  std_map.insert(std::pair<std::string, int>("fgh", 6));
  std_map.insert(std::pair<std::string, int>("ghf", 7));
  std_map.insert(std::pair<std::string, int>("dghfg", 8));
  std_map.insert(std::pair<std::string, int>("dghfdsg", 9));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsd", 10));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsdasd", 11));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsasdasdd", 12));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsdasdasd", 13));
  std_map.insert(std::pair<std::string, int>("dghfgfdsasadfdsasasdsadsad", 14));
  std_map.insert(std::pair<std::string, int>("dghdsafgfsadfdsasasdsadsad", 15));
  std_map.insert(std::pair<std::string, int>("ådsdghfgfsadfdsasasdsadsad", 16));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfdsasasdsaddsasad", 17));
  std_map.insert(
      std::pair<std::string, int>("dghfgfsadfdsasassadadsadsad", 18));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfdsasdasasdsadsad", 19));
  std_map.insert(
      std::pair<std::string, int>("dghasdaasdfgfsadfsasdsadsad", 20));
  std_map.insert(
      std::pair<std::string, int>("asddghfgfsadfsasaß∂asdsadsad", 21));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfasdsasdsadsad", 22));
  std_map.insert(std::pair<std::string, int>("dghfgfsadfsasdsadsad", 23));
  std_map.insert(std::pair<std::string, int>("dghfgfsasdadfsasdsadsad", 24));
  std_map.insert(
      std::pair<std::string, int>("asdsadadghfgfsadfsasdsadsad", 25));
  for (auto i : std_map) {
    EXPECT_EQ(i.second, STL_map[i.first]);
  }
  EXPECT_EQ(STL_map.size(), std_map.size());
}

TEST(Map, Modifier_Get_Value) {
  STL::map<std::string, int> m;
  m["123"] = 5;
  EXPECT_EQ(5, m["123"]);
}

TEST(Map, Modifier_Insert_or_assign) {
  STL::map<char, int> STL_map_1{{'b', 228}, {'c', 1337}};
  STL::map<char, int> STL_map_2{
      {'b', 228},
      {'c', 1337},
      {'d', 14},
      {'a', 28},
  };

  EXPECT_EQ(STL_map_1.insert_or_assign('d', 322).second, true);
  EXPECT_EQ(STL_map_1.insert_or_assign('d', 14).second, false);

  EXPECT_EQ(STL_map_1.insert_or_assign('a', 5).second, true);
  EXPECT_EQ(STL_map_1.insert_or_assign('a', 28).second, false);

  auto it1 = STL_map_1.begin();
  auto it2 = STL_map_2.begin();
  while (it1 != STL_map_1.end()) {
    EXPECT_EQ(*it1, *it2);
    ++it1, ++it2;
  }
  EXPECT_EQ(STL_map_1.size(), STL_map_2.size());
}

TEST(Map, Modifier_Erase_1) {
  STL::map<int, std::string> STL_map_1{
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  STL::map<int, std::string> STL_map_2{
      {1, "aboba"}, {3, "amogus"}, {4, "abobus"}};
  auto it = STL_map_1.begin();
  ++it;
  STL_map_1.erase(it);
  auto it1 = STL_map_1.begin();
  auto it2 = STL_map_2.begin();

  while (it1 != STL_map_1.end()) {
    EXPECT_EQ(it1.operator*().first, it2.operator*().first);
    ++it1, ++it2;
  }
  EXPECT_EQ(STL_map_1.size(), STL_map_2.size());
}

TEST(Map, Modifier_Erase_2) {
  STL::map<int, std::string> STL_map_1{
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  STL::map<int, std::string> STL_map_2{
      {1, "aboba"}, {2, "shleppa"}, {4, "abobus"}};
  auto it = STL_map_1.begin();
  it++;
  it++;
  STL_map_1.erase(it);
  auto it1 = STL_map_1.begin();
  auto it2 = STL_map_2.begin();

  while (it1 != STL_map_1.end()) {
    EXPECT_EQ(it1.operator*().first, it2.operator*().first);
    ++it1, ++it2;
  }
  EXPECT_EQ(STL_map_1.size(), STL_map_2.size());
}

TEST(Map, Modifier_Erase_3) {
  STL::map<int, std::string> STL_map_1{
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  STL::map<int, std::string> STL_map_2{{1, "aboba"}};

  auto it0 = STL_map_1.begin();
  ++it0;
  STL_map_1.erase(it0);

  auto it = STL_map_1.begin();
  ++it;
  STL_map_1.erase(it);

  auto it2 = STL_map_1.begin();
  ++it2;
  STL_map_1.erase(it2);

  auto it3 = STL_map_1.begin();
  auto it4 = STL_map_2.begin();

  while (it3 != STL_map_1.end()) {
    EXPECT_EQ(it3.operator*().first, it4.operator*().first);
    ++it3, ++it4;
  }

  EXPECT_EQ(STL_map_1.size(), STL_map_2.size());
}

TEST(Map, Modifier_Swap) {
  STL::map<int, std::string> STL_map_1{
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  STL::map<int, std::string> STL_map_2{
      {10, "shtirlits"}, {12, "vovochka"}, {13, "poruchik"}, {14, "chepaev"}};
  STL::map<int, std::string> STL_map_3{
      {1, "aboba"}, {2, "shleppa"}, {3, "amogus"}, {4, "abobus"}};
  STL::map<int, std::string> STL_map_4{
      {10, "shtirlits"}, {12, "vovochka"}, {13, "poruchik"}, {14, "chepaev"}};

  STL_map_1.swap(STL_map_2);
  auto it1 = STL_map_1.begin();
  auto it2 = STL_map_2.begin();
  auto it3 = STL_map_3.begin();
  auto it4 = STL_map_4.begin();
  while (it1 != STL_map_1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }
  while (it2 != STL_map_2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }
  EXPECT_EQ(STL_map_1.size(), STL_map_4.size());
  EXPECT_EQ(STL_map_2.size(), STL_map_3.size());
}

TEST(Map, Modifier_Mem_Merge) {
  STL::map<int, std::string> STL_map_1{
      {1, "diksi"}, {2, "podval so zmeyami"}, {3, "klouny"}};
  STL::map<int, std::string> STL_map_2{
      {3, "klouny"}, {4, "sbebr platforma"}, {5, "avito"}};
  STL::map<int, std::string> STL_map_3{{1, "diksi"},
                                       {2, "podval so zmeyami"},
                                       {3, "klouny"},
                                       {4, "sbebr platforma"},
                                       {5, "avito"}};
  STL_map_1.merge(STL_map_2);
  auto it1 = STL_map_1.begin();
  auto it3 = STL_map_3.begin();
  while (it1 != STL_map_1.end()) {
    EXPECT_EQ(*it1, *it3);
    ++it1, ++it3;
  }
  EXPECT_EQ(STL_map_1.size(), STL_map_3.size());
}

TEST(Map, Lookup_Contains) {
  STL::map<int, std::string> STL_map;
  STL_map.insert(1, "salamandry");
  STL_map.insert(2, "medoedy");
  STL_map.insert(3, "kapibary");
  STL_map.insert(4, "alpaki");
  EXPECT_EQ(STL_map.contains(1), true);
  EXPECT_EQ(STL_map.contains(2), true);
  EXPECT_EQ(STL_map.contains(3), true);
  EXPECT_EQ(STL_map.contains(4), true);
  EXPECT_EQ(STL_map.contains(7), false);
  EXPECT_EQ(STL_map.contains(-2), false);
  EXPECT_EQ(STL_map.contains(0), false);
}
TEST(Map, Exception_1) {
  STL::map<int, std::string> STL_map;
  STL_map.insert(2, "medoedy");
  STL::map<int, std::string>::iterator t = STL_map.begin();
  ++t;
  ASSERT_ANY_THROW(*t);
}

TEST(Map, Exception_2) {
  STL::map<int, std::string> STL_map;
  STL_map.insert(2, "medoedy");
  STL::map<int, std::string>::iterator t = STL_map.begin();
  ++t;
  ASSERT_ANY_THROW(++t);
}

TEST(Constructors, Default_set) {
  STL::set<int> STL;
  std::set<int> stl;
  ASSERT_TRUE(STL.empty() == stl.empty());
}

TEST(Constructors, Parametres_set) {
  STL::set<int> STL{1, 5, 6, 8, -15, 21};
  std::set<int> stl{1, 5, 6, 8, -15, 21};
  STL::set<int>::iterator STLIt = STL.begin();
  std::set<int>::iterator stlIt = stl.begin();
  bool equal = true;
  for (; (STLIt != STL.end()) && (stlIt != stl.end()); ++STLIt, ++stlIt) {
    if (*STLIt != *stlIt) {
      equal = false;
      break;
    }
  }
  ASSERT_TRUE(equal);
}

TEST(Constructors, Copy_set) {
  STL::set<int> st1{76, -68, 15, 0, 8, -15, 21};
  STL::set<int> st2(st1);
  STL::set<int>::iterator it1 = st1.begin();
  STL::set<int>::iterator it2 = st2.begin();
  bool equal = true;
  for (; (it1 != st1.end()) && (it2 != st2.end()); ++it1, ++it2) {
    if (*it1 != *it2) {
      equal = false;
      break;
    }
  }
  ASSERT_TRUE(equal);
}

TEST(Constructors, Move_set) {
  STL::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  STL::set<int> st2((STL::set<int>&&)st1);
  ASSERT_TRUE(st1.empty() && !st2.empty());
}

TEST(Overloads, Dereferencing_set) {
  STL::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  STL::set<int>::iterator it1 = st1.find(135);
  ASSERT_TRUE(*it1 == 135);
}

TEST(Overloads, PreIncrement_set) {
  STL::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  STL::set<int>::iterator it1 = st1.begin();
  STL::set<int>::iterator it2 = ++it1;
  ASSERT_TRUE(*it1 == -4 && *it2 == -4);
}

TEST(Overloads, PreDecrement_set) {
  STL::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  STL::set<int>::iterator it1 = st1.find(135);
  STL::set<int>::iterator it2 = --it1;
  ASSERT_TRUE(*it1 == 67 && *it2 == 67);
}

TEST(Overloads, Equal_set) {
  STL::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  STL::set<int>::iterator it1 = st1.find(135);
  STL::set<int>::iterator it2 = --it1;
  ASSERT_TRUE(it1 == it2);
}

TEST(Overloads, MoveAssign_set) {
  STL::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  STL::set<int> st2;
  st2 = (STL::set<int>&&)st1;
  ASSERT_TRUE(st1.empty() && !st2.empty());
}

TEST(Iterators, Begin_set) {
  STL::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  STL::set<int>::iterator it1 = st1.begin();
  ASSERT_TRUE(*it1 == -15);
}

TEST(Iterators, End_set) {
  STL::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  STL::set<int>::iterator it1 = st1.find(135);
  ++it1;
  ASSERT_TRUE(it1 == st1.end());
}

TEST(Capacity, Empty_set) {
  STL::set<int> st1;
  ASSERT_TRUE(st1.empty());
}

TEST(Capacity, Size_set) {
  STL::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  ASSERT_TRUE(st1.size() == 7);
}

TEST(LookUp, Find_set) {
  STL::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  STL::set<int>::iterator it1 = st1.find(67);
  ASSERT_TRUE(*it1 == 67);
}

TEST(LookUp, Contains_set) {
  STL::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  ASSERT_TRUE(st1.contains(67));
}

TEST(Modifieres, Clear_set) {
  STL::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  st1.clear();
  ASSERT_TRUE(st1.empty());
}

TEST(Modifieres, Insert_set) {
  STL::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  st1.insert(-200);
  ASSERT_TRUE(*st1.begin() == -200);
}

TEST(Modifieres, Erase_set) {
  STL::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  STL::set<int>::iterator it1 = st1.find(8);
  st1.erase(it1);
  // ASSERT_ANY_THROW(*st1.find(8) == 0);
}

TEST(Modifieres, Swap_set) {
  STL::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  STL::set<int> st2{1, 3, 6, 7, -12, 21};
  st1.swap(st2);
  ASSERT_TRUE(*st1.find(21) && *st2.find(135));
}

TEST(Modifieres, Merge_set) {
  STL::set<int> st1{-4, 8, 135, 67, 5, -15, 1};
  STL::set<int> st2{1, 3, 6, 7, -12, 21};
  st1.merge(st2);
  ASSERT_TRUE(*st1.find(21) && *st1.find(135));
}

TEST(Const, Iterator_set) {
  const STL::set<int> st{-1, 23, 5, -19};
  STL::set<int>::iterator it = st.find(5);
  ASSERT_TRUE(*it == 5);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
