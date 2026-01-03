#include <string>

class Console
{
public:
    virtual void write(const std::string& message) = 0;
    virtual char readKey() = 0;
    virtual std::string readLine() = 0;
    virtual void clear() = 0;
};
