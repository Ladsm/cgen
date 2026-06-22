#pragma once
#pragma once
#include <string>

class removeCgen {
public:
    removeCgen(bool x, bool y, const std::string& n)
        : is_header(x), is_both(y), name(n) {
    }
    void run();
private:
    std::string name = "";
    bool is_header = false;
    bool is_both = false;
};