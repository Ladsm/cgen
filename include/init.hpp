#pragma once
#include <string>

class init {
public:
    init(bool is_library, bool is_git, const std::string& name)
        : is_library(is_library), is_git(is_git), name(name) {
    }
    void run();
private:
    bool is_library;
    bool is_git;
    std::string name;
};
