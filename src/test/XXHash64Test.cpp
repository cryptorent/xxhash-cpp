#include "gtest/gtest.h"
#include "../xxhash/XXHash64.h"

TEST(Hash64, test) {
    std::string text = "test";
    uint64_t hashValue = XXHash64::hash(text.c_str(), text.size(), 0);
    ASSERT_EQ(0x4FDCCA5DDB678139L, hashValue);
}

TEST(Hash64, testLen20) {
    std::string text = "01234567890123456789";
    uint64_t hashValue = XXHash64::hash(text.c_str(), text.size(), 0);
    ASSERT_EQ(0x2D071F530B4E5DCCL, hashValue);
}