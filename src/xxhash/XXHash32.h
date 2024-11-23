#ifndef XXHASH32_H
#define XXHASH32_H

#include <cstdint>
#include <cstring>
#include <algorithm>

class XXHash32 {
private:
    // Prime numbers used in the algorithm
    static const uint32_t PRIME32_1 = 0x9E3779B1;
    static const uint32_t PRIME32_2 = 0x85EBCA77;
    static const uint32_t PRIME32_3 = 0xC2B2AE3D;
    static const uint32_t PRIME32_4 = 0x27D4EB2F;
    static const uint32_t PRIME32_5 = 0x165667B1;
    // Helper method to perform a single round of mixing
    static uint32_t round(uint32_t acc, uint32_t input);
public:
    // Computes the 32-bit XXHash of the given input byte array with the specified seed
    static uint32_t hash(const char* input, size_t len, uint32_t seed);
    static uint32_t hash(const char* input, size_t len, size_t offset, uint32_t seed);
};

#endif //XXHASH32_H
