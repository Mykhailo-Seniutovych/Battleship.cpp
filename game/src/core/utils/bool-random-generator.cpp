#include "bool-random-generator.h"

BoolRandomGenerator::BoolRandomGenerator() : m_random_engine(m_random_device()) {}

bool BoolRandomGenerator::getRandomBool()
{
    return m_random_distribution(m_random_engine);
}