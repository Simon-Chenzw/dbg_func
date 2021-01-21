#include <string>
#include "console.cpp"

namespace dbg_ns {

    template <typename Ret>
    class pkg {
      public:
        console con;
        pkg(int _line, const std::string& _namestr): con(_line, _namestr) {}

        template <typename T>
        Ret solve(T&& a) {
            con << a;
            std::cerr << con;
            return a;
        }

        template <typename T, typename... Args>
        Ret solve(T&& a, Args&&... args) {
            con << a;
            return solve(args...);
        }
    };

}    // namespace dbg_ns
