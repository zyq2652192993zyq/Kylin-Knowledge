> # GDB

参考：

* [100个GDB小技巧](https://github.com/hellogcc/100-gdb-tips/blob/master/src/index.md)
* [Debugging with GDB](https://sourceware.org/gdb/onlinedocs/gdb/)

-----

## 在Ubuntu中安装GDB

```shell
$ sudo apt install gdb
```

## 启动GDB

只需在命令行输入`gdb`即可启动`GDB`。

```shell
$ gdb

# run result
GNU gdb (Ubuntu 8.1-0ubuntu3.1) 8.1.0.20180409-git
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word".
(gdb)
```

### 启动GDB不显示提示信息

```shell
$ gdb -q
(gdb)
```

另外一种方法是修改文件 `~/.bashrc`,

```shell
$ sudo vim ~/.bashrc

# add a new line at the end of the file
alias gdb="gdb -q"

$ source ~/.bashrc
```

## 退出 GDB

退出`gdb`可以输入命令`quit`或`q`，或者使用快捷键`Ctrl + d`，注意`Ctrl + C`不会退出`gdb`，它只是取消目前正在进行的任务。

### 退出`gdb`时不显示提示信息

`gdb`在退出的时候会提示：

```
A debugging session is active.

    Inferior 1 [process 29686    ] will be killed.

Quit anyway? (y or n) n
```

可以在`gdb`里通过命令把提示信息关掉：

```
(gdb) set confirm off
```

## 检查GDB版本信息

```shell
(gdb) show version

# run result
GNU gdb (Ubuntu 8.1-0ubuntu3.1) 8.1.0.20180409-git
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word".
```

## 列出函数名

比如我们写了下面这样一个函数在`main.c`文件内：

```c
#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int multiply(int a, int b)
{
    return a * b;
}

int main()
{
    int a = 3, b = 4;
    printf("%d\n", add(a, b));
    printf("%d\n", multiply(a, b));
    
    return 0;
}
```

可以使用命令`info functions`打印可执行文件的所有函数名称

```bash
$ gcc -g main.c -o main
$ gdb main
Reading symbols from main...done.
(gdb) info functions
All defined functions:

File main.c:
int add(int, int);
int main();
int multiply(int, int);

Non-debugging symbols:
0x00000000000004f0  _init
0x0000000000000520  printf@plt
0x0000000000000530  __cxa_finalize@plt
0x0000000000000540  _start
0x0000000000000570  deregister_tm_clones
0x00000000000005b0  register_tm_clones
0x0000000000000600  __do_global_dtors_aux
0x0000000000000640  frame_dummy
0x00000000000006e0  __libc_csu_init
0x0000000000000750  __libc_csu_fini
0x0000000000000754  _fini
```

另外`gdb`还支持正则表达式`info functions regex`，比如这个例子

```bash
(gdb) info functions mu*
All functions matching regular expression "mu*":

File main.c:
int main();
int multiply(int, int);

Non-debugging symbols:
0x0000000000000570  deregister_tm_clones
0x00000000000005b0  register_tm_clones
0x0000000000000640  frame_dummy
```

函数名里面出现了`main`函数名，是因为我们在`main`函数里面调用了函数`multiply`。



