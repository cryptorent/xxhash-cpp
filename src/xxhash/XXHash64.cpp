#include "XXHash64.h"

uint64_t XXHash64::rotateLeft(uint64_t x, int32_t n) {
    return (x << n) | (x >> (64 - n));
}

uint64_t XXHash64::round(uint64_t acc, uint64_t input) {
    acc += input * PRIME64_2;
    acc = rotateLeft(acc, 31);
    acc *= PRIME64_1;
    return acc;
}

uint64_t XXHash64::mergeRound(uint64_t hash, uint64_t v) {
    hash ^= round(0, v);
    hash = hash * PRIME64_1 + PRIME64_4;
    return hash;
}

uint64_t XXHash64::hash(const char *input, size_t len, uint64_t seed) {
    return hash(input, len, 0, seed);
}

uint64_t XXHash64::hash(const char *input, size_t len, size_t offset, uint64_t seed) {
    uint64_t hash;
    size_t bufLimit = offset + len;

    if (bufLimit >= 32) {
        size_t limit = bufLimit - 32;
        uint64_t v1 = seed + PRIME64_1 + PRIME64_2;
        uint64_t v2 = seed + PRIME64_2;
        uint64_t v3 = seed + 0;
        uint64_t v4 = seed - PRIME64_1;

        while (offset <= limit) {
            v1 = round(v1, *reinterpret_cast<const uint64_t *>(input) + offset);
            v2 = round(v2, *reinterpret_cast<const uint64_t *>(input + offset + 8));
            v3 = round(v3, *reinterpret_cast<const uint64_t *>(input + offset + 16));
            v4 = round(v4, *reinterpret_cast<const uint64_t *>(input + offset + 24));;
            offset += 32;
        }

        hash = rotateLeft(v1, 1) +
               rotateLeft(v2, 7) +
               rotateLeft(v3, 12) +
               rotateLeft(v4, 18);

        hash = mergeRound(hash, v1);
        hash = mergeRound(hash, v2);
        hash = mergeRound(hash, v3);
        hash = mergeRound(hash, v4);
    } else {
        hash = seed + PRIME64_5;
    }

    hash += len;

    while (offset + 8 <= bufLimit) {
        uint64_t k1 = *reinterpret_cast<const uint64_t *>(input + offset);
        k1 *= PRIME64_2;
        k1 = rotateLeft(k1, 31);
        k1 *= PRIME64_1;
        hash ^= k1;
        hash = rotateLeft(hash, 27) * PRIME64_1 + PRIME64_4;
        offset += 8;
    }

    while (offset + 4 <= bufLimit) {
        hash ^= (*reinterpret_cast<const uint32_t *>(input + offset) & 0xFFFFFFFFULL) * PRIME64_1;
        hash = rotateLeft(hash, 23) * PRIME64_2 + PRIME64_3;
        offset += 4;
    }

    while (offset < bufLimit) {
        hash ^= (input[offset] & 0xFFULL) * PRIME64_5;
        hash = rotateLeft(hash, 11) * PRIME64_1;
        offset++;
    }

    hash ^= hash >> 33;
    hash *= PRIME64_2;
    hash ^= hash >> 29;
    hash *= PRIME64_3;
    hash ^= hash >> 32;

    return hash;
}
