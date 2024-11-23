#include "XXHash32.h"

uint32_t XXHash32::round(uint32_t acc, uint32_t input) {
    acc += input * PRIME32_2;
    acc = (acc << 13) | (acc >> (32 - 13)); // Rotate left by 13
    acc *= PRIME32_1;
    return acc;
}

uint32_t XXHash32::hash(const char *input, size_t len, uint32_t seed) {
    return hash(input, len, 0, seed);
}

uint32_t XXHash32::hash(const char *input, size_t len, size_t offset, uint32_t seed) {
    uint32_t hash;
    size_t bufLimit = offset + len;

    // If the input is longer or equal to 16 bytes, process in 16-byte chunks
    if (bufLimit >= 16) {
        size_t limit = bufLimit - 16;
        // Initialize four running hash values
        uint32_t v1 = seed + PRIME32_1 + PRIME32_2;
        uint32_t v2 = seed + PRIME32_2;
        uint32_t v3 = seed;
        uint32_t v4 = seed - PRIME32_1;

        // Process 16 bytes at a time
        while (offset <= limit) {
            v1 = round(v1, *reinterpret_cast<const uint32_t *>(input) + offset);
            v2 = round(v2, *reinterpret_cast<const uint32_t *>(input + offset + 4));
            v3 = round(v3, *reinterpret_cast<const uint32_t *>(input + offset + 8));
            v4 = round(v4, *reinterpret_cast<const uint32_t *>(input + offset + 12));;
            offset += 16;
        }
        // Combine the four running hash values
        hash = ((v1 << 1) | (v1 >> (32 - 1))) +
               ((v2 << 7) | (v2 >> (32 - 7))) +
               ((v3 << 12) | (v3 >> (32 - 12))) +
               ((v4 << 18) | (v4 >> (32 - 18)));
    } else {
        // If input is smaller than 16 bytes, start with seed + PRIME32_5
        hash = seed + PRIME32_5;
    }

    // Add the length of the input to the hash
    hash += static_cast<uint32_t>(len);

    // Process remaining 4-byte chunks
    while (offset + 4 <= bufLimit) {
        hash += *reinterpret_cast<const uint32_t *>(input + offset) * PRIME32_3;
        hash = (hash << 17) | (hash >> (32 - 17)); // Rotate left by 17
        hash *= PRIME32_4;
        offset += 4;
    }

    // Process remaining bytes (less than 4)
    while (offset < bufLimit) {
        hash += (input[offset] & 0xFF) * PRIME32_5;
        hash = (hash << 11) | (hash >> (32 - 11)); // Rotate left by 11
        hash *= PRIME32_1;
        offset++;
    }

    // Final mixing of the hash
    hash ^= hash >> 15;
    hash *= PRIME32_2;
    hash ^= hash >> 13;
    hash *= PRIME32_3;
    hash ^= hash >> 16;

    return hash;
}
