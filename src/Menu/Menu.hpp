#ifndef MENU_HPP
#define MENU_HPP

#include <array>
#include <string>
#include <functional>

template<unsigned Size>
class Menu {
private:
    unsigned selectedIndex;
    std::array<std::string, Size> values;
    std::array<std::function<void()>, Size> actions;
public:
    Menu(const std::array<std::string, Size>& values, const std::array<std::function<void()>, Size>& actions);
    void select(int difference);
    void executeSelected();
    std::string show();
};

/// Implementation ///

template<unsigned Size>
Menu<Size>::Menu(const std::array<std::string, Size>& _values, const std::array<std::function<void()>, Size>& _actions):
selectedIndex(0), values(_values), actions(_actions)
{

}

template<unsigned Size>
void Menu<Size>::select(int difference){
    selectedIndex += difference;
    if(selectedIndex < 0){
        selectedIndex = Size + selectedIndex;
    } else if(selectedIndex >= Size){
        selectedIndex %= Size;
    }
}

template<unsigned Size>
void Menu<Size>::executeSelected(){
    actions.at(selectedIndex)();
}

template<unsigned Size>
std::string Menu<Size>::show(){
    std::string result = "";
    
    for(unsigned index = 0; index < Size; ++index){
        if(index == selectedIndex){
            result += "> " + values[index] + " <\n";
        } else {
            result += "  " + values[index] + " \n";
        }
    }

    return result;
}

#endif // MENU_HPP