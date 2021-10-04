#ifndef BATTLESHIP_SRC_CORE_UTILS_TEXT_UTILS_H
#define BATTLESHIP_SRC_CORE_UTILS_TEXT_UTILS_H
#include <string>

class TextUtils
{
public:
    static bool containsOnlyAscii(const std::string &t_value);
};

#endif