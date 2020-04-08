# dbg_func
a macro that can print values and their names  
提供一个简单的方法在输出调试法中输出数据

## 功能
* 提供了一个宏`dbg(...)`来往标准错误流中输出数据  
* 宏中可使用任意个数的参数，会打印在同一行中
* 支持输出
    + 通过`inter(l,r)`输出`[l,r]` l,r应为指针或迭代器
    + 数组
    + pair 
    + vector
    + deque
    + stack
    + queue
    + priority_queue
* 每行输出开头打印源代码所在行数
* 彩色显示 
    + **only for linux**
* 会返回最后一个参数
    + 支持左值引用

## Demo
* **src/demo.cpp:**
    ![demo_pic](pic/demo_pic.jpg)

## 使用方法
* 下载`src/dbg_func`
* 直接include
* **注意:**  
`dbg_func`中include了 `<iostream>` `<string>` `<vector>` `<deque>` `<stack>` `<queue>`  
请确保在没有本库的情况下不会编译失败
* 其他的使用方式 **(for OIer)**
    1. **(推荐方式)** 将`dbg_func`添加进`<bits/stdc++.h>`
        + **only for linux**
        + 添加如下代码
            ```cpp
            #ifndef open_dbg_func
            #define dbg(args...) (args)
            #endif
            ```
        + `open_dbg_func` 是`dbg_func`中定义的宏 用来标记是否include了`dbg_func`
    2. 在`<iostream>`或其他头文件或编译器中定义一个宏标记本机环境
        + 添加如下代码
            ```cpp
            #ifdef IS_LOCAL_ENV
            #include <dbg_func>
            #else 
            #define dbg(args...) (args)
            #endif
            ```
    3. 采取标记OJ的方式
        + `ONLINE_JUDGE`是一个在许多评测平台都有定义的宏 如`Codeforces`或`Luogu`
        + 添加如下代码
            ```cpp
            #ifndef ONLINE_JUDGE
            #include <dbg_func>
            #else 
            #define dbg(args...) (args)
            #endif
            ```
        + 使用前请确保**OJ有定义`ONLINE_JUDGE`**,或更换为OJ上定义的其他宏

## Tips
* `dbg_namespace::max_len`指定了vector等STL容器的最大显示长度，默认为30
* 可自行更改`\033`代码 改变默认颜色
* 若想支持自定义的`class`，可直接重载输出运算符
* 若有建议或bug，可以提issue
* 如果可以的话，使用`dbg_func`的时候请标明且附上github地址

## TODO
1. 若有参数没有输出运算符或者是不支持的类型,编译将无法通过
    - 添加识别是否有输出运算符的部分
2. `inter(l,r)`作为最后一个参数,会返回内置的`interval`对象
    - 改为返回其中一个指针(?)
3. `dbg`不能为空
    - 为空时只输出行号，或者输出一些更多的东西