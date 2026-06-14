#include "init.hpp"
#include "fflib.hpp"
#include "textblobs.hpp"
#include <iostream>
#include <format>

void init::run() {
	fflib::mkdir(name);
	fflib::cd(name);
	std::string mainfile = R"(
#include <iostream>

int main() {
    std::cout << "Hello, World!\n";
    return 0;
}
)";
	if (!is_library) {
		fflib::touch("CMakeLists.txt", make_binary(name));
		fflib::mkdir("src");
		fflib::mkdir("include");
		fflib::cd("src");
		fflib::touch("main.cpp", mainfile);
		fflib::cddotdot();
		fflib::cd("include");
		fflib::touch("pch.h", "#pragma once\n//add headers here...");
		fflib::cddotdot();
	}
	else {
		fflib::touch("CMakeLists.txt", make_library(name));
		fflib::mkdir("src");
		fflib::mkdir("include");
		fflib::mkdir("demo");
		fflib::mkdir("cmake");
		fflib::cd("cmake");
		fflib::touch(
			std::format("{}Config.cmake", name), 
			make_config(name)
		);
		fflib::cddotdot();
		fflib::cd("demo");
		fflib::touch("demo.cpp", R"(
#include "lib.hpp"

int main() {
	printtest();
	return 0;
}
)");
		fflib::cddotdot();
		fflib::cd("include");
		fflib::touch("lib.hpp", "#pragma once\nvoid printtest();");
		fflib::touch("pch.h", "#pragma once\n//add headers here...");
		fflib::cddotdot();
		fflib::cd("src");
		fflib::touch("lib.cpp", R"(
#include <iostream>

void printtest() {
	std::cout << "Library working!\n";
	return;
}
)");
		fflib::cddotdot();
	}
	if (is_git == true) {
		std::system("git config core.autocrlf input");
		int result = std::system("git init");
		if (result != 0) {
			std::cout << "Could not make git repository\n";
		}
		fflib::touch(".gitignore", 
			R"(build/
out/
build/
.vscode/
.vs/
.idea/
*.o
*.obj
*.exe
*_i.c
*_p.c
*_h.h
*.ilk
*.meta
*.obj
*.iobj
*.pch
*.pdb
*.ipdb
*.pgc
*.pgd
*.rsp
*.sbr
*.tlb
*.tli
*.tlh
*.tmp
*.tmp_proj
*_wpftmp.csproj
*.log
*.vspscc
*.vssscc
.builds
*.pidb
*.svclog
*.scc
)");
		std::system("git add .");
		std::system("git commit -m \"Initial commit\"");
	}
	return;
}