#include "tinykv/renderer.h"
#include "tinykv/result.h"

#include <gtest/gtest.h>
#include <optional>
#include <sstream>
#include <string>

TEST(RenderTest, PutNewKey) {
  tinykv::PutResult r{"a", "apple", std::nullopt};
  std::ostringstream os;

  tinykv::Renderer::render(r, os);

  EXPECT_EQ(os.str(), "Put the pair {\"a\": \"apple\"}.\n");
}

TEST(RenderTest, UpdateKey) {
  tinykv::PutResult r{"a", "pear", "apple"};
  std::ostringstream os;
  std::string expected =
      "The value of \"a\" is updated from \"apple\" to \"pear\".\n";

  tinykv::Renderer::render(r, os);

  EXPECT_EQ(os.str(), expected);
}

TEST(RenderTest, GetExistingKey) {
  tinykv::GetResult r{"a", "apple"};
  std::ostringstream os;
  std::string expected = "Got the pair {\"a\": \"apple\"}.\n";

  tinykv::Renderer::render(r, os);

  EXPECT_EQ(os.str(), expected);
}

TEST(RenderTest, GetNonexistingKey) {
  tinykv::GetResult r{"a", std::nullopt};
  std::ostringstream os;
  std::string expected = "The key does not exist.\n";

  tinykv::Renderer::render(r, os);

  EXPECT_EQ(os.str(), expected);
}

TEST(RenderTest, RemoveExistingKey) {
  tinykv::RemoveResult r{true, "a"};
  std::ostringstream os;
  std::string expected = "Removed the pair mapped by \"a\".\n";

  tinykv::Renderer::render(r, os);

  EXPECT_EQ(os.str(), expected);
}

TEST(RenderTest, RemoveNonexistingKey) {
  tinykv::RemoveResult r{false, "a"};
  std::ostringstream os;
  std::string expected = "The key does not exist.\n";

  tinykv::Renderer::render(r, os);

  EXPECT_EQ(os.str(), expected);
}

TEST(RenderTest, ExistsExistingKey) {
  tinykv::ExistsResult r{true, "a"};
  std::ostringstream os;
  std::string expected = "Found the key \"a\".\n";

  tinykv::Renderer::render(r, os);

  EXPECT_EQ(os.str(), expected);
}

TEST(RenderTest, ExistsNonexistingKey) {
  tinykv::ExistsResult r{false, "a"};
  std::ostringstream os;
  std::string expected = "The key does not exist.\n";

  tinykv::Renderer::render(r, os);

  EXPECT_EQ(os.str(), expected);
}
