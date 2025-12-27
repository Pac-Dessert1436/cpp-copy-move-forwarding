#include <iostream>

bool debug_enabled = false;

inline void debug_print(const std::string &message)
{
    if (debug_enabled)
    {
        std::cout << "[DEBUG] " << message << std::endl;
    }
}