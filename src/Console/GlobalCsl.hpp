#ifndef GLOBALCSL_HPP
#define GLOBALCSL_HPP

#include "Console.hpp"

class GlobaleCSL {
private:
    static Console* console;
public:
    static Console* get();
    static void del();
};

#endif // GLOBAL_HPP