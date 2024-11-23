#ifndef BENCHCONTAINER_H
#define BENCHCONTAINER_H

#include <cstdint>
#include <vector>

#include "xxhash/XXHash32.h"
#include "xxhash/XXHash64.h"

class BenchContainer {
public:
    enum class HashId { XXH32, XXH64 };

    static uint64_t hash(HashId hashID, const char* input, int length, int offset) {
        switch (hashID) {
            case HashId::XXH32:
                return XXHash32::hash(input, length, offset, 0);
            case HashId::XXH64:
                return XXHash64::hash(input, length, offset, 0);
            default: throw std::invalid_argument("Unsupported hash ID");
        }
    }

    static std::string hashIdToString(HashId hashID) {
        switch (hashID) {
            case HashId::XXH32: return "XXH32";
            case HashId::XXH64: return "XXH64";
            default: throw std::invalid_argument("Unsupported hash ID");
        }
    }
};

#endif //BENCHCONTAINER_H
