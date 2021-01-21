#include <iostream>
namespace dbg_ns {
    enum class clr : int {
        reset = 0,
        black = 30,
        red = 31,
        green = 32,
        yellow = 33,
        blue = 34,
        magenta = 35,
        cyan = 36,
        white = 37,
        on_black = 40,
        on_red = 41,
        on_green = 42,
        on_yellow = 43,
        on_blue = 44,
        on_magenta = 45,
        on_cyan = 46,
        on_white = 47,
    };

#ifdef __unix__
    std::ostream& operator<<(std::ostream& os, const clr& color) {
        return os << "\033[" << static_cast<int>(color) << "m";
    }
#elif defined(_WIN32) || defined(WIN32)
    // #    define WIN32_LEAN_AND_MEAN    // Exclude rarely-used stuff from Windows headers
    // #    define NOMINMAX               // Fixes the conflicts with STL
    // #    include <Windows.h>
    std::ostream& operator<<(std::ostream& os, const clr color) {
        // static const auto init = [] {
        //     // Set output mode to handle virtual terminal sequences
        //     HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        //     DWORD dwMode = 0;
        //     GetConsoleMode(hOut, &dwMode);
        //     SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        //     return 0;
        // }();
        return os << "\033[" << static_cast<int>(color) << "m";
    }
#else
#    pragma message("Unsupported platforms, cannot print out in color")
    std::ostream& operator<<(std::ostream& os, const clr& color) {
        return os;
    }
#endif

}    // namespace dbg_ns