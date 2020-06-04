> # C或C++常见编译选项

参考资料：

* 《CSAPP》课程的`c_boot_camp`文件
* [GCC/G++编译参数含义](https://blog.csdn.net/yasi_xi/article/details/18551745)

```
-g:produce debug information(important;used by GDB/valgrind)
-Werror:treat all warnings as errors(this is our default)
-Wall/-Wextra:enable all construction warnings
-pedantic:indicate all mandatory diagnostics listed in C-standard
-O0/-O1/-O2:optimization levels
-o<filename>:name output binary file filename
```

**一、gcc 编译流程**

1. 预处理-Pre-Processing

```bash
$ gcc -E test.c -o test.i    # .i文件
```

2. 编译-Compiling

```bash
$ gcc -S test.i -o test.s  #.s文件 
```

3. 汇编-Assembling        

```bash
$ gcc -c test.s -o test.o  #.o文件
```

4.链接-Linking           

```bash
$ gcc test.o -o test #可执行文件
```

**-O选项**

-O 选项告诉 GCC 对源代码进行基本优化。这些优化在大多数情况下都会使程序执行的更快。 -O2 选项告诉

GCC 产生尽可能小和尽可能快的代码。 如-O2，-O3，-On（n 常为0--3）；

-O  主要进行跳转和延迟退栈两种优化；

-O0 表示不做优化

-O1 为默认优化

-O2 除了完成-O1的优化之外，还进行一些额外的调整工作，如指令调整等。

-O3 则包括循环展开和其他一些与处理特性相关的优化工作。

选项将使编译的速度比使用 -O 时慢， 但通常产生的代码执行速度会更快。

**调试选项-g和-pg**

GCC 支持数种调试和剖析选项，常用到的是 -g 和 -pg 。

-g 选项告诉 GCC 产生能被 GNU 调试器使用的调试信息以便调试你的程序**。**GCC 提供了一个很多其他 C 编译器里没有的特性, 在 GCC 里你能使-g 和 -O(产生优化代码)联用。

-pg 选项告诉 GCC 在编译好的程序里加入额外的代码。运行程序时, 产生 gprof 用的剖析信息以显示你的程序的耗时情况。

**-l参数和-L参数**

-l参数就是用来指定程序要链接的库，-l参数紧接着就是库名

