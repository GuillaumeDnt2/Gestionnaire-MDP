#include "Console.hpp"
#include <string>
#include <termios.h>

class LinuxConsole : public Console
{
private:
    struct termios canon_t, raw_t;
    void SetRawMode(bool enable);
public:
    LinuxConsole();
    void write(const std::string& message) override;
    char readKey() override;
    std::string readLine() override;
    void clear() override;
};