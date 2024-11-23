#include "Benchmark.h"

void Benchmark::run() {
    // Define the size of the byte array (e.g., 10 MB)
    const int size = 10 * 1024 * 1024; // 10 megabytes

    // Initialize the byte array with repeating values from 0 to 255
    std::vector<char> data(size);
    for (int i = 0; i < size; i++) {
        data[i] = static_cast<char>(i % 256);
    }

    for (auto hashID : {BenchContainer::HashId::XXH32, BenchContainer::HashId::XXH64}) {
        std::vector<int> chunkSizes = { 5, 10, 20, 40, 200, 1000, size };
        std::map<int, long> best;
        for (int chunkSize : chunkSizes) {
            best[chunkSize] = std::numeric_limits<long>::max();
        }
        long hashAccumulator = 0;

        for (int i = 0; i < 10; i++) {
            for (int chunkSize : chunkSizes) {
                auto startTime = std::chrono::high_resolution_clock::now();
                int offset = 0;
                while (offset + chunkSize <= data.size()) {
                    hashAccumulator += BenchContainer::hash(hashID, data.data(), chunkSize, offset);
                    offset += chunkSize;
                }
                auto endTime = std::chrono::high_resolution_clock::now();
                long totalTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
                if (totalTime < best[chunkSize])
                    best[chunkSize] = totalTime;
            }
        }
        std::cout << "Hash accumulator (to prevent optimization): " << hashAccumulator << std::endl;
        std::cout << static_cast<int>(hashID) << std::endl; // Replace with better output for HashId if needed
        for (const auto& pair : best) {
            double totalTimeMs = pair.second / 1'000'000.0;
            std::cout << "chunk size = " << pair.first << " best time " << totalTimeMs << " ms" << std::endl;
        }
    }
}
