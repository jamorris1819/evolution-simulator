#include "pch.h"
#include "noisegenerator.h"
#include <vector>

double NoiseGenerator::generate(double x, double y) {
    return 0.0;
}
std::vector<BiomeType> NoiseGenerator::generateHexagon(double x, double y, int size) {
    std::vector<BiomeType> type;

    for (int i = 0; i < 7; i++) {
        if (rand() % 2 == 0) type.push_back(BiomeType::GRASS);
        else type.push_back(BiomeType::WATER);
    }

    return type;
}