#include "text-utils.h"

bool TextUtils::containsOnlyAscii(const std::string &t_value)
{
    for (auto character : t_value)
    {
        if (static_cast<unsigned char>(character) > 127)
        {
            return false;
        }
    }
    return true;
}