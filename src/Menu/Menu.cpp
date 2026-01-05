#include <string>

#include "Menu.hpp"

Menu::Menu(const std::vector<std::string>& _values, const std::vector<std::function<void()>>& _actions, Console* _console, bool noReturn):
selectedIndex(0), values(_values), actions(_actions), repeat(true), console(_console)
{
    if(values.size() != actions.size()){
        throw "Menu vectors must be the same size";
    }

    if(console == nullptr){
        throw "Console can't be null";
    }

    if(!noReturn){
        values.push_back("Retour");
        actions.push_back([this](){repeat = false;});
    }

    size = values.size();
}

void Menu::select(unsigned index){
    if(index >= size){
        throw "The selected item must be between 0 and " + std::to_string(size - 1) + " (value: " + std::to_string(index) + ")"; 
    }

    selectedIndex = index;
}

void Menu::selectUp(){
    unsigned newIndex = selectedIndex - 1;
    
    // Check underflow
    if(newIndex > selectedIndex){
        newIndex = size -1;
    }

    select(newIndex);
}

void Menu::selectDown(){
    unsigned newIndex = selectedIndex + 1;
    if(selectedIndex == size){
        newIndex = 0;
    }

    select(newIndex);
}

void Menu::executeSelected(){
    actions.at(selectedIndex)();
}

std::string Menu::toString(){
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

void Menu::display(){
    console->clear();
    console->write(toString());
}

void Menu::launch(){
    display();
    repeat = true;
    while (repeat)
    {
        switch (console->readControle())
        {
        case Console::UP :
            selectUp();
            display();
            break;

        case Console::DOWN :
            selectDown();
            display();
            break;

        case Console::ENTER :
            executeSelected();
            break;
        }
    }
    
}