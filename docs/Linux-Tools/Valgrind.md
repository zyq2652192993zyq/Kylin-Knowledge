> # Valgrind

参考资料：

* valgrind官网文档：<http://valgrind.org/docs/manual/QuickStart.html>
* <https://blog.csdn.net/wzzfeitian/article/details/8567030>
* https://zhuanlan.zhihu.com/p/107120029?utm_source=wechat_session&utm_medium=social&utm_oi=725106525000974336

# 安装valgrind

```bash
$ sudo apt-get install valgrind
```

# 使用valgrind

最典型的例子莫过于写一个简单的链表：

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{	
	int data;
	struct Node * next;
}  Node;

Node *head = NULL;

//每次插入在链表的首部
void add(int num)
{
	Node *t = malloc(sizeof(Node));
	t -> data = num;
	t -> next = head;
	head = t;
}

void printList(Node *root)
{
	Node *t = root;
	while (t) {
		printf("%d ", t -> data);
		t = t -> next;
	}
	printf("\n");
}

int main()
{
	for (int i = 1; i < 11; ++i) {
		add(i);
	}
	printList(head);

	return 0;
}
```

注意到我们使用`malloc`动态分配了内存空间，但是却没有收回。如果用`gcc`编译发现是可以正常运行：

```bash
$ gcc -Werror -Wall -Wextra -O2 -std=c99 link.c -g -o link
$ ./link
10 9 8 7 6 5 4 3 2 1
```

但是没有报错信息并不意味着我们写的程序没有问题，很显然上面的程序存在内存泄漏。那这时候就需要用valgrind来进行检查。

valgrind的指令是：

```bash
$ valgrind --tool=memcheck --leak-check=full ./link
==261== Memcheck, a memory error detector
==261== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==261== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==261== Command: ./link
==261==
==261== error calling PR_SET_PTRACER, vgdb might block
10 9 8 7 6 5 4 3 2 1
==261==
==261== HEAP SUMMARY:
==261==     in use at exit: 160 bytes in 10 blocks
==261==   total heap usage: 11 allocs, 1 frees, 1,184 bytes allocated
==261==
==261== LEAK SUMMARY:
==261==    definitely lost: 0 bytes in 0 blocks
==261==    indirectly lost: 0 bytes in 0 blocks
==261==      possibly lost: 0 bytes in 0 blocks
==261==    still reachable: 160 bytes in 10 blocks
==261==         suppressed: 0 bytes in 0 blocks
==261== Reachable blocks (those to which a pointer was found) are not shown.
==261== To see them, rerun with: --leak-check=full --show-leak-kinds=all
==261==
==261== For counts of detected and suppressed errors, rerun with: -v
==261== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

写的程序一共分配了10个节点，在结果里面有一句：

```
==261==     in use at exit: 160 bytes in 10 blocks
==261==   total heap usage: 11 allocs, 1 frees, 1,184 bytes allocated
```

代表程序结束后仍然存在于10`blocks`里，有10个`allocs`没有被`free`。

于是修改程序：

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{	
	int data;
	struct Node * next;
}  Node;

Node *head = NULL;

//每次插入在链表的首部
void add(int num)
{
	Node *t = malloc(sizeof(Node));
	t -> data = num;
	t -> next = head;
	head = t;
}

void printList(Node *root)
{
	Node *t = root;
	while (t) {
		printf("%d ", t -> data);
		t = t -> next;
	}
	printf("\n");
}

void makeEmpty()
{
	while (head) {
		Node *tmp = head;
		head = head -> next;
		free(tmp);
		tmp = NULL;
	}
}

int main()
{
	for (int i = 1; i < 11; ++i) {
		add(i);
	}
	printList(head);
	makeEmpty();

	return 0;
}
```

然后再次运行valgrind检查：

```bash
$ gcc -Werror -Wall -Wextra -O2 -std=c99 link.c -g -o link
$ ./link
10 9 8 7 6 5 4 3 2 1
$ valgrind --tool=memcheck --leak-check=full ./link
==223== Memcheck, a memory error detector                                 
==223== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.   
==223== Using Valgrind-3.13.0 and LibVEX; rerun with -h for copyright info
==223== Command: ./link                                                   
==223==                                                                   
==223== error calling PR_SET_PTRACER, vgdb might block                    
10 9 8 7 6 5 4 3 2 1                                                      
==223==                                                                   
==223== HEAP SUMMARY:                                                     
==223==     in use at exit: 0 bytes in 0 blocks                           
==223==   total heap usage: 11 allocs, 11 frees, 1,184 bytes allocated    
==223==                                                                   
==223== All heap blocks were freed -- no leaks are possible               
==223==                                                                   
==223== For counts of detected and suppressed errors, rerun with: -v      
==223== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)    
```

加上`makeEmpty()`函数后检查发现`11 allocs, 11 frees`，不存在内存泄漏了。

```
==223==     in use at exit: 0 bytes in 0 blocks                           
==223==   total heap usage: 11 allocs, 11 frees, 1,184 bytes allocated    
```

