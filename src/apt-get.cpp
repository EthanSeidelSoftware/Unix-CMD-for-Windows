// apt.cpp - a simple wrapper that calls winget with args

#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    std::string cmd = "winget";

    // Append all arguments passed to apt.exe
    for (int i = 1; i < argc; ++i) {
        cmd += " ";
        cmd += argv[i];
    }

    std::cout << "Running: " << cmd << std::endl;

    int ret = system(cmd.c_str());
    return ret;
}
