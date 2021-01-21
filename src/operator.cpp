#include <iostream>
#include <type_traits>

namespace dbg_ns {

    const int max_len = 20;

    template <typename _pointer, bool bracket = true>
    class range {
      public:
        _pointer l, r;    // l <= r; should support (++ != ==)

        range(const _pointer& _l, const _pointer& _r): l(_l), r(_r) {}

        friend std::ostream& operator<<(std::ostream& os, const range& rg) {
            if (bracket) os << '{';    // if constexpr (c++17)
            if (rg.l != rg.r) {
                os << *rg.l;
                _pointer it = std::next(rg.l);
                for (int cnt = 2; it != rg.r && cnt <= max_len; std::advance(it, 1), ++cnt) os << ',' << ' ' << *it;
                if (it != rg.r) os << ',' << ' ' << "...";
            }
            if (bracket) os << '}';    // if constexpr (c++17)
            return os;
        }
    };

    template <typename T1, typename T2>
    constexpr range<typename std::decay<T1>::type> make_range(T1 l, T2 r) {
        static_assert(std::is_same<typename std::decay<T1>::type, typename std::decay<T2>::type>::value,
                      "l and r are not the same type");
        // Need to check if l,r is a pointer or iterator?
        // static_assert(std::is_pointer<T1>::value, "must be pointer");
        // static_assert(is_iterator<T1>::value, "must be iterator");
        return range<typename std::decay<T1>::type>(l, r);
    }

    // pair
    template <typename T1, typename T2>
    std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& pr) {
        os << '(' << pr.first << ',' << ' ' << pr.second << ')';
        return os;
    };

    // tuple

    // generate range
    template <typename T>
    inline auto rangeof(const T& container)
        -> decltype(range<decltype(std::begin(container))>(std::begin(container), std::end(container))) {
        return range<decltype(std::begin(container))>(std::begin(container), std::end(container));
    }

    // array
    template <typename T, std::size_t N>
    std::ostream& operator<<(std::ostream& os, const std::array<T, N>& container) {
        return os << rangeof(container);
    };

    // vector
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const std::vector<T>& container) {
        return os << rangeof(container);
    };

    // deque
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const std::deque<T>& container) {
        if (container.size() <= max_len) {
            return os << rangeof(container);
        }
        else {
            using range_type = range<decltype(container.begin()), false>;
            os << '{' << range_type(container.begin(), std::next(container.begin(), max_len / 2)) << ", ... , "
               << range_type(std::prev(container.end(), max_len / 2), container.end()) << '}';
            return os;
        }
    };

    // forward_list
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const std::forward_list<T>& container) {
        return os << rangeof(container);
    };

    // list
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const std::list<T>& container) {
        return os << rangeof(container);
    };

    // set
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const std::set<T>& container) {
        return os << rangeof(container);
    };

    // map
    template <typename T1, typename T2>
    std::ostream& operator<<(std::ostream& os, const std::map<T1, T2>& container) {
        return os << rangeof(container);
    };

    // multiset
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const std::multiset<T>& container) {
        return os << rangeof(container);
    };

    // multimap
    template <typename T1, typename T2>
    std::ostream& operator<<(std::ostream& os, const std::multimap<T1, T2>& container) {
        return os << rangeof(container);
    };

    // unordered_set
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const std::unordered_set<T>& container) {
        return os << rangeof(container);
    };

    // unordered_map
    template <typename T1, typename T2>
    std::ostream& operator<<(std::ostream& os, const std::unordered_map<T1, T2>& container) {
        return os << rangeof(container);
    };

    // unordered_multiset
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const std::unordered_multiset<T>& container) {
        return os << rangeof(container);
    };

    // unordered_multimap
    template <typename T1, typename T2>
    std::ostream& operator<<(std::ostream& os, const std::unordered_multimap<T1, T2>& container) {
        return os << rangeof(container);
    };

    template <typename container>
    const typename container::container_type& get_container(const container& a) {
        struct hack: container {
            static const typename container::container_type& get(const container& a) {
                return a.*(&hack::c);
            }
        };
        return hack::get(a);
    }

    // stack
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const std::stack<T>& container) {
        if (container.size() <= max_len) {
            return os << get_container(container);
        }
        else {
            const auto& dp = get_container(container);    // default: deque
            os << "{ ... , " << range<decltype(dp.begin()), false>(std::prev(dp.end(), max_len), dp.end()) << '}';
            return os;
        }
    };

    // queue
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const std::queue<T>& container) {
        return os << get_container(container);    // default: deque
    };

    // priority_queue
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const std::priority_queue<T>& container) {
        // TODO: Low performance
        typename std::decay<decltype(container)>::type pq_copy(container);
        os << '{';
        if (!container.empty()) {
            os << pq_copy.top();
            pq_copy.pop();
            for (int cnt = 2; !pq_copy.empty() && cnt <= max_len; ++cnt) {
                os << ',' << ' ' << pq_copy.top();
                pq_copy.pop();
            }
            if (!pq_copy.empty()) os << ',' << ' ' << "...";
        }
        os << '}';
        return os;
    };

}    // namespace dbg_ns