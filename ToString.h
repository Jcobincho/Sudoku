#pragma once
#include <sstream>
#include <string>

class ToString
{
public:
    template <typename T>
    static std::string ConvertToString(T value)
    {
        std::ostringstream oss;
        oss << value;
        return oss.str();
    }
};
