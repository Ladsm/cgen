#pragma once
#include <string>

class add {
public:
    add(bool x, bool y, bool z, bool m, const std::string& n)
        : is_header(x), is_class(y), is_both(z), is_struct(m), name(n) {
    }
    void run();
private:
    std::string name = "";
    bool is_header = false;
    bool is_struct = false;
    bool is_class = false;
    bool is_both = false;
};