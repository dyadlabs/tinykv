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
