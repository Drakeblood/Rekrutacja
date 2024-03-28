#pragma once

#include <string>
#include <vector>

class StringHelper
{
public:
    static std::vector<std::string> split(const std::string& str, const std::string& delimiter);
};