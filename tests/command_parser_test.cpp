#include "tinykv/command.h"
#include "tinykv/command_parser.h"
#include "tinykv/error.h"

#include <gtest/gtest.h>

TEST(ParseTest, EmptyInput1) {
  tinykv::Command result = tinykv::CommandParser::parse("");
  EXPECT_TRUE(result.empty());
}

TEST(ParseTest, EmptyInput2) {
  tinykv::Command result = tinykv::CommandParser::parse("    ");
  EXPECT_TRUE(result.empty());
}

TEST(ParseTest, QuitCommand) {
  tinykv::Command expected{"quit", {}};
  tinykv::Command result = tinykv::CommandParser::parse("quit");
  EXPECT_EQ(result, expected);
}

TEST(ParseTest, OneArgument) {
  tinykv::Command expected = {"get", {"a"}};
  tinykv::Command result = tinykv::CommandParser::parse("get a");
  EXPECT_EQ(result, expected);
}

TEST(ParseTest, MultiArguments) {
  tinykv::Command expected = {"put", {"a", "apple"}};
  tinykv::Command result = tinykv::CommandParser::parse("put a apple");
  EXPECT_EQ(result, expected);
}

TEST(ParseTest, ExtraSpace) {
  tinykv::Command expected = {"put", {"a"}};
  tinykv::Command result =
      tinykv::CommandParser::parse("   put       a          ");
  EXPECT_EQ(result, expected);
}

TEST(ParseTest, ArgumentInQuote) {
  tinykv::Command expected = {"put", {"a", "hello world"}};
  tinykv::Command result =
      tinykv::CommandParser::parse("put a \"hello world\"");
  EXPECT_EQ(result, expected);
}

TEST(ParseTest, IncompleteQuotes) {
  EXPECT_THROW(tinykv::CommandParser::parse("put a \"hello"),
               tinykv::ParseError);
}
