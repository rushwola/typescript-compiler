#include <iostream>
#include "config.h"


void CONFIG::printInfo() {
    // 构造函数实现
    std::cout << "Hello, CONFIG!" << std::endl;
}
bool CONFIG::verbose = false;
bool CONFIG::traceTypeChecker = false;
;