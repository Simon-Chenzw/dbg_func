#include "dbg_func"
using namespace std;

int f(int n) {
    if (n == 0)
        return 1;
    else
        return dbg(n, n * f(n - 1));
}

vector<int>& test(vector<int>& a) {
    a[0]++;
    return dbg(a);
}

int main() {
    vector<int> a {1, 2, 3};
    deque<int> b;
    b.push_back(1);
    b.push_back(2);
    b.push_back(3);
    stack<int> c;
    c.push(1);
    c.push(2);
    c.push(3);
    priority_queue<int> d;
    d.push(1);
    d.push(2);
    d.push(3);
    dbg(a, b, c, d);

    dbg(&a);
    dbg(&test(a));

    string s = "test";
    dbg("test");
    dbg(s);

    cout << dbg(f(10));

    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
#line 123
    dbg(arr);
}
