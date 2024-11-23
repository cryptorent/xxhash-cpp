#ifndef XXHASH64_H
#define XXHASH64_H

#include <cstdint>
#include <cstring>
#include <iostream>

class XXHash64 {
private:
    static const uint64_t PRIME64_1 = 0x9E3779B185EBCA87ULL;
    static const uint64_t PRIME64_2 = 0xC2B2AE3D27D4EB4FULL;
    static const uint64_t PRIME64_3 = 0x165667B19E3779F9ULL;
    static const uint64_t PRIME64_4 = 0x85EBCA77C2B2AE63ULL;
    static const uint64_t PRIME64_5 = 0x27D4EB2F165667C5ULL;

    static uint64_t rotateLeft(uint64_t x, int32_t n);
    static uint64_t round(uint64_t acc, uint64_t input);
    static uint64_t mergeRound(uint64_t hash, uint64_t v);
public:
    static uint64_t hash(const char* input, size_t len, uint64_t seed);
    static uint64_t hash(const char* input, size_t len, size_t offset, uint64_t seed);
};

#endif //XXHASH64_H
