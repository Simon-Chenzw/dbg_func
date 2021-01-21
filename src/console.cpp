#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "operator.cpp"
#include "platform.cpp"

namespace dbg_ns {

    class namesplit {
      public:
        const std::string str;
        std::string::const_iterator it;

        namesplit(const std::string& _str): str(_str), it(str.cbegin()) {}

        void ignore() {
            bool instr = false;      //在字符串中
            bool escape = false;     // 转义
            int parentheses = 0;     // 小括号
            int curlybracket = 0;    // 大括号
            // int bracket = 0;         // 中括号
            while (it != str.cend()) {
                if (*it == ',' && !parentheses && !curlybracket && !instr) {
                    ++it;
                    break;
                }
                if (*it == '(')
                    parentheses++;
                else if (*it == ')')
                    parentheses--;
                else if (*it == '{')
                    curlybracket++;
                else if (*it == '}')
                    curlybracket--;
                else if (*it == '\"' && !escape)
                    instr = !instr;
                escape = (*it == '\\' && instr);
                ++it;
            }
        }

        std::string get() {
            std::string ret;
            bool instr = false;      //在字符串中
            bool escape = false;     // 转义
            int parentheses = 0;     // 小括号
            int curlybracket = 0;    // 大括号
            // int bracket = 0;         // 中括号
            while (it != str.cend()) {
                if (*it == ',' && !parentheses && !curlybracket && !instr) {
                    ++it;
                    break;
                }
                if (*it == '(')
                    parentheses++;
                else if (*it == ')')
                    parentheses--;
                else if (*it == '{')
                    curlybracket++;
                else if (*it == '}')
                    curlybracket--;
                else if (*it == '\"' && !escape)
                    instr = !instr;
                escape = (*it == '\\' && instr);
                if (*it != ' ') ret.push_back(*it);
                ++it;
            }
            return ret;
        }
    };

    class valpr {
      public:
        std::string name, value;

        valpr(const std::string& _name, const std::string& _value): name(_name), value(_value) {}

        friend std::ostream& operator<<(std::ostream& os, const valpr& pr) {
            if (!pr.name.empty())
                os << "   " << clr::cyan << pr.name << clr::reset << " = " << pr.value;
            else
                os << "   " << clr::green << pr.value << clr::reset;
            return os;
        }
    };

    class console {
      public:
        int line;
        namesplit names;
        std::vector<valpr> vals;

        console(const int& _line, const std::string& _namestr): line(_line), names(_namestr) {}

        template <typename T>
        console& operator<<(T a) {
            std::ostringstream ss;
            ss << std::boolalpha << a;
            vals.emplace_back(names.get(), ss.str());
            return *this;
        }

        template <typename T, std::size_t N>
        console& operator<<(const T (&arr)[N]) {
            std::ostringstream ss;
            ss << std::boolalpha << range<decltype(std::begin(arr))>(std::begin(arr), std::end(arr));
            vals.emplace_back(names.get(), ss.str());
            return *this;
        }

        template <std::size_t N>
        console& operator<<(const char (&str)[N]) {
            names.ignore();
            vals.emplace_back("", str);
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& os, const console& con) {
            // TODO 自动匹配行宽 自动换行format
            os << "[" << std::setw(2) << std::setfill('0') << con.line << ']';
            for (const valpr& val : con.vals) os << val;
            os << std::endl;
            return os;
        }
    };

}    // namespace dbg_ns