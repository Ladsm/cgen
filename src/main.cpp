#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <format>
#include "textblobs.hpp"
#include "init.hpp"
#include "add.hpp"
#include "remove.hpp"
#include "fflib.hpp"

int main(int argc, char* argv[]) {
    std::vector<std::string> args(argv, argv + argc);
    if (args.size() < 2) {
        std::cout << "Usage: cgen <command> [name] [flags...]\n";
        return 1;
    }
    const std::string command = args[1];
    if (command == "help") {
        std::cout << R"(Usage: cgen <command> [name] [flags...]

Cgen is a cmake generator and C/C++ helper program.
It is designed to smooth out the cmake experience.

Commands:
    help    Shows Help Menu
    init    Makes a new project. E.g., `cgen init my_project -bin`
    add     Adds a source file, header, or both to CMakeLists.txt.
            Do not include file extensions. E.g., `cgen add file --both`
    clean   Wipes the build directory.
    build   Compiles the project using CMake.
    run     Runs the compiled executable from the build directory.
    license Genorates a license. E.g, `cgen license --mit`
    version Shows version info

Flags:
    init:
        -lib          Creates a static library project configuration
        -bin          Creates a binary executable project configuration (Default)
        -git          Initializes a Git repository (requires git in your $PATH)

    add:
        -h, --hpp     Makes a standalone header file instead of a cpp file
        -b, --both    Makes both a cpp file and a header file
        --class       Creates a new class (cpp and header file)
        --struct      Creates a new struct (cpp and header file)
    
    license:
        --mit         MIT license
        --gpl2        GPL2 license
        --gpl3        GPL3 license
        --apache2     Apache 2.0 Apache 
        --bsd2        2-Clause BSD License
        --bsd3        3-Clause BSD License
)";
        return 0;
    }

    else if (command == "version") {
        std::cout << "1.0\n";
        return 0;
    }

    else if (command == "init") {
        if (args.size() < 3) {
            std::cout << "Error: Please provide a project name.\n";
            return 1;
        }
        const std::string name = args[2];
        bool is_library = false;
        bool is_binary = false;
        bool git = false;
        for (size_t i = 3; i < args.size(); i++) {
            if (args[i] == "-lib") is_library = true;
            else if (args[i] == "-bin") is_binary = true;
            else if (args[i] == "-git") git = true;
        }
        if (is_library && is_binary) {
            std::cout << "You can't make it a binary and a library at the same time!\n";
            return 1;
        }
        if (!is_library && !is_binary) {
            is_binary = true;
        }
        init initualizer(is_library, git, name);
        initualizer.run();
    }

    else if (command == "add") {
        if (args.size() < 3) {
            std::cout << "Error: Please provide a filename.\n";
            return 1;
        }
        const std::string filename = args[2];
        bool is_header = false;
        bool is_struct = false;
        bool is_class = false;
        bool is_both = false;
        for (size_t i = 3; i < args.size(); i++) {
            if (args[i] == "-h" || args[i] == "--hpp") is_header = true;
            else if (args[i] == "--class") is_class = true;
            else if (args[i] == "-b" || args[i] == "--both") is_both = true;
            else if (args[i] == "--struct") is_struct = true;
        }
        if (is_class || is_struct) {
            is_both = true;
        }
        if (is_both) {
            is_header = false;
        }
        add addition(is_header, is_class, is_both, is_struct, filename);
        addition.run();
    }

    else if (command == "remove") {
        if (args.size() < 3) {
            std::cout << "Error: Please provide a filename.\n";
            return 1;
        }
        const std::string filename = args[2];
        bool is_header = false;
        bool is_both = false;
        for (size_t i = 3; i < args.size(); i++) {
            if (args[i] == "-h" || args[i] == "--hpp") is_header = true;
            else if (args[i] == "-b" || args[i] == "--both") is_both = true;
        }
        removeCgen Remove(is_header, is_both, filename);
        Remove.run();
    }

    else if (command == "clean") {
        if (!fflib::exists("CMakeLists.txt")) {
            std::cout << "No CMakeLists.txt in directory\n";
            return 1;
        }
        if (fflib::exists("build")) {
            fflib::rm_rf("build");
        }
        else {
            std::cout << "Nothing to clean.\n";
        }
        return 0;
    }

    else if (command == "build") {
        if (!fflib::exists("CMakeLists.txt")) {
            std::cout << "No CMakeLists.txt in directory\n";
            return 1;
        }
        if (!fflib::exists("build")) {
            fflib::mkdir("build");
        }
        fflib::cd("build");
#ifdef _WIN32
        std::system("cmake.exe ..");
        std::system("cmake.exe --build .");
#else
        std::system("cmake ..");
        std::system("cmake --build .");
#endif
        fflib::cddotdot();
        return 0;
    }

    else if (command == "run") {
        if (!fflib::exists("build")) {
            std::cout << "Error: No build directory found. Please run 'cgen build' first.\n";
            return 1;
        }
        std::string full_path = fflib::current_path();
        size_t last_slash = full_path.find_last_of("/\\");
        std::string project_name = (last_slash != std::string::npos) ? full_path.substr(last_slash + 1) : "app";
        fflib::cd("build");
#ifdef _WIN32
        std::string exe_path = project_name + ".exe";
        if (fflib::exists(std::format("Debug\\{}.exe", project_name))) {
            exe_path = std::format("Debug\\{}.exe", project_name);
        }
        else if (fflib::exists(std::format("Release\\{}.exe", project_name))) {
            exe_path = std::format("Release\\{}.exe", project_name);
        }
        if (!fflib::exists(exe_path)) {
            std::cout << "Error: Executable not found.\n";
            fflib::cddotdot();
            return 1;
        }
        std::system(exe_path.c_str());
#else
        std::string elf_path = std::format("./{}", project_name);
        if (!fflib::exists(project_name)) {
            std::cout << "Error: Executable not found.\n";
            fflib::cddotdot();
            return 1;
        }
        std::system(elf_path.c_str());
#endif
        fflib::cddotdot();
        return 0;
    }

    else if (command == "license") {
        if (args.size() < 3) {
            std::cout << "Error: Please provide a license flag (e.g., cgen license --mit)\n";
            return 1;
        }
        const std::string licensename = args[2];
        if (licensename == "--mit") {
            fflib::touch("LICENSE", mit());
        }
        else if (licensename == "--gpl2") {
            fflib::touch("LICENSE", gpl2());
        }
        else if (licensename == "--gpl3") {
            fflib::touch("LICENSE", gpl3());
        }
        else if (licensename == "--apache2") {
            fflib::touch("LICENSE", apache2());
        }
        else if (licensename == "--bsd2") {
            fflib::touch("LICENSE", bsd2());
        }
        else if (licensename == "--bsd3") {
            fflib::touch("LICENSE", bsd3());
        }
        else {
            std::cout << "No license with that name.\n";
            return 1;
        }
        return 0;
    }

    else {
        std::cout << "Unknown command: " << command << "\n";
        return 1;
    }

    return 0;
}
