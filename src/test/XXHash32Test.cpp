#include "gtest/gtest.h"
#include "../xxhash/XXHash32.h"

TEST(Hash32, test) {
    std::string text = "test";
    uint32_t hashValue = XXHash32::hash(text.c_str(), text.size(), 0);
    ASSERT_EQ(0x3E2023CF, hashValue);
}

TEST(Hash32, testLen20) {
    std::string text = "01234567890123456789";
    uint32_t hashValue = XXHash32::hash(text.c_str(), text.size(), 0);
    ASSERT_EQ(0x7183E10C, hashValue);
}