#include <iostream>              // For input/output (e.g., std::cout, std::cerr)
#include <filesystem>           // C++17 feature for file system operations
#include <string>               // For using std::string
#include <vector>               // For using std::vector to store multiple file paths

// Use the std::filesystem namespace to simplify function calls
namespace fs = std::filesystem;

// Helper function: checks if a given argument is a flag (starts with a dash '-')
bool is_flag(const std::string& arg) {
    return !arg.empty() && arg[0] == '-';
}

int main(int argc, char* argv[]) {
    // Flags for recursive (-r) and force (-f) deletion
    bool recursive = false;
    bool force = false;
    bool allowmultiplepaths = false;

    // Vector to store all file/folder paths provided as arguments
    std::vector<std::string> targets;

    // Loop through all command-line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        // If the argument starts with a dash, treat it as a flag
        if (is_flag(arg)) {
            // Check if the flag string contains 'r' or 'f'
            if (arg.find('r') != std::string::npos)
                recursive = true;
            if (arg.find('f') != std::string::npos)
                force = true;
            if (arg.find("mf") != std::string::npos)
                allowmultiplepaths = true;
        }
        else {
            // Otherwise, treat it as a file or directory path to delete
            targets.push_back(arg);
        }
    }

    // If no paths were given, print an error and exit
    if (targets.empty()) {
        std::cerr << "rm: missing operand\n";
        return 1;
    }

    // Warn if multiple paths and -mp not set
    if (targets.size() > 1 && !allowmultiplepaths) {
        std::cerr << "rm: multiple paths provided; use -mp to allow multiple deletions safely\n";
        return 1;
    }

    // Loop through each file/folder path
    for (const auto& path_str : targets) {
        fs::path path(path_str);  // Convert string to a filesystem path object

        try {
            // If the file/folder doesn't exist
            if (!fs::exists(path)) {
                if (!force) {
                    std::cerr << "rm: cannot remove '" << path << "': No such file or directory\n";
                }
                continue; // Skip to the next target
            }

            // If it's a directory
            if (fs::is_directory(path)) {
                // Only allow recursive directory deletion with both -r and -f
                if (recursive && force) {
                    fs::remove_all(path);  // Deletes all contents inside the folder
                }
                else {
                    std::cerr << "rm: cannot remove '" << path << "': Is a directory (use -rf)\n";
                }
            }
            else {
                // If it's a file, delete it
                fs::remove(path);
            }
        }
        catch (const std::exception& e) {
            // Catch and report any error during deletion
            std::cerr << "rm: error removing '" << path << "': " << e.what() << "\n";
        }
    }

    return 0; // Program completed successfully
}
