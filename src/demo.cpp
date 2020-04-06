#include "dbg_func"
using namespace std;

int func(int n) {
    if (n == 0)
        return 1;
    else
        return dbg(n, n * func(n - 1));
}

int main() {
    dbg(dbg_namespace::max_len);

    vector<int> vec;
    for (int i = 0; i < 40; i++) vec.push_back(i);
    dbg(vec);

    deque<int> deq;
    for (int i = 0; i < 40; i++) deq.push_back(i);
    dbg(deq);

    stack<int> sta;
    for (int i = 0; i < 40; i++) sta.push(i);
    dbg(sta);

    queue<int> que;
    for (int i = 0; i < 40; i++) que.push(i);
    dbg(que);

    priority_queue<int> pq;
    for (int i = 0; i < 40; i++) pq.push(i);
    dbg(pq);

    pair<int, bool> pr(123, 9.87);
    dbg(pr);

    string str = "this is a string";
    char ch[] = "this is a char[]";
    dbg("this is a const char[]");
    dbg(ch);
    dbg(str);

    const char demo[] = "address of the return variable";
    dbg(&demo, &dbg(demo));

    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    dbg(arr);

    dbg(inter(arr + 3, arr + 7));

    dbg("function:");
    func(5);
}
