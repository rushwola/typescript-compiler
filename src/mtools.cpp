#include <iostream>
#include <string>

bool endsWith( char const * str,  char const * suffix) {
    std::string str1(str);
    std::string suffix1(suffix);
    if (str1.length() < suffix1.length()) {
        return false;
    }
    std::string end = str1.substr(str1.length() - suffix1.length());
    return end.compare(suffix1) == 0;
};