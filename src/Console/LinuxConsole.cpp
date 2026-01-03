#include "LinuxConsole.hpp"
#include <termios.h>
#include <unistd.h>
#include <iostream>

LinuxConsole::LinuxConsole()
{
    // Get the current terminal attributes
    tcgetattr(STDIN_FILENO, &canon_t);

    // Set up raw mode attributes
    raw_t = canon_t;
    raw_t.c_lflag &= ~(ICANON | ECHO);
}

void LinuxConsole::SetRawMode(bool enable)
{
    if (enable)
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &raw_t);
    }
    else
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &canon_t);
    }
}

void LinuxConsole::write(const std::string& message)
{
    std::cout << message;
}

char LinuxConsole::readKey()
{
    char ch;
    SetRawMode(true);
    ch = getchar();
    SetRawMode(false);
    return ch;
}

std::string LinuxConsole::readLine()
{
    std::string line;
    std::getline(std::cin, line);
    return line;
}

void LinuxConsole::clear()
{
    std::cout << "\033[H\033[2J";
}