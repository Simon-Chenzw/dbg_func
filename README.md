# dbg_func
a macro that can print values and their names  
提供一个简单的方法在输出调试法中输出数据

## 功能
* 提供了一个宏`dbg(...)`来往标准错误流中输出数据  
* 宏中可使用任意个数的参数，会打印在同一行中
* 支持输出
    + 数组
    + pair 
    + vector
    + deque
    + stack
    + queue
    + priority_queue
* 每行输出开头打印源代码所在行数
* 变量名彩色显示 
    + **only for linux**
* 会返回最后一个参数
    + 支持左值引用

## 使用方法
* 普通方法  
    + 直接include  
* for OIer
    + 在代码头部加入如下形式的代码
        ```cpp
        #ifndef ONLINE_JUDGE
        #include<dbg_func>
        #else 
        #define dbg(args...) args
        #endif
        ```
        + `ONLINE_JUDGE`是一个在许多评测平台都有定义的宏 如codeforces或luogu
        + 你也可以反向操作，采取在本地定一个宏，标记本机环境的方式
    + 或者将其添加进`<bits/stdc++.h>` 
        + **only for linux**
        + 然后添加如下代码
        ```cpp
        #ifndef open_dbg_func
        #define dbg(args...) args
        #endif
        ```
        + `open_dbg_func` 是`dbg_func`中定义的宏 用来标记是否include了`dbg_func`
* **注意**  
`dbg_func`中include了 `deque` `iostream` `queue` `stack` `string` `vector`  
请确保当你使用了这些库时，已经正确include了这些库，避免编译失败

# 已知的bug
* 若有参数没有输出运算符或者是不支持的类型,编译将无法通过