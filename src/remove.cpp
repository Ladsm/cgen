#include "remove.hpp"
#include "fflib.hpp"
#include <iostream>
#include <format>

void removeCgen::run() {
    if (!fflib::exists("CMakeLists.txt")) {
        std::cout << "No CMakeLists.txt in directory\n";
        return;
    }

    if (is_header || is_both) {
        fflib::cd("include");
        if (!fflib::exists(std::format("{}.hpp", name))) {
            std::cout << "No file with that name";
            fflib::cddotdot();
            return;
        }
        fflib::rm(std::format("{}.hpp", name));
        fflib::cddotdot();
    }

    if (!is_header || is_both) {
        fflib::cd("src");
        if (!fflib::exists(std::format("{}.cpp", name))) {
            std::cout << "No file with that name";
            fflib::cddotdot();
            return;
        }
        fflib::rm(std::format("{}.cpp", name));
        fflib::cddotdot();
    }

    if (is_both || !is_header) {
        fflib::find_and_replace_file(
            "CMakeLists.txt",
            std::format("{}.cpp", name),
            ""
        );
    }
}
