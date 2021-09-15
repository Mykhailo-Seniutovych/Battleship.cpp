#ifndef BATTLESHIP_SRC_CORE_UTILS_BOOL_RANDOM_GENERATOR_H
#define BATTLESHIP_SRC_CORE_UTILS_BOOL_RANDOM_GENERATOR_H

#include <random>

class BoolRandomGenerator
{
public:
    BoolRandomGenerator();
    bool getRandomBool();

private:
    std::random_device m_random_device;
    std::mt19937 m_random_engine;
    std::bernoulli_distribution m_random_distribution;
};

#endif
