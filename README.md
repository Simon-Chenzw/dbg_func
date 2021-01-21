# dbg_func
a macro that can print values and their names  
提供一个简单的方法在输出调试法中输出数据  
Tested on MSVC 14.26 + Windows 10 & GCC 7.5.0 + Ubuntu 18.04  
**使用的时候请标明且附上github地址**

## Demo
* **[demo.cpp](demo.cpp):**
    ![demo_pic](pic/demo_pic.jpg)

## 功能
* 提供了一个宏`dbg(...)`来往标准错误流中输出数据  
* 宏中可使用任意个数的参数，会打印在同一行中
* 支持输出
    + 通过宏`dbgrange(l,r)`输出`[l,r)` l,r应为指针或迭代器
    + 数组
    + pair 
    + STL 容器
* 每行输出开头打印源代码所在行数
* 彩色显示 
* 会返回最后一个参数的引用
    + 若最后一个参数为左值返回左值引用，为右值则返回右值引用
    + 返回类型的判断代码为 `decltype((__VA_ARGS__))`


## 使用方法
* 下载`dbg_func`
* 直接include
* **注意:**  
`dbg_func`中include了 ***好多好多库***  
请确保在没有本库的情况下不会编译失败
* 其他的使用方式 **(for OIer)**
    1. 非OJ编译环境才使用`dbg_func`
        + `ONLINE_JUDGE`是一个在许多评测平台都有定义的宏 如`Codeforces`和`Luogu`
        + 使用前请确保**OJ有定义`ONLINE_JUDGE`**,或更换为OJ上定义的其他宏
        +   ```cpp
            #ifndef ONLINE_JUDGE
            #include "dbg_func"
            #else 
            #define dbg(...) (__VA_ARGS__)
            #endif
            ```
    2. 将`dbg_func`添加进`<bits/stdc++.h>` **only for linux**
        + `open_dbg_func` 是`dbg_func`中定义的宏 用来标记是否include了`dbg_func`
        +   ```cpp
            #ifndef open_dbg_func
            #define dbg(...) (__VA_ARGS__)
            #endif
            ```

## Tips
* 宏 `DBG_LEN` 指定了数组或STL容器的最大显示长度，默认为20
    + 在include本库前，添加宏可以更改
    + 例如 `#define DBG_LEN 50` 可以更改为 50
* 若想支持自定义类，可直接重载输出运算符

## 已知 issue 及 TODO
1. 若有参数没有输出运算符或者是不支持的类型,编译将无法通过
    - 添加识别是否有输出运算符的部分
2. `dbgrange(l,r)`作为最后一个参数,会返回内置的`interval`对象
    - 改为返回其中一个指针?
3. `dbg`不能为空
    - 为空时只输出行号，或者输出一些更多的东西