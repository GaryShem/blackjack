#include "Utils.h"

bool Utils::StringEndsWith(std::string fullString, std::string ending)
{
    if (fullString.length() < ending.length())
    {
        return false;
    }
    for (int i = 1; i <= ending.length(); i++)
    {
        if (fullString[fullString.length() - i] != ending[ending.length() - i])
        {
            return false;
        }
    }
    return true;
    return fullString.compare(fullString.length() - ending.length(), ending.length(), ending);
}
