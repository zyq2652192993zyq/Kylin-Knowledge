> # Makefile

参考资料：

* [Unix Makefile 教程](https://lellansin.gitbooks.io/makefile/content/)
* 《跟我一起写makefile》

# 为什么需要makefile

手动编译源代码文件很麻烦，特别是当你要编译多个源文件，并切每次编译都要重复输入编译命令的时候。而 Makefile 正是为了简化这个过程的一个工具。

现在有一个名为`program.c`的文件：

```c
#include <stdio.h>

int main()
{
    printf("Hello world!\n");
}
```

按照以往，我们会在终端输入：

```bash
$ gcc program.c -o program
```

现在如果用makefile写，它的原则是：

```
target: dependency
	command
```

`target`是我们想得到的可执行文件，`dependency`是生成可执行文件所依赖的文件，`command`是编译命令。

```makefile
program: program.c
	gcc program.c -o program
```

```bash
$ make
gcc program.c -o program
```

于是在当前目录下生成了可执行文件`program`。

这是针对单个文件的编译。

# 多文件编译

现在考虑如果`program.c`依赖于很多的文件，比如有`max.c`实现查找最大值的函数，并在`main.c`中调用，那么我们按照上面的方法可以写成

```c
//program.c
#include <stdio.h>
#include "max.h"

int main()
{
	int arr[] = {1,2,3,4,5,6,7};
	int res = find_max(arr, 7);
	printf("%d\n", res);

	return 0;
}
```

```c
//max.h
#ifndef _max_h
#define _max_h

int find_max(int arr[], int n)；

#endif
```

```c
//max.c
#include "max.h"

int find_max(int arr[], int n)
{
	int res = arr[0];
	for (int i = 0; i < n; ++i) {
		if (arr[i] > res) res = arr[i];
	}

	return res;
}
```

```makefile
program: program.c max.c
	gcc program.c max.c -o program
```
但是如果每次都按照上面的方法编译，会存在两个问题：

* 如果依赖的文件很多，比如实现多个版本的`find_max`函数，在不同的文件里，那么这个命令将会很长。
* 每次都需要将源文件重新编译，会造成编译时间很长。

在《CSAPP》的第一章对编译过程有很详细的介绍：[GCC全过程详解+剖析生成的.o文件](https://blog.csdn.net/gt1025814447/article/details/80442673)

`GCC` 编译器将 `hello.c` 编译程 `hello` 可执行文件分为四个阶段完成，四个阶段执行的程序是**预处理器、编译器、汇编器和链接器**，这四个程序一起构成了**编译系统**。

![](F:\Project\Reading-Notes\Linux\assets/compile.png)

- 预处理器阶段：预处理器（cpp）根据以 `#` 开头的命令，修改原始的C程序，读取相应头文件的内容，直接插入到程序文本中，得到另一个C程序，以 `.i` 为文件扩展名。

```bash
$ gcc -E hello.c -o hello.i
# 第二种方法： cpp hello.c > hello.i     【cpp是预编译器】
```

如果不加 `-o hello.i` 则会 `.i` 文件的内容直接输出。所作的主要内容：

将所有 `#define` 删除，并且展开所有的宏定义

处理所有的条件预编译指令，如 `#if #ifdef #undef #ifndef #endif #elif`

处理 `#include`，将包含的文件插入到此处，这是一个递归的过程

删除所有注释 `// /* */`

添加行号和文件名标识，以便于编译时产生的错误警告能显示行号

保留 `#pragma` 编译器指令

- 编译阶段：编译器（ccl）将新得到的 `.i` 程序翻译成文本文件 `hello.s` ，包含汇编语言程序。文件内包含 `main` 函数的定义和其他语句，每一行语句描述了一条低级机器语言指令。汇编语言为不同语言的编译器提供了通用的输出语言，比如C编译器和Fortran编译器产生多额输出文件用的是同一样的汇编语言。

```bash
$ gcc -S  hello.i  -o  hello.s
```

将预处理完的`.i`文件进行一系列的词法分析、语法分析、语义分析及优化后生成响应的汇编代码文件，这是整个程序构建的最核心的部分，也是最复杂的部分。

- 汇编阶段：汇编器（as）将 `hello.s` 翻译成机器语言指令，打包成**可重定位目标程序（relocatable object program）**的格式，保存在 `.o` 为扩展名的文件。

```bash
gcc  -c  hello.s  -o  hello.o # 或者 as  hello.s -o  hello.o
```

汇编是将第二步生成的汇编代码编程机器可执行的指令，每一个汇编语句几乎都对应一条机器指令

- 链接阶段：程序调用了 `printf` 函数，预先有一个单独编译好的 `printf.o` 文件，链接器（ld）将两个文件合并成可执行文件 `hello` ，然后加载到内存由系统执行。

所以可以先将`max.c`编译成`.o`文件，最后通过链接器链接起来。

```makefile
program: program.c max.o
	gcc program.c max.o -o program

max.o: max.c
	gcc -c max.c
```

上面语句的意思是目标`program`依赖于`program.c`文件和`max.o`文件，而`max.o`文件依赖于`max.c`文件，其中`-c`的选项就是生成`.o`文件。

因为上面的编译过程中间生成了`.o`文件并不是我们需要的，所以需要在编译完成后删除掉

```makefile
program: program.c max.o
	gcc program.c max.o -o program

max.o: max.c
	gcc -c max.c
	
clean:
	rm *.o program
```

当想要生成可执行文件的时候输入`make`，如果想删除不需要的文件（`.o`），那么只需要输入`make clean`即可执行`clean`的部分。

现在如果多了一个查找最小值的函数`find_min()`，那么`Makefile`的写法变成：

```makefile
program: program.c max.o min.o
	gcc program.c max.o min.o -o program

max.o: max.c
	gcc -c max.c
	
min.o: min.c
	gcc -c min.c
	
clean:
	rm *.o program
```

# 宏

`make` 允许你使用类似变量的宏。宏在 Makefile 中使用 名称 = 值 的形式来定义。

考虑一种情况，刚才我们是用`gcc`来进行编译的，如果后面想换成`g++`，并且依赖的文件很多，那就需要将多处的`gcc`替换成`g++`，所以我们可以用变量来对其进行替换。

```makefile
CC = gcc

program: program.c max.o min.o
	$(CC) program.c max.o min.o -o program

max.o: max.c
	$(CC) -c max.c
	
min.o: min.c
	$(CC) -c min.c

clean:
	rm *.o program
```

这样如果换成`g++`，则只需要修改一行代码。比如想要在编译的时候加一些选项或者第三方库，也可以定义成变量的形式。

```makefile
CC = gcc
CFLAGS = -lm -Wall -Wextra -Werror -O2 -g

program: program.c max.o min.o
	$(CC) $(CFLAGS) program.c max.o min.o -o program

max.o: max.c
	$(CC) $(CFLAGS) -c max.c
	
min.o: min.c
	$(CC) $(CFLAGS) -c min.c

clean:
	rm *.o program
```

其中`-lm`是链接第三方的动态数学库。

考虑如果想生成两个可执行文件，比如生成`main_min`和`main_max`，如果知识单纯的写成下面这样：

```makefile
CC = gcc
CFLAGS = -lm -Wall -Wextra -Werror -O2 -g

main_min: main_min.c max.o min.o
	$(CC) $(CFLAGS) main_min.c max.o min.o -o main_min
	
main_max: main_max.c max.o min.o
	$(CC) $(CFLAGS) main_max.c max.o min.o -o main_max

max.o: max.c
	$(CC) $(CFLAGS) -c max.c
	
min.o: min.c
	$(CC) $(CFLAGS) -c min.c

clean:
	rm *.o main_min main_max
```

执行`make`发现之生成了`main_min`，这是因为编译器发现已经存在了可执行文件`main_min`，那么就会跳过生成`main_max`，解决的办法是采用`ALL`。

```makefile
CC = gcc
CFLAGS = -lm -Wall -Wextra -Werror -O2 -g

ALL: main_min main_max

main_min: main_min.c max.o min.o
	$(CC) $(CFLAGS) main_min.c max.o min.o -o main_min
	
main_max: main_max.c max.o min.o
	$(CC) $(CFLAGS) main_max.c max.o min.o -o main_max

max.o: max.c
	$(CC) $(CFLAGS) -c max.c
	
min.o: min.c
	$(CC) $(CFLAGS) -c min.c

clean:
	rm *.o main_min main_max
```

