#include "StringHelper.h"

std::vector<std::string> StringHelper::split(const std::string& str, const std::string& delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> result;

    while ((pos_end = str.find(delimiter, pos_start)) != std::string::npos)
    {
        token = str.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        result.push_back(token);
    }

    result.push_back(str.substr(pos_start));
    return result;
}