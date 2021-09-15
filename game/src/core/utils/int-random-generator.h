#ifndef BATTLESHIP_SRC_CORE_UTILS_INT_RANDOM_GENERATOR_H
#define BATTLESHIP_SRC_CORE_UTILS_INT_RANDOM_GENERATOR_H

#include <random>
#include <cstdint>
#include <iostream>

template <typename T>
class IntRandomGenerator
{
public:
    IntRandomGenerator(T t_min, T t_max)
        : m_random_engine(m_random_device()), m_random_distribution(t_min, t_max)
    {
    }
    
    T getRandomInt()
    {

        return m_random_distribution(m_random_engine);
    }

private:
    std::random_device m_random_device;
    std::mt19937 m_random_engine;
    std::uniform_int_distribution<T> m_random_distribution;
};

#endif
