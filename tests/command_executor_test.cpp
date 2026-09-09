#include "tinykv/command.h"
#include "tinykv/command_executor.h"
#include "tinykv/kv_store.h"
#include <gtest/gtest.h>
#include <stdexcept>

TEST(ExecuteTest, UnknownCommand) {
  tinykv::KVStore kv;
  tinykv::CommandExecutor executor;
  tinykv::Command cmd{"foo", {}};
  try {
    executor.execute(kv, cmd);
    FAIL() << "expected std::runtime_error";
  } catch (const std::runtime_error &e) {
    EXPECT_STREQ(e.what(), "Unknown command");
  }
}

TEST(ExecuteTest, IncorrectArguments) {
  tinykv::KVStore kv;
  tinykv::CommandExecutor executor;
  tinykv::Command cmd{"put", {"a"}};
  try {
    executor.execute(kv, cmd);
    FAIL() << "expected std::runtime_error";
  } catch (const std::runtime_error &e) {
    EXPECT_STREQ(e.what(), "Incorrect argument number");
  }
}

TEST(ExecuteTest, IncorrectGet) {
  tinykv::KVStore kv;
  tinykv::CommandExecutor executor;
  tinykv::Command cmd{"get", {"a"}};
  try {
    executor.execute(kv, cmd);
    FAIL() << "expected std::runtime_error";
  } catch (const std::runtime_error &e) {
    EXPECT_STREQ(e.what(), "The key does not exist");
  }
}

TEST(ExecuteTest, CorrectGet) {
  tinykv::KVStore kv;
  kv.put("a", "apple");
  tinykv::KVStore expected = kv;
  tinykv::CommandExecutor executor;
  tinykv::Command cmd{"get", {"a"}};
  EXPECT_NO_THROW(executor.execute(kv, cmd));
  EXPECT_EQ(kv, expected);
}

TEST(ExecuteTest, SimpleContain) {
  tinykv::KVStore kv;
  kv.put("a", "apple");
  tinykv::CommandExecutor executor;
  tinykv::Command cmd{"contain", {"a"}};
  EXPECT_NO_THROW(executor.execute(kv, cmd));
}
