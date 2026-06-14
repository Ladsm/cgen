#include "add.hpp"
#include "fflib.hpp"
#include <iostream>
#include <format>

void add::run() {
    if (!fflib::exists("CMakeLists.txt")) {
        std::cout << "No CMakeLists.txt in directory\n";
        return;
    }
    bool created_cpp = false;
    if (is_header) {
        fflib::cd("include");
        fflib::touch(std::format("{}.hpp", name), "#pragma once\n\n");
        fflib::cddotdot();
        return;
    }
    else if (is_both) {
        fflib::cd("include");
        if (is_struct) {
            fflib::touch(
                std::format("{}.hpp", name),
                std::format("#pragma once\n\nstruct {} {{\n\t\n}};\n", name)
            );
        }
        else if (is_class) {
            fflib::touch(
                std::format("{}.hpp", name), 
                std::format("#pragma once\n\nclass {} {{\n\t\n}};\n", name)
            );
        }
        else {
            fflib::touch(std::format("{}.hpp", name), "#pragma once\n");
        }
        fflib::cddotdot();
        fflib::cd("src");
        fflib::touch(
            std::format("{}.cpp", name), 
            std::format("#include \"{}.hpp\"\n", name)
        );
        fflib::cddotdot();
        created_cpp = true;
    }
    else {
        fflib::cd("src");
        fflib::touch(
            std::format("{}.cpp", name),
            "\n"
        );
        fflib::cddotdot();
        created_cpp = true;
    }
    if (created_cpp) {
        if (fflib::cat("CMakeLists.txt").find("#CGEN_ANCHOR") != std::string::npos) {
            fflib::append_at_point_file(
                "CMakeLists.txt",
                "#CGEN_ANCHOR",
                std::format("\n    src/{}.cpp", name)
            );
        }
        else {
            std::cout << "Warning: '#CGEN_ANCHOR' anchor comment not found in CMakeLists.txt. File not added to target.\n";
        }
    }
}
