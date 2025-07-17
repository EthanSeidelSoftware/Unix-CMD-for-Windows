#include <iostream>
#include <fstream>
#include <filesystem>
#include <chrono>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: touch <file>" << std::endl;
        return 1;
    }

    fs::path filePath = argv[1];

    try {
        if (!fs::exists(filePath)) {
            // Create empty file
            std::ofstream file(filePath);
            if (!file) {
                std::cerr << "touch: cannot create file '" << filePath.string() << "'" << std::endl;
                return 1;
            }
            file.close();
        } else {
            // Update last write time to current time (C++17-compatible)
            auto now = std::chrono::system_clock::now();
            auto ftime = fs::file_time_type::clock::now() + 
                         std::chrono::duration_cast<fs::file_time_type::duration>(now.time_since_epoch() - std::chrono::system_clock::now().time_since_epoch());
            fs::last_write_time(filePath, ftime);
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "touch: error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
