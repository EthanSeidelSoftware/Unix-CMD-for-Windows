#include <windows.h>
#include <shellapi.h>
#include <iostream>
#include <string>

// Helper to convert narrow string to wide string
std::wstring s2ws(const std::string& s) {
    int len;
    int slength = (int)s.length() + 1;
    len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
    std::wstring ret(len, L'\0');
    MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, &ret[0], len);
    return ret;
}

int wmain(int argc, wchar_t* argv[]) {
    if (argc < 2) {
        std::wcerr << L"Usage: sudo <command> [args...]" << std::endl;
        return 1;
    }

    // Build command line (skip argv[0])
    std::wstring params;
    for (int i = 1; i < argc; ++i) {
        if (i > 1) params += L" ";
        params += L"\"";
        params += argv[i];
        params += L"\"";
    }

    // Extract executable (first argument)
    std::wstring exe = argv[1];

    SHELLEXECUTEINFOW sei = { sizeof(sei) };
    sei.lpVerb = L"runas";              // wide string literal
    sei.lpFile = exe.c_str();
    sei.lpParameters = params.c_str() + exe.size() + 3; // careful with pointer arithmetic
    sei.nShow = SW_SHOWNORMAL;
    sei.fMask = SEE_MASK_NOASYNC;

    if (!ShellExecuteExW(&sei)) {
        DWORD err = GetLastError();
        if (err == ERROR_CANCELLED) {
            std::wcerr << L"User declined the elevation." << std::endl;
        }
        else {
            std::wcerr << L"Failed to launch as admin. Error code: " << err << std::endl;
        }
        return 1;
    }

    return 0;
}
