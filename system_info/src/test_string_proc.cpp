#include <gtest/gtest.h>

#include "string_proc.h"

TEST(StringProc, RTrim) {
  ASSERT_EQ("", RTrim(""));
  ASSERT_EQ("abc", RTrim("abc"));
  ASSERT_EQ("   asdc", RTrim("   asdc"));
  ASSERT_EQ("", RTrim("     "));
  ASSERT_EQ("a b c d", RTrim("a b c d     "));
  ASSERT_EQ("x", RTrim("x\n"));
  ASSERT_EQ("x", RTrim("x\t\n\r"));
}

TEST(StringProc, LTrim) {
  ASSERT_EQ("", LTrim(""));
  ASSERT_EQ("abc", LTrim("abc"));
  ASSERT_EQ("asdc   ", LTrim("asdc   "));
  ASSERT_EQ("", LTrim("     "));
  ASSERT_EQ("a b c d", LTrim("     a b c d"));
  ASSERT_EQ("x", LTrim("\nx"));
  ASSERT_EQ("x", LTrim("\t\n\rx"));
}

TEST(StringProc, Split) {
  using Pair = std::pair<std::string, std::string>;
  char delim = ':';

  ASSERT_EQ(Pair("", ""), Split("", delim));
  ASSERT_EQ(Pair("123", "asv"), Split("123:asv", delim));
  ASSERT_EQ(Pair("", "asd"), Split(":asd", delim));
  ASSERT_EQ(Pair("sad", ""), Split("sad:", delim));
  ASSERT_EQ(Pair("", ""), Split(":", delim));
}
