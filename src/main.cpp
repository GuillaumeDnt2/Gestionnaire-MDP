#include "Console/LinuxConsole.hpp"
#include <array>
#include <string>

Console* console = new LinuxConsole();

void displayMenu(unsigned selectedIndex = 0)
{
    const std::array<std::string, 5> menuItems = {
        "Option 1",
        "Option 2",
        "Option 3",
        "Option quatre",
        "Exit"
    };

    // Clear the screen
    console->clear();

    for (unsigned int i = 0; i < menuItems.size(); ++i)
    {
        if (i == selectedIndex)
        {
            // Highlight the selected item
            console->write("> " + menuItems[i] + " <\n");
        }
        else
        {
            console->write("  " + menuItems[i] + "\n");
        }
    }
}

int main() {
    int c;
    unsigned selectedIndex = 0;

    displayMenu();

    while (true)
    {
        c = console->readKey();
        if (c == 27) { // ESC 
            if (console->readKey() == '[') { 
                switch (console->readKey()) { 
                    case 'A': 
                        selectedIndex == 0 ? selectedIndex = 3 : selectedIndex--;
                        break; // flèche haut 
                    case 'B': selectedIndex == 3 ? selectedIndex = 0 : selectedIndex++;
                        break; // flèche bas 
                    } 
                }
                displayMenu(selectedIndex);
            }
    
    }
    
    delete console;
    return 0;
}