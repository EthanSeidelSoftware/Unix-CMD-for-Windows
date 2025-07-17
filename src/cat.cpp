// cat.cpp - prints the contents of one or more files to stdout

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: cat <file1> [file2 ...]" << std::endl;
        return 1;
    }

    for (int i = 1; i < argc; ++i) {
        std::ifstream file(argv[i]);
        if (!file) {
            std::cerr << "cat: " << argv[i] << ": No such file or cannot open" << std::endl;
            continue;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
    }

    return 0;
}
