#include "tinykv/kv_store.h"
#include <gtest/gtest.h>

TEST(PutTest, EmptyInput) {
  tinykv::KVStore kv;
  EXPECT_FALSE(kv.put("", ""));
  EXPECT_FALSE(kv.put("", "World!"));
}

TEST(PutTest, CommonInput) {
  tinykv::KVStore kv;
  EXPECT_TRUE(kv.put("Hello", "World!"));
}

TEST(PutTest, DoublePut) {
  tinykv::KVStore kv;
  EXPECT_TRUE(kv.put("a", "apple"));
  EXPECT_EQ(kv.get("a").value(), "apple");
  EXPECT_TRUE(kv.put("a", "abandon"));
  EXPECT_EQ(kv.get("a").value(), "abandon");
}

TEST(PutTest, PutEmpty) {
  tinykv::KVStore kv;
  EXPECT_TRUE(kv.put("a", ""));
  EXPECT_EQ(kv.get("a").value(), "");
}

TEST(GetTest, GetNonexist) {
  tinykv::KVStore kv;
  EXPECT_EQ(kv.get("Hello"), std::nullopt);
}

TEST(GetTest, GetExist) {
  tinykv::KVStore kv;
  kv.put("Hello", "World!");
  EXPECT_EQ(kv.get("Hello").value(), "World!");
}

TEST(RemoveTest, RemoveNonexist) {
  tinykv::KVStore kv;
  EXPECT_FALSE(kv.remove("Hello"));
}

TEST(RemoveTest, RemoveExist) {
  tinykv::KVStore kv;
  kv.put("Hello", "World!");
  EXPECT_TRUE(kv.remove("Hello"));
  EXPECT_EQ(kv.get("Hello"), std::nullopt);
}

TEST(ExistsTest, Nonexist) {
  tinykv::KVStore kv;
  EXPECT_FALSE(kv.exists("Hello"));
}

TEST(ExistsTest, Exist) {
  tinykv::KVStore kv;
  kv.put("Hello", "World!");
  EXPECT_TRUE(kv.exists("Hello"));
}

TEST(IntegrationTest, RemoveAndPut) {
  tinykv::KVStore kv;
  EXPECT_TRUE(kv.put("a", "apple"));
  EXPECT_EQ(kv.get("a").value(), "apple");
  EXPECT_TRUE(kv.remove("a"));
  EXPECT_TRUE(kv.put("a", "abandon"));
  EXPECT_EQ(kv.get("a").value(), "abandon");
}
