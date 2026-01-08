#include "GlobalCsl.hpp"
#include "LinuxConsole.hpp"

Console *GlobaleCSL::console = nullptr;

Console *GlobaleCSL::get()
{
    if(console == nullptr){
        console = new LinuxConsole();
    }

    return console;
}

void GlobaleCSL::del()
{
    if(console != nullptr){
        delete console;
        console = nullptr;
    }
}