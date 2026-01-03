#include "Console/LinuxConsole.hpp"
#include "Menu/Menu.hpp"
#include <array>
#include <string>
#include <functional>
#include <iostream>

const unsigned MENU_SIZE = 3;

template<unsigned Size>
void displayMenu(Console* console, Menu<Size> &menu)
{
    // Clear the screen
    console->clear();
    console->write(menu.show());
}

int main() {
    const std::array<std::string, MENU_SIZE> menuItems = {
            "Option 1",
            "Option 2",
            "Exit"
    };

    const std::array<std::function<void()>, MENU_SIZE> menuActions = {
        [](){std::cout << "Execute option 1" << std::endl;},
        [](){std::cout << "Execute option 2" << std::endl;},
        [](){exit(0);}
    };

    int c;
    Console* console = new LinuxConsole();
    Menu<MENU_SIZE> menu = Menu<MENU_SIZE>(menuItems, menuActions);

    displayMenu<MENU_SIZE>(console, menu);

    while (true)
    {
        c = console->readKey();
        if (c == 27) { // ESC 
            if (console->readKey() == '[') { 
                switch (console->readKey()) { 
                    case 'A': 
                        menu.select(-1);
                        break; // flèche haut 
                    case 'B': 
                        menu.select(1);
                        break; // flèche bas 
                    } 
                }
        } else if (c == 10) { // Enter key
            menu.executeSelected();
            console->write("Press any key to continue...\n");
            console->readKey();
        } else {
            break; // Exit on any other key
        }
        displayMenu<MENU_SIZE>(console, menu);
    }
    
    delete console;
    return 0;
}