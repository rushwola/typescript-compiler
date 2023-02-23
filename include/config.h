#ifndef CONFIG_H
#define CONFIG_H

class CONFIG {
public:
    //在编译过程中是否显示详细的信息
    static bool verbose;
    static bool traceTypeChecker;
    void printInfo();
};
#endif