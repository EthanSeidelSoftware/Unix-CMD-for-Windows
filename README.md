# Windows UNIX Command Pack

A collection of simple UNIX-style command-line utilities compiled as separate executables for Windows.  
This project brings common UNIX commands to Windows, implemented in C++ using modern features.

---

## Included Commands

| Command | Description                     | Notes                              |
|---------|---------------------------------|----------------------------------|
| `rm`    | Remove files/directories         | Supports recursive removal        |
| `clear` | Clear the console screen         | Calls Windows `cls`               |
| `ls`    | List directory contents          | Lists current or specified folder |
| `cat`   | Print file contents              | Supports multiple files           |
| `touch` | Create or update file timestamp | Creates empty file if missing     |
| `apt`   | Wrapper for `winget`             | For package management on Windows |
| `sudo`  | Run command as administrator     | Elevates privileges with UAC      |

---

## Building

Requires:
- [CMake](https://cmake.org/) (3.10 or later)
- Visual Studio 2017/2019/2022 with C++ tools

### Steps:

1. Clone the repository:

   ```sh
   git clone https://github.com/yourusername/windows-unix-command-pack.git
   cd windows-unix-command-pack
