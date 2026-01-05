#ifndef CONSOLE_HPP
#define CONSOLE_HPP

#include <string>

class Console
{
public:
    enum CTRL {
        UP,
        DOWN,
        ENTER
    };
    
    virtual void write(const std::string& message) = 0;
    virtual char readKey() = 0;
    virtual std::string readLine() = 0;
    virtual CTRL readControle() = 0;
    virtual void clear() = 0;
};

#endif // CONSOLE_HPP
