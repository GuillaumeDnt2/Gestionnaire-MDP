#include "Menu.hpp"

Menu::Menu(const std::vector<std::string>& _values, const std::vector<std::function<void()>>& _actions):
selectedIndex(0), values(_values), actions(_actions)
{
    if(values.size() != actions.size()){
        throw "Menu vectors must be the same size";
    }

    size = values.size();
}

void Menu::select(int difference){
    selectedIndex += difference;
    if(selectedIndex < 0){
        selectedIndex = size + selectedIndex;
    } else if(selectedIndex >= size){
        selectedIndex %= size;
    }
}

void Menu::executeSelected(){
    actions.at(selectedIndex)();
}

std::string Menu::show(){
    std::string result = "";
    
    for(unsigned index = 0; index < size; ++index){
        if(index == selectedIndex){
            result += "> " + values[index] + " <\n";
        } else {
            result += "  " + values[index] + " \n";
        }
    }

    return result;
}