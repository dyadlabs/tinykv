#include "tinykv/error.h"
#include "tinykv/kv_store.h"

#include <gtest/gtest.h>

#include <string>

namespace {

template <typename Fn> std::string messageOf(Fn op) {
  try {
    op();
  } catch (const tinykv::TinyKVError &e) {
    return e.what();
  }
  return "<no exception thrown>";
}

} // namespace

TEST(EmptyKeyTest, EveryOperationRejectsAnEmptyKey) {
  tinykv::KVStore kv;

  EXPECT_THROW(kv.put("", ""), tinykv::InvalidKey);
  EXPECT_THROW(kv.put("", "World!"), tinykv::InvalidKey);
  EXPECT_THROW(kv.get(""), tinykv::InvalidKey);
  EXPECT_THROW(kv.remove(""), tinykv::InvalidKey);
  EXPECT_THROW(kv.exists(""), tinykv::InvalidKey);
}

TEST(EmptyKeyTest, EveryOperationReportsTheSameMessage) {
  tinykv::KVStore kv;

  const std::string expected = messageOf([&] { kv.put("", "v"); });
  ASSERT_NE(expected, "<no exception thrown>");

  EXPECT_EQ(messageOf([&] { kv.put("", "v"); }), expected);
  EXPECT_EQ(messageOf([&] { kv.get(""); }), expected);
  EXPECT_EQ(messageOf([&] { kv.remove(""); }), expected);
  EXPECT_EQ(messageOf([&] { kv.exists(""); }), expected);
}

TEST(EmptyKeyTest, RejectedPutLeavesTheStoreUnchanged) {
  tinykv::KVStore kv;
  kv.put("a", "apple");

  tinykv::KVStore before;
  before.put("a", "apple");

  EXPECT_THROW(kv.put("", "rejected"), tinykv::InvalidKey);

  EXPECT_EQ(kv, before);
}

TEST(PutTest, CommonInput) {
  tinykv::KVStore kv;

  EXPECT_NO_THROW(kv.put("Hello", "World!"));

  const auto value = kv.get("Hello");
  ASSERT_TRUE(value.has_value());
  EXPECT_EQ(*value, "World!");
}

TEST(PutTest, DoublePut) {
  tinykv::KVStore kv;

  EXPECT_NO_THROW(kv.put("a", "apple"));
  ASSERT_TRUE(kv.get("a").has_value());
  EXPECT_EQ(*kv.get("a"), "apple");

  EXPECT_NO_THROW(kv.put("a", "abandon"));
  ASSERT_TRUE(kv.get("a").has_value());
  EXPECT_EQ(*kv.get("a"), "abandon");
}

TEST(PutTest, EmptyValueIsAllowed) {
  tinykv::KVStore kv;

  EXPECT_NO_THROW(kv.put("a", ""));

  const auto value = kv.get("a");
  ASSERT_TRUE(value.has_value());
  EXPECT_TRUE(value->empty());
}

TEST(GetTest, GetNonexist) {
  tinykv::KVStore kv;

  EXPECT_EQ(kv.get("Hello"), std::nullopt);
}

TEST(GetTest, GetExist) {
  tinykv::KVStore kv;
  kv.put("Hello", "World!");

  const auto value = kv.get("Hello");
  ASSERT_TRUE(value.has_value());
  EXPECT_EQ(*value, "World!");
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

  EXPECT_NO_THROW(kv.put("a", "apple"));
  ASSERT_TRUE(kv.get("a").has_value());
  EXPECT_EQ(*kv.get("a"), "apple");

  EXPECT_TRUE(kv.remove("a"));

  EXPECT_NO_THROW(kv.put("a", "abandon"));
  ASSERT_TRUE(kv.get("a").has_value());
  EXPECT_EQ(*kv.get("a"), "abandon");
}
