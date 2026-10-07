#include "tinykv/command.h"
#include "tinykv/command_executor.h"
#include "tinykv/error.h"
#include "tinykv/kv_store.h"
#include "tinykv/result.h"

#include <gtest/gtest.h>

TEST(ExecuteTest, UnknownCommandThrowsUnknownCommand) {
  tinykv::KVStore kv;
  tinykv::CommandExecutor executor;
  tinykv::Command command{"foo", {}};

  EXPECT_THROW(executor.execute(kv, command), tinykv::UnknownCommand);
}

TEST(ExecuteTest, IncorrectArgumentsThrowsInvalidArguments) {
  tinykv::KVStore kv;
  tinykv::CommandExecutor executor;
  tinykv::Command command{"put", {"a"}};

  EXPECT_THROW(executor.execute(kv, command), tinykv::InvalidArguments);
}

TEST(ExecuteTest, EmptyKeyThrowsInvalidKey) {
  tinykv::KVStore kv;
  tinykv::CommandExecutor executor;
  tinykv::Command command{"put", {"", "value"}};

  EXPECT_THROW(executor.execute(kv, command), tinykv::InvalidKey);
}

TEST(ExecuteTest, EmptyKeyArgumentIsRejectedForReadsToo) {
  tinykv::KVStore kv;
  tinykv::CommandExecutor executor;
  // Exactly what CommandParser::parse("get \"\"") produces.
  tinykv::Command command{"get", {""}};

  EXPECT_THROW(executor.execute(kv, command), tinykv::InvalidKey);
}

TEST(ExecuteTest, PutReturnsInsertResult) {
  tinykv::KVStore kv;
  tinykv::CommandExecutor executor;
  tinykv::Command command{"put", {"a", "apple"}};

  tinykv::ExecutionResult result = executor.execute(kv, command);

  ASSERT_TRUE(std::holds_alternative<tinykv::PutResult>(result));
  const auto &put = std::get<tinykv::PutResult>(result);
  EXPECT_EQ(put.key, "a");
  EXPECT_EQ(put.value, "apple");
  EXPECT_FALSE(put.original_value.has_value());
  ASSERT_TRUE(kv.get("a").has_value());
  EXPECT_EQ(*kv.get("a"), "apple");
}

TEST(ExecuteTest, PutReturnsUpdateResult) {
  tinykv::KVStore kv;
  kv.put("a", "apple");
  tinykv::CommandExecutor executor;
  tinykv::Command command{"put", {"a", "pear"}};

  tinykv::ExecutionResult result = executor.execute(kv, command);

  ASSERT_TRUE(std::holds_alternative<tinykv::PutResult>(result));
  const auto &put = std::get<tinykv::PutResult>(result);
  EXPECT_EQ(put.key, "a");
  EXPECT_EQ(put.value, "pear");
  ASSERT_TRUE(put.original_value.has_value());
  EXPECT_EQ(*put.original_value, "apple");
  ASSERT_TRUE(kv.get("a").has_value());
  EXPECT_EQ(*kv.get("a"), "pear");
}

TEST(ExecuteTest, GetReturnsValue) {
  tinykv::KVStore kv;
  kv.put("a", "apple");
  tinykv::CommandExecutor executor;
  tinykv::Command command{"get", {"a"}};

  tinykv::ExecutionResult result = executor.execute(kv, command);

  ASSERT_TRUE(std::holds_alternative<tinykv::GetResult>(result));
  const auto &get = std::get<tinykv::GetResult>(result);
  EXPECT_EQ(get.key, "a");
  ASSERT_TRUE(get.value.has_value());
  EXPECT_EQ(*get.value, "apple");
}

TEST(ExecuteTest, GetMissingKeyReturnsEmptyValue) {
  tinykv::KVStore kv;
  tinykv::CommandExecutor executor;
  tinykv::Command command{"get", {"a"}};

  tinykv::ExecutionResult result = executor.execute(kv, command);

  ASSERT_TRUE(std::holds_alternative<tinykv::GetResult>(result));
  const auto &get = std::get<tinykv::GetResult>(result);
  EXPECT_EQ(get.key, "a");
  EXPECT_FALSE(get.value.has_value());
}

TEST(ExecuteTest, RemoveExistingKeyReturnsSuccess) {
  tinykv::KVStore kv;
  kv.put("a", "apple");
  tinykv::CommandExecutor executor;
  tinykv::Command command{"remove", {"a"}};

  tinykv::ExecutionResult result = executor.execute(kv, command);

  ASSERT_TRUE(std::holds_alternative<tinykv::RemoveResult>(result));
  const auto &remove = std::get<tinykv::RemoveResult>(result);
  EXPECT_TRUE(remove.success);
  EXPECT_EQ(remove.key, "a");
  EXPECT_FALSE(kv.exists("a"));
}

TEST(ExecuteTest, RemoveMissingKeyReturnsFailure) {
  tinykv::KVStore kv;
  tinykv::CommandExecutor executor;
  tinykv::Command command{"remove", {"a"}};

  tinykv::ExecutionResult result = executor.execute(kv, command);

  ASSERT_TRUE(std::holds_alternative<tinykv::RemoveResult>(result));
  const auto &remove = std::get<tinykv::RemoveResult>(result);
  EXPECT_FALSE(remove.success);
  EXPECT_EQ(remove.key, "a");
}

TEST(ExecuteTest, ExistsReturnsTrueForExistingKey) {
  tinykv::KVStore kv;
  kv.put("a", "apple");
  tinykv::CommandExecutor executor;
  tinykv::Command command{"exists", {"a"}};

  tinykv::ExecutionResult result = executor.execute(kv, command);

  ASSERT_TRUE(std::holds_alternative<tinykv::ExistsResult>(result));
  const auto &exists = std::get<tinykv::ExistsResult>(result);
  EXPECT_TRUE(exists.exists);
  EXPECT_EQ(exists.key, "a");
}

TEST(ExecuteTest, ExistsReturnsFalseForMissingKey) {
  tinykv::KVStore kv;
  tinykv::CommandExecutor executor;
  tinykv::Command command{"exists", {"a"}};

  tinykv::ExecutionResult result = executor.execute(kv, command);

  ASSERT_TRUE(std::holds_alternative<tinykv::ExistsResult>(result));
  const auto &exists = std::get<tinykv::ExistsResult>(result);
  EXPECT_FALSE(exists.exists);
  EXPECT_EQ(exists.key, "a");
}
