#ifndef MENU_HPP
#define MENU_HPP

#include <vector>
#include <string>
#include <functional>
#include <exception>

class Menu {
private:
    unsigned selectedIndex;
    unsigned size;
    std::vector<std::string> values;
    std::vector<std::function<void()>> actions;
public:
    Menu(const std::vector<std::string>& values, const std::vector<std::function<void()>>& actions);
    void select(int difference);
    void executeSelected();
    std::string show();
};

#endif // MENU_HPP