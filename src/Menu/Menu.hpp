#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <string>
#include <functional>
#include <exception>

#include "../Console/Console.hpp"

class Menu {
private:
    unsigned selectedIndex;
    unsigned size;
    bool repeat;
    std::vector<std::string> values;
    std::vector<std::function<void()>> actions;
    Console* console;

    std::string toString();
    void display();

public:
    Menu(const std::vector<std::string>& values, const std::vector<std::function<void()>>& actions, Console* console, bool noReturn = false);
    void select(unsigned index);
    void selectUp();
    void selectDown();
    void executeSelected();
    void launch();
};

#endif // MENU_HPP