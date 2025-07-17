// ls.cpp - Lists files in the current directory (Windows)

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    fs::path dir = ".";

    // Optionally allow "ls [directory]"
    if (argc > 1) {
        dir = argv[1];
    }

    try {
        if (!fs::exists(dir)) {
            std::cerr << "ls: cannot access '" << dir << "': No such file or directory\n";
            return 1;
        }

        for (const auto& entry : fs::directory_iterator(dir)) {
            std::cout << entry.path().filename().string();

            if (fs::is_directory(entry.status())) {
                std::cout << "/";
            }

            std::cout << "\n";
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "ls: error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
