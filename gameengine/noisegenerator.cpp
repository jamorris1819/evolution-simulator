#include "pch.h"
#include "noisegenerator.h"
#include <vector>
#include "vertex.h"
#define PI 3.1415326

double NoiseGenerator::generate(double x, double y) {
    return noise.get()->GetSimplex(x, y);
}
std::vector<BiomeType> NoiseGenerator::generateHexagon(double x, double y, int size) {
    std::vector<BiomeType> type;

    type.push_back(getBiomeType(generate(x, y)));

    for (int i = 0; i < 6; i++) {
        // first point
        float angle_deg = 60 * i - 30;
        float angle_rad = (PI / 180) * angle_deg;
        engine::Vertex v(cos(angle_rad) * size, sin(angle_rad) * size);

        auto pos = engine::Vertex(x + v.getPosition().x, y + v.getPosition().y);
        auto height = generate(pos.getPosition().x , pos.getPosition().y);
        auto biomeType = getBiomeType(height);
        type.push_back(biomeType);
    }

    return type;
}

BiomeType NoiseGenerator::getBiomeType(double height) {
    return height > 0.4 ? BiomeType::GRASS : BiomeType::WATER;
}
