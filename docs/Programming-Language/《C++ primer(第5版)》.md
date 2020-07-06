> # 《C++ primer(第5版)》

## 第二章 变量和基本类型

### 2.1 基本内置类型

C++定义了包括**算术类型**（arithmetic  type）和**空类型**（void）。其中算术类型包括字符、整型数、布尔值和浮点数。空类型不对应具体的值。

#### 2.1.1 算术类型

算术类型分为两类：**整型**（integer type，包括字符和布尔类型在内）和**浮点型**。

| 类型        | 含义           | 最小尺寸     |
| ----------- | -------------- | ------------ |
| bool        | 布尔类型       | 未定义       |
| char        | 字符           | 8位          |
| wchar_t     | 宽字符         | 16位         |
| char16_t    | Unicode字符    | 16位         |
| char32_t    | Unicode字符    | 32位         |
| short       | 短整型         | 16位         |
| int         | 整型           | 16位         |
| long        | 长整型         | 32位         |
| long        | 长整型         | 64位         |
| float       | 单精度浮点型   | 6位有效数字  |
| double      | 双精度浮点型   | 10位有效数字 |
| long double | 扩展精度浮点型 | 10位有效数字 |

一个`char`的大小和一个机器字节一样。

计算内存的基本单元是位（ bit ）。字节（ byte ）通常指的是 8 位的内存单元。

#### 2.1.2 类型转换

当赋给无符号类型一个超出它表示范围的值时，结果时初始值对无符号类型表示数值总数取模后的余数。

切勿混用带符号类型和无符号类型，因为带符号数会自动转成无符号数。比如这个例子：

```c++
#include <iostream>

using namespace std;

int main()
{
    int a = -1;
    unsigned int b = 1;
    
    cout << a * b << endl;
        
    return 0;
}
```

```shell
# run result
4294967295
```

#### 2.1.3 字面值常量

**整型和浮点型字面值常量**

默认的浮点型字面值是一个`double`

**字符和字符串字面值**

```c++
'a' //char型字面值或字符型字面值
"Hello World!" //字符串字面值
```

字符串字面值的类型实际上是由常量字符构成的数组。

**布尔字面值和指针字面值**

`true`和`false`是布尔类型的字面值

`nullptr`是指针字面值。



### 2.2 变量

#### 2.2.1 变量定义

**对象**（object）是指一块能存储数据并具有某种类型的内存空间。

初始化不是赋值，初始化的含义是创建变量时赋予一个初始值，赋值的含义是把当前对象的当前值擦除，而以一个新值来代替。

C++11新标准用花括号来初始化变量，这种初始化的形式称为**列表初始化**（list initialization）。

如果定义时没有指定初始值，则变量被**默认初始化**（default initialized）。定义在函数体内部的内置类型变量将不被初始化。

#### 2.2.2 变量声明和定义的关系

变量声明规定了变量的类型和名字，定义除此之外还申请存储空间，也可能为变量赋予一个初始值。

```c++
extern int i; //声明
int j; //声明并定义
extern int k = 3; //任何包含显示初始化的声明即成为定义
```

#### 2.2.4 名字的作用域

作用域中一旦声明了某个名字，嵌套的所有作用域都能访问改名字。允许在内层作用域中重新定义外层作用域已有的名字。

```c++
int i = 42;
int main()
{
    int i = 100;
    int j = i;
}
/*
j的值是100，内层作用域重新定义了外层的i
*/
```

```c++
int i = 100, sum = 0;
for (int i = 0; i != 10; ++i)
    sum += i;
cout << i << " " << sum << endl;
//输出i=100， sum = 45，内层计算sum时候重新定义了i。
```



### 2.3 复合类型

#### 2.3.1 引用

**引用（reference）**：

* 引用必须被初始化，如`int &d`是错误的；
* 引用即别名：引用并非对象，它只是为一个已经存在的对象所起的另外一个名字，所以不能定义引用的引用。
* ==除了两种例外情况==，其他所有引用的类型都要和与之绑定的对象严格匹配。而且，引用只能绑定在对象上，而不能与字面值或某个表达式的计算结果绑定在一起。

```c++
double r = 3.14; int &p = r; //错误，引用类型要和绑定的对象匹配
int &p = 3; //错误，引用不能与字面值绑定
```

==两种例外==：

1. 初始化常量引用时允许用任意表达式作为初始值。

```c++
int i = 42;
const int &r1 = i; //正确
const int &r2 = 42; //正确
const int &r3 = r1 * 2; //正确
int &r4 = r1 * 2; //错误，普通引用不能绑定表达式的计算结果
```

2. 将基类的指针或引用绑定到派生类对象上。（15.2.3 类型转换与继承）

#### 2.3.2 指针

**指针（pointer）**：

指针与引用相比有很多不同点。其一，**指针本身就是一个对象**，允许对指针赋值和拷贝，而且在指针的生命周期内它可以先后指向几个不同的对象。其二，**指针无须在定义时赋初值**。和其他内置类型一样，在块作用域内定义的指针如果没有被初始化，也将拥有一个不确定的值。

指针存放某个对象的地址，要想获取该地址，需要使用**取地址符**（操作符`&`）：

```c++
int i = 42; int *p = &i; //p存放变量i的地址
```

==除了2.4.2节和15.2.3节将要介绍的两种例外情况==，其他所有指针的类型都要和它所指向的对象严格匹配。

如果指针指向了一个对象，则允许使用**解引用符**（操作符*）来访问该对象。

**两种例外的情形：**

(2.4.2节)指向常量的指针，和**常量引用**一样，没有规定所指对象必须是一个常量。



**空指针（null pointer）**不指向任何对象，得到空指针最直接的办法是用字面值`nullptr`来初始化指针，过去还会用一个名为`NULL`的**预处理变量（preprocessor variable）**来给指针赋值，c++11新标准下最好使用`nullptr`。

```c++
int *p1 = nullptr; //等价于int *p1 = 0;此种推荐使用
int *p2 = 0;
int *p3 = NULL; //等价于int *p3 = 0;
```

赋值永远改变等号左侧的对象：

```c++
int i = 42;
int *p = &i;
*p = 10; //ide值改变，但是p指针没有改变
```

这里两个指针存放的地址值相同（两个指针相等）有三种可能：

1. 它们都为空
2. 都指向同一个对象
3. 或者都指向了同一个对象的下一地址。

<u>需要注意的是，一个指针指向某对象，同时另一个指针指向另外对象的下一地址，此时也有可能出现这两个指针值相同的情况，即指针相等。</u>例子如下：

```c++
#include <iostream>
#include <iterator>
using namespace std;

int a[] = { 1,2 };
int i = 4;

int main()
{

    int *p = end(a);
    if (p == &i) cout << "equ" << endl;

    return 0;
}
```

解析：`end()`函数返回一个迭代器，指向最后一个元素的下一个位置。都为数组`a`和变量`i`都为整型数，内存连续，那么`i`的起始地址应是数组a最后一个元素的下一位置，所以相等。

**void***是一种特殊的指针类型，可用于存放任意对象的地址。不能直接操作**void*****指针**所指的对象，因为我们并不知道这个对象的类型是什么。

**指向指针的指针**

```c++
int i = 1024;
int *p = &i;
int *p1 = &p;
```

**对指针的引用**

引用本身不是对象，因此不能定义指向引用的指针。但是指针是对象，所以存在对指针的引用。

指针是一个对象，可以对指针引用：

```c++
int i = 42;
int *p;
int *&r = p; //r相当于指针p的别名
r = &i; //r是指针p的别名，这样定义没问题
*r = 1; //改变了i的值
```

理解r的类型从右往左理解：变量名是r，离得最近的是`&`，所以是一个引用，然后是`*`，说明是对指针的引用，最后是`int`，说明是对整型指针的引用。



### 2.4`const`限定符

`const`对象必须初始化，因为编译器在编译过程中会把用到`const`变量的地方都替换掉。如果利用一个对象去初始化另一个对象，它们是不是`const`都无关紧要。

**`const`的引用**

可以把引用绑定到`const`对象上，如下例：

```c++
const int i = 42;
const int &r = i; //正确操作，引用及其对象都是常量
int &m = i; //错误，非常量引用绑定了常量对象
```

#### 2.4.2 指针和`const`

指向常量的指针（pointer to const）：

```c++
const double pi = 3.14;
const double *p = &pi; //正确，指向常量的指针
```

注意一点，**常量指针或常指针（const pointer）**必须初始化，**指向常量的指针**可不必。如下例：

```c++
const int *p; //定义合法，但是指针p没有任何指向
int *const p; //定义非法，常量指针必须初始化
```

用名词**顶层` const`（top-level const）**表示指针本身是个常量，而用名词**底层`const`（low-level const）**表示指针所指的对象是一个常量。更一般的，顶层`const`可以表示任意的对象是常量，这一点对任何数据类型都适用，用于声明引用的`const`都是底层`const`。如`const int &r = i;`

###2.4.4 `constexpr`和常量表达式

**常量表达式（const expression）**是指值不会改变并且在编译过程就能得到计算结果的表达式。

```c++
const int v = 12; //v是常量表达式
const int l = v + 1; //l也是常量表达式
const int sz = get_size(); //不是常量表达式，因为只有程序运行时才能得到计算结果
```

C++11新标准规定，允许将变量声明为`constexpr`类型以便由编译器来验证变量的值是否是一个常量表达式。声明为`constexpr`的变量一定是一个常量，而且必须用常量表达式初始化：

```c++
constexpr int sz = get_size(); //get_size()为constexpr函数时候正确
```

算术类型，引用和指针都属于字面值类型。`constexpr`指针的初始值必须是`nullptr`或0，或者是存储与某个固定地址中的对象。定义于所有函数体之外的对象地址不变，可以用来初始化`constexpr`。

`constexpr`把所定义的对象置为了顶层`const`：

```c++
const int *p = nullptr; //p是一个指向整型常量的指针，顶层const
constexpr int *q = nullptr; //q是一个指向整型的常指针，底层const
```

根据`constexpr`指针的定义可知其可以指向常量也可以指向非常量。

### 2.5 处理类型

**类型别名**

类型别名是某种类型的同义词，传统方法是用`typedef`

```c++
typedef double wages; //wages是double的同义词
typedef wages base, *p; //base也是double的同义词，p是double*的同义词
```

C++11使用了**别名声明（alias declaration）**来定义类型别名：

```c++
using wages = double; //wages是double的同义词
```

`auto`**类型说明符**

C++11新标准引入了auto类型说明符，用它就能让编译器替我们去分析表达式所属的类型。和原来那些只对应一种特定类型的说明符（比如double）不同，auto让编译器通过初始值来推算变量的类型。显然，<u>auto定义的变量必须有初始值</u>。

`auto`一般会忽略顶层`const`，保留底层`const`：

```c++
const int ci=i，&cr=ci；
auto b = ci；//b是一个整数（ci的顶层const特性被忽略掉了）
auto c = cr；//c是一个整数（cr是ci的别名，ci本身是一个顶层const）
auto d = si；//d是一个整型指针（整数的地址就是指向整数的指针）
auto e = &ci；//e是一个指向整数常量的指针（对常量对象取地址是一种底层const）
```

如果希望推断出来的auto类型是顶层const需要明确指出：

```c++
const auto f = ci; //等价于const int f
```

`decltype`**类型指示符**

C++11新标准引入了第二种类型说明符decltype，它的作用是选择并返回操作数的数据类型。

```c++
int i = 42, *p = &i, &r = i;
const int ci = 1; &cj = ci;
int x = 0;

decltype(r) y = x; //这里推断出y的类型是int &,y绑定到x
decltype(cj) z = x; //这里z的类型是const int &, z绑定到x
decltype(r + 0) b; //r的类型可以与0相加，r是i的别名，所以结果是int，所以b的类型是int
```

特殊情况：变量名加上括号会被认为是一个表达式，会得到引用类型：

```c++
decltype((i)) d; //这种变量定义错误，d的类型是int &，需要初始化
decltype(i) d; //正确，d的类型是int
```

如果表达式的求值结果是左值，`decltype`作用于该表达式（不是变量）得到一个引用类型。举个例子，假定p的类型是`int`，因为解引用运算符生成左值，所以`decltype(*p）`的结果是`int &`。另一方面，因为取地址运算符生成右值，所以`decltype（&p）`的结果是`int**`，也就是说，结果是一个指向整型指针的指针。

`decltype`的一个很典型的应用是比如在优先级队列里面，对比较运算符进行重载，如LeetCode 23.合并K个有序链表：

```c++
//LeetCode 23 合并K个有序链表
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        std::ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);

        auto cmp = [](ListNode *l1, ListNode *l2){
            return l1 -> val > l2 -> val;
        };

        int n = lists.size();
        priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pq(cmp);

        for (auto & e : lists) 
            if (e) pq.push(e);

        ListNode *dummy = new ListNode(-1), *cur = dummy;
        while (!pq.empty()) {
            ListNode *tmp = pq.top(); pq.pop();
            cur -> next = tmp;
            cur = cur -> next;
            if (cur -> next) pq.push(cur -> next);
        }
        return dummy -> next;
    }
};
```

一种实现方式是对函数调用运算符进行重载

```c++
struct cmp {
    bool operator() (ListNode *l1, ListNode *l2)
    {
        return l1 -> val > l2 -> val;
    }
};

priority_queue<ListNode*, vector<ListNode*>, cmp> pq;
```

一篇很好的总结：https://www.cnblogs.com/wu-xiao-facebook/p/11606383.html

会发现结构体是提前给定的，无法修改了，所以可以利用`decltype` 来解决这个问题。

### 2.6 自定义数据结构

c++11新标准规定，可以为类内数据成员提供一个类内初始值，或者放在花括号里面，或者放在等号右边，不可以用原括号。



## 第三章 字符串、向量和数组

### 3.2 标准库string

**直接初始化和拷贝初始化**

使用等号的初始化执行的是拷贝初始化，不使用等号的是直接初始化。

```c++
string s1 = "hiya"; //copy initialization
string s2("hiya"); //direct initialization
string s3(10, 'c'); //s3 = "cccccccccc"
```

`string :: size_type`**类型**

特点：

1. 无符号类型的值
2. 能存放下任何string对象的大小

c++11允许用`auto`和`decltype`来推断变量类型：

```c++
string line = "this is an example";
auto len = line.size(); //len的剋行是string :: size_type
```

**范围for语句**

```c++
string str = "some string";
for(auto c : str)
    cout << c << '\t';
for(auto &a : str) //改变字符串中的字符需要引用
    a = toupper(a);
```

**比较`string`对象：**

1. 如果两个string对象的长度不同，而且较短string对象的每个字符都与较长的string随想对应位置相同，则较短string小于较长的string
2. 如果两个string对象在某些位置上不一致，则比较结果是第一对相异字符比较多的结果。

**string对象和字面值的相加**

标准库允许把字符字面值和字符串字面值转换成string对象，但是要确保`+`两侧的运算对象至少有一个是string对象。

在读取，string对象会自动忽略开头的空白（空格、换行符、制表符等），从第一个真正的字符开始读起。



### 3.3 标准库vector

列表初始化`vector`对象，C++11新标准允许用花括号括起来的0个或多个初始元素值赋给`vector`对象。

```c++
vector<string> = {"a", "ah", "the"};
```

### 3.5 数组

#### 3.5.2 访问素组元素

数组下标被定义为`size_t`类型，是一种机器无关的无符号类型，足够大以便能表示在内存中任意对象的大小。在头文件`cstddef`中定义了`size_t`类型，是C标准库`stddef`的C++版本。

#### 3.5.3 指针和数组

```c++
int ia[] = {0,1,2,3};
auto ia2(ia); //ia2是一个指针
ia2 = 42; //错误
```

C++11新标准引入了`begin`和`end`函数，使用方法是把对象作为参数。

```c++
int ia[] = {0,1,2,3,4};
int *beg = begin(ia);
int *lats = end(ia);
```

尾后指针不能执行解引用和递增操作。

两个指针相减结果的类型是`ptrdiff_t`的标准库类型，定义在头文件`cstddef`中，是一种带符号类型的机器无关的数据类型。

两个空指针允许相减，结果为0。

#### 3.5.4 C风格字符串

<u>在C++程序中最好不要使用C风格字符串，因为C风格字符串不仅使用起来不太方便，而且极易引发程序漏洞。</u>

C语言标准看`string.h`提供了一组函数来操作C风格字符串，头文件`csting`是其C++版本。（其中p是C风格的字符串）

| 函数名            | 功能                                                       |
| ----------------- | ---------------------------------------------------------- |
| `strlen(p)`       | 返回p的长度                                                |
| `strcmp(p1, p2)`  | 比较p1和p2相等性，相等为0，p1>p2，返回正值，否则返回负值。 |
| `strcat(p1,  p2)` | 将p2附加到p1之后，返回p1                                   |
| `strcpy(p1, p2)`  | 将p2拷贝给p1，返回给p1                                     |

传入此类函数的指针必须是以空字符串为结尾的数组。

```c++
char ca[] = {'a','b','c'};
cout << strlen(ca) << endl; //错误，ca没有以空字符串结尾
```

比较标准库`string`类型，可以直接使用运算符号（因为已经做了运算符重载），但是C风格字符串使用运算符则比较的是指针，所以应该用`strcmp()`。

如果我们想连接两个标准库string类型，只需要：

```c++
string largeStr = s1 + " " + s2;
```

如果s1和s2是C风格的字符串，执行`s1+s2`将是指针相加，无意义也非法。

解决方案就是使用函数`strcat`和`strcpy`，另外还需要一个用于存放结果的数组，数组必须足够大以便容纳下结果字符串和末尾空字符串。

```c++
strcpy(largeStr, s1);
strcat(largeStr, " ");
strcat(largeStr, s2);
```

显然我们需要正确预估大小，并且如果其中一个字符串内容变化，就必须重新检查空间是否足够。如果程序里满是这种代码，将非常难以维护。

#### 3.5.5 与旧代码的接口

任何出现字符串字面值的地方都可以用以空字串结束的字符数组来替代。

* 允许用以空字符串结束的字符数组来初始化string对象或为string对象赋值
* string对象加法中允许使用以空字符串结束的字符数组作为其中一个运算对象，但是不能两个都是。

不能用string对象直接初始化指向字符的指针。

```c++
string s = "Hello";
char *str = s; //错误
const char *str = s.c_str(); //正确
```

不允许使用vector对象初始化数组，但是可以用数组初始化vector对象。

```c++
int arr[] = {0,1,2,3,4,5,6,7};
vector<int> ivec(begin(arr), end(arr)); //用arr全部元素初始化
vector<int> subVec(arr + 1, arr + 3); //部 分元素初始化
```

### 3.6 多维数组

多维数组的下标引用

```c++
ia[2][3] = {1,2,3,4,5,6};
int (&row)[3] = ia[1];
```





## 第四章 表达式



### 4.11 类型转换

两种类型可以相互转换，它们就是关联的。

如果类型转换自动执行，无需程序员介入，被称为**隐式转换**（implicit conversion）

以下情形编译器自动发生类型转换：

* 比`int`类型小的整型值首先提升为较大的运算对象的类型
* 在条件中，非布尔型转换称布尔型
* 初始化过程中，初始值转换称变量的类型，赋值语句中，右侧运算对象转换成左侧运算对象的类型。
* 算术或关系运算对象有多种类型，需要转成同一种类型。
* 函数调用也会发生类型转换。



#### 4.11.3 显式转换

四种强制类型转换：`static_cast`，`dynamic_cast`， `const_cast`，和`reinterpret_cast`。

`static_cast` :任何不包含底层`const`，都可以使用`static_cast`，如：

```c++
#include <iostream>

using namespace std;

int main()
{
    int i = 3, j = 6;
    double k = static_cast<double>(i) / j;
    
    cout << k << endl;
    
    return 0;
}
```

```shell
# run result
0.5
```

使用`static_cast`可以把较大的算术类型值赋给较小的类型值，告诉编译器我们知道存在精度损失并且并不在乎，编译时就不会出现警告了。

另外就是可以用`static_cast`找回存在于`void *`的指针：

```c++
void *p = &d; //任何非常量对象的地址都能存入void*
double *dp = static_cast<double*>(p);
```

找回后存入对象的地址的值是一样的。

`const_cast`只能改变运算对象的底层`const`

将常量对象转为非常量对象，称为去掉`const`性质。

```c++
#include <iostream>

using namespace std;

int main()
{
    char arr[] = "hello";
    const char *cp = arr;
    char *p = const_cast<char*>(cp);
    p[0] = 'b';
    for (int i = 0; i < 5; ++i)
        cout << arr[i];
    
    return 0;
}
```

```shell
# run result 
bello
```

`reinterpret_cast`几乎什么都可以转，但是存在问题：

```c++
int *p;
char *pc = reinterpret_cast<char*>(p);
```

上面这段程序语法上没错，但是`pc`所指的对象是一个`int`类型而不是字符。尽量不要使用。

C语言风格的强制类型转换：`(type) expr`，看起来功能强大，缺点是是转化不够明确，不能进行错误检查，容易出错。

## 第六章 函数

### 6.1 函数基础

函数定义包含以下部分：返回类型、函数名、0个或者多个参数、函数体。‘通过调用运算符来执行函数。

**函数形参列表**

定义一个不带形参的函数，常用方法是写一个空的形参列表。为了与C兼容，也可以使用关键字`void`表示函数没有形参。

```c++
int fact() {} //隐式定义空的形参列表
int fact(void) {} //显示定义空的形参列表
```

**函数返回类型**

特殊返回类型是void。不能返回数组类型或函数类型。

**自动对象**

只存在于执行期间的对象称为自动对象。形参是一种自动对象：函数开始时为形参申请存储空间。

**局部静态对象**

在局部变量之前加上关键字`static`，局部变量就成为一个局部静态变量。

内存中的位置：静态存储区
初始化：未经初始化的全局静态变量会执行值初始化，为0（自动对象的值是任意的，除非他
被显式初始化）；
作用域：作用域仍为局部作用域，当定义它的函数或者语句块结束的时候，作用域结束。但
是当局部静态变量离开作用域后，并没有销毁，而是仍然驻留在内存当中，只不过我们不能再对
它进行访问，直到该函数再次被调用，并且值不变；

典型程序：

```c++
#include <iostream>

using namespace std;

int call()
{
    static int cnt = 0;
    return ++cnt;
}

int main()
{
    for (int i = 0; i < 10; ++i){
        cout << call() << " ";
    }
    
    return 0;
}
```

```shell
# run result
1 2 3 4 5 6 7 8 9 10
```

**函数声明**

函数定义只能有一次，但是可以声明多次。

### 6.2 参数传递

#### 6.2.1 传值参数

**指针形参**

执行指针拷贝操作，拷贝的是指针的值。拷贝后，两个指针是不同的指针。

```c++
int n = 3, i = 4;
int *p = &n, *q = &i;
*p = 42; //n = 42, i = 4;
p = q; //n = 42, i = 4
```

#### 6.2.3 `const`形参和实参

```c++
const int ci = 42; //顶层const
int i = ci; //正确，拷贝忽略顶层const
ci = i; //错误，ci值不可改变
int * const p = &i;
*p = 0; //正确，p值不可改变，但是p指向的对象可以改变
p = &ci; //错误，因为p值不可改变。
int const * m = &ci; //错误，数据类型不匹配，左值是int*，右值是const int *
const int *m1 = &ci; //正确，指向常量的指针
const int * const m2 = &ci; //肯定正确
const int * const m3 = &i; //正确
```

#### 6.2.4 数组形参



#### 6.2.6 含可变形参的函数

C++11提供了两种主要方法：

* 通过`initializer_list`
* 通过可变参数模板（16.4节）

### 6.3 函数返回类型

return语句返回值类型必须与函数返回类型相同或者能隐式转换完成。

#### 6.3.3 返回数组指针

数组不能拷贝，所以函数不能返回数组。函数可以返回数组的指针或者引用。

```c++
typedef int arrT[10];
//等价于 using arrT = int[10];
arrT* func(int i); //func返回一个指向含有10个整数的数组指针
```

**声明一个返回数组指针的函数**

如果不使用类型别名，则声明一个返回数组指针的函数的形式比如是：

```c++
int (*func(int i))[10];
```

从函数内层来看，`func(int i)`表示函数名为`func`，参数是`int i`，因为前面有`*`，所以这个函数的返回值是指针。然后外层告诉我们这个指针指向的是一个长度为10的整型数组。

**使用尾置返回类型**

C++11新标准里可以简化`func`的声明，就是尾置返回类型（trailing return type），对于返回类型比较复杂的函数最有效，比如返回类型是数组的指针或数组的引用。

位置返回类型跟在形参列表后面以一个`->`符号开头，为了表示函数真正的返回类型跟在形参之后，我们在本应该出现返回类型地方放置一个`auto`：

```c++
#include <bits/stdc++.h>

using namespace std;

int odd[] = {1,3,5,7};
int even[] = {0,2,4,6};

auto func(int i) -> int (*)[4]
{
	return (i % 2) ? &odd : &even;
}


int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int (*p)[4] = func(3);
	for (int i = 0; i < 4; ++i) {
		cout << (*p)[i] << endl;
	}

	return 0;
}
```

**使用`decltype`**

如果我们直到函数返回的指针将指向哪个数组，就可以使用`decltype`

```c++
#include <bits/stdc++.h>

using namespace std;

int odd[] = {1,3,5,7};
int even[] = {0,2,4,6};

decltype(odd)* func(int i)
{
	return (i % 2) ? &odd : &even;
}


int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int (*p)[4] = func(4);
	for (int i = 0; i < 4; ++i) {
		cout << (*p)[i] << endl;
	}

	return 0;
}
```

注意`decltype`的结果是数组，所以还需要加一个`*`。

**6.3.3节练习**

练习6.36：编写一个函数的声明，使其返回数组的引用并且该数组包含10个string对象。不要使用尾置返回类型、decltype或者类型别名。

```c++
string (&func())[10];
```

练习6.37：为上一题的函数再写三个声明，一个使用类型别名，另一个使用尾置返回类型，最后一个使用decltype关键字。

```c++
using str = string[10];
str& func();
```

```c++
auto func() -> string(&)[10];
```

```c++
string name[10];
decltype(name)& func();
```

### 6.4 函数重载

**重载函数**：同一作用域内的几个函数名字相同，但形参列表不同。**不允许两个函数除了返回类型外其他所有要素都相同**。

顶层`const`不影响传入函数的对象。

```c++
record lookup(Phone);
record lookup(const Phone); //重复声明

record lookup(Phone *);
record lookup(Phone *const); //重复声明
```

如果形参是某种类型的指针或者引用，通过区分指向的对象是常量对象还是非常量对象可以实现函数重载，此时`const`是底层的。

```c++
record lookup(Account &);
record lookup(const Account &);

record lookup(Account *);
record lookup(const Account *);
```

### 6.5 特殊用途语言

#### 6.5.2 内联函数和`constexpr`函数

将函数指定为内联函数（inline），通常就是将它在每个调用展开，可以避免函数调用的开销。

constexpr函数指能用于常量表达式，**函数的返回类型及所有形参都得是字面值类型，函数体中必须有且只有一条`return`语句**。

```c++
constexpr int new_sz() { return 42; }
constexpr int foo = new_sz();
```

```c++
constexpr size_t scale(size_t cnt) { return new_sz() * cnt; }
int arr[scale(2)]; //正确，scale(2)是常量表达式
int i = 2;
int a[scale(i)]; //错误，scale(i)不是常量表达式
```

#### 6.5.3 调式帮助

`assert`是一种预处理宏（preprocessor macro），定义于`<cassert>`头文件。因为预处理名字由预处理器而非编译器管理，所以无需使用`using`声明或者`std::assert`。

```c++
__func__ //编译器定义的一个局部静态变量，用于存放函数名字
__FILE__ //存放文件名的字符串字面值
__LINE__ //存放当前行号的整型字面值
__DATE__ //存放文件编译日期的字符串字面值
```

```c++
#include <bits/stdc++.h>

using namespace std;

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	if (3 > 2) {
		cout << __FILE__ << ": " << "error at line " << __LINE__ << endl;
	}

	return 0;
}
```

### 6.7 函数指针

函数指针的定义

```
存储类型/数据类型 (*函数指针名)();
```

含义：函数指针指向的是程序代码存储区（函数的存储地址）

```c++
bool lengthCompare(const string & s1, const string & s2);
bool (*pf)(const string & s1, const string & s2);
pf = lengthCompare;
pf = &lengthCompare; //等价的声明
```

函数指针的使用：

```c++
bool b1 = pf("hello", "goodbye");
bool b2 = (*pf)("hello", "goodbye");
bool b3 = lengthCompare("hello", "goodbye");
```

函数指针要和函数匹配需要参数类型以及返回类型都相同，并不存在转换规则。

**重载函数的指针**

必须清晰的指定选用哪个函数。

```c++
void ff(int *);
void ff(unsigned int);

void (*pf)(unsigned int) = ff;
void (*pf1)(int) = ff; //没有任何一个函数形参列表于其匹配
double (*pf2)(int *) = ff; //返回类型不匹配
```

函数指针的典型用途是实现函数回调。通过函数指针调用的函数，例如将函数指针作为参数传递给一个函数，使得在处理相似事件的时候可以灵活的使用不同的方法。

调用者（主调函数）不需要关心谁是被调用者，需要直到存在一个具有特定原型和限制条件的被调用函数。

**函数指针举例**
编写一个计算函数compute，对两个整数进行各种计算。
有一个形参为指向具体算法函数的指针，根据不同的实参函数，用不同的算法进行计算。
编写三个函数：求两个整数的最大值、最小值、和。分别用这三个函数作为实参，测试compute函数。

```c++
#include <bits/stdc++.h>

using namespace std;

int myMax(int a, int b) { return a > b ? a : b; }

int myMin(int a, int b) { return a < b ? a : b; }

int mySum(int a, int b) { return a + b; }

int compute(int a, int b, int (*func)(int, int))
{
	return func(a, b);
}


int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << compute(2, 3, &myMax) << endl;
	cout << compute(2, 3, &myMin) << endl;
	cout << compute(2, 3, &mySum) << endl;

	return 0;
}
```





## 第七章 类

类的基本思想是**数据抽象（data abstraction）**和**封装（encapsulation）**，抽象依赖于接口和实现分离的编程技术。

默认情况下`this`的类型是指向类类型非常量的常量指针，书中的`this`类型是`Sales_data *const`，在函数的参数列表后面紧跟一个`const`，这样就可以通过`this`调用一个常量对象了。

如果在类的内部声明了常量成员函数，在类的外面也必须在函数的参数列表后面指定`const`属性。

### 7.1 定义抽象数据类型

#### 7.1.3 定义类相关的非成员函数

比如`read`，`print`等函数，虽然属于类接口的组成部分，但是实际上并不属于类本身，这部分往往和运算符重载结合。

```c++
istream &read(istream & is, Sales_data &item);
istream &operator>>(istream &is, Sales_data &item);
```

第一个函数是定义了一个非成员函数，就是一个普通函数，调用方法比如`read(cin, iterm)`，第二个是输入运算符重载，调用方法`cin >> item`。`print`函数同理。

#### 7.1.4 构造函数

每个类分别定义了它的对象被初始化的方式，类通过一个或几个特殊的成员函数来控制对象的初始化过程，这些函数叫做**构造函数（constructor）**。

构造函数不能被声明成`const`，可以在`const`对象的构造过程中向其写值。

类通过**默认构造函数（default constructor）**，无须任何参数。如果类没有显示的定义构造函数，编译器会隐式的定义一个默认构造函数，称为**合成的默认构造函数（synthesized default constructor）**，执行默认初始化。

不过合成默认构造函数只适合非常简单的类，一般的类必须定义自己的默认构造函数，原因是：

* 一旦定义了一些其他构造函数，除非再定义默认构造函数，否则类将没有默认构造函数。
* 如果类中内置类型默认初始化，它们的值是未定义的，很可能让用户使用到这些未定义的值。
* 类中包含其他类类型的成员，且该成员没有默认构造函数，编译器将无法初始化该成员。

在C++11新标准里，在参数列表后写上`= default`来要求编译器生成构造函数，如果出现在类内部，则默认构造函数是内联的，否则不是内联。

```c++
Sales_data() = default;
```

书中出现的构造函数：

```c++
Sales_data(const string &s): bookNo(s) {}
```

位于冒号和花括号之间的部分称为**构造函数初始值列表（constructor initialize list）**

### 7.2 访问控制与封装

使用**访问说明符（access specifiers）**加强类的封装性。

`class`和`struct`的唯一区别是默认访问权限不一样。

#### 7.2.1 友元

类可以允许其他类或函数访问非公有成员，方法就是让其成为**友元（friend）**。

友元声明只能出现在类定义的内部，友元不是类的成员函数，所以出现的位置不限，也不受区域访问控制级别的约束。

### 7.3 类的其他特性

#### 7.3.3 类类型

可以只声明类而不定义它，称为**前向声明（forward declaration）**。只有完成类的定义，编译器才知道存储数据成员需要的空间，所以类的成员类型不能是类自己，但是可以是指向自身类型的指针。

#### 7.3.4 友元再探

即使在类的内部定义了友元函数，也必须在外部提供相应的声明使得函数可见，即使用声明友元函数的类的成员调用该友元函数，也必须是被声明过的。

```c++
struct X
{
	friend void f() {}
	X() { f(); } //f()还没有被声明
	void g();
	void h();
};

void X::g() { return f(); } //f()还没有被声明
void f(); //声明f()
void X::h() { return f(); } //正确
```

### 7.4类的作用域

类中如果成员使用了外层作用域中某个名字，则类内不能重新定义该名字。

### 7.5 构造函数再探

成员初始化的顺序和构造函数初始值列表的顺序无关，而是和在类定义中的顺序有关。

#### 7.5.2 委托构造函数

C++11新标准可以使用**委托构造函数（delegating constructor）**。一个委托构造函数使用它所属的类的其他构造函数执行自己的初始化过程。

```c++
class Sales_data
{
public:
	//非委托构造函数
	Sales_data(string s, unsigned cnt, double price): 
		bookNo(s), units_sold(cnt), revenue(cnt * price) {}
	//委托构造函数
	Sales_data(): Sales_data("", 0, 0) {}
	Sales_data(string s): Sales_data(s, 0, 0) {}
	Sales_data(istream & is): Sales_data() { read(is, *this); }
};
```

#### 7.5.4 隐式类型转换

只允许一步类型转换。关键字`explicit`只对一个实参的构造函数有效，需要多个实参的构造函数不能用于执行隐式转换，只能在类内声明构造函数时使用`explicit`关键字，类的外部定义时不应重复。

`explicit`构造函数只能用于直接初始化，一种典型的情况是执行拷贝初始化（使用`=`），此时只可以使用直接初始化而不能使用`explicit`构造函数。



### 7.6 类的静态数据成员

需要类的静态数据成员的原因：比如银行系统中的每个账户，计算账户利息需要利率（共享信息），共享信息一般设置为全局变量，但是会缺乏对数据的保护：

1. 全局变量不受类的控制访问的限定（即没有隐藏），其他类和全局函数都能访问此数据
2. 容易造成名字冲突

所以类的静态数据成员，拥有一块单独的存储区，可以是public，也可以是private。类型可以是常量、引用、指针等。

因为静态数据成员不属于类的任何一个对象，所以它们并不是在类的对象创建时定义的。一般来说，我们不能在类的内部初始化静态成员。相反必须在类的外部定义和初始化每个静态数据成员。

但是我们可以为静态成员提供`const`整型的类内初始值，要求类的静态数据成员必须是字面值类型的`constexpr`，比如

```c++
class foo{
  private:
    static constexpr int size = 30;
    double daily[size];
};
```

如果在类的内部提供了一个初始值，则不能再指定初始值。

静态成员和非静态成员适用场景的区别：

1. 静态数据成员可以是不完全类型。静态数据成员类型可以是它所属的类类型，非静态数据成员则只能声明它所属的类的指针或引用。

```c++
class foo{
  private:
    static foo mem1;
    foo *mem2;
    foo mem3; //false
};
```

1. 静态数据成员可以作为默认实参

```c++
class screen{
  public:
  	screen & clear(char = bkground);  
  private:
    static const char bkground;
};
```



## 第九章 顺序容器

书中对`lsit`的介绍是比较少的，但是这个容器在写LRU和LFU的时候使用起来就会很方便，参考了[cpp reference](https://zh.cppreference.com/w/cpp/container/list)上的解释。

`list`支持常数时间从容器任何位置插入和移除元素的容器，不支持快速随机访问。实现为双向链表，`forward_list`是单向链表。

`list`的迭代器在添加、移除和移动元素不会非法化迭代器或引用，迭代器只有在对应元素被删除的时候才会失效。

成员函数:

```c++
operator= //重载了赋值运算符
```

元素访问：

```c++
front();  //访问第一个元素
back(); //访问最后一个元素
```

迭代器：

```c++
begin(); cbegin()
end(); cend();
rbegin(); rend(); 
crbegin(); crend(); //和其他容器的迭代器含义是一致的
```

容量：

```c++
empty(); size(); //和其他容器的函数意义一致
max_size(); //返回可容纳的最大元素数，较少使用
```

修改器：

```c++
clear();
insert();
push_back();
erase();
pop_back();
push_front();
pop_front();
```

```c++
// 移除位于pos的元素
iterator erase( iterator pos ); 
iterator erase( const_iterator pos ); //C++11
//移除[first, last)中的元素
iterator erase( iterator first, iterator last );
iterator erase( const_iterator first, const_iterator last ); //C++11
```

应用举例：

```c++
#include <list>
#include <iostream>
#include <iterator> /* advance */

using namespace std;
 
int main( )
{
    list<int> c{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (const auto &i : c) {
        cout << i << " ";
    }
    cout << endl;
 	//删除首部元素
    c.erase(c.begin());
    for (const auto &i : c) {
        cout << i << " ";
    }
    cout << endl;
  	//删除第一个到第3个元素
  	list<int>::iterator rangeBegin = c.begin();
  	list<int>::iterator rangeEnd = c.begin();
  	advance(rangeEnd, 3);

    c.erase(rangeBegin, rangeEnd);
    for (const auto &i : c) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}
```

```
0 1 2 3 4 5 6 7 8 9 
1 2 3 4 5 6 7 8 9 
4 5 6 7 8 9 
```

函数`sort()`和`merge`的应用：（注意`merge`是合并有序链表，所以先排序）

```c++
#include <iostream>
#include <list>
 
std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list)
{
    for (auto &i : list) {
        ostr << " " << i;
    }
    return ostr;
}
 
int main()
{
    std::list<int> list1 = { 5,9,0,1,3 };
    std::list<int> list2 = { 8,7,2,6,4 };
 
    list1.sort();
    list2.sort();
    std::cout << "list1:  " << list1 << "\n";
    std::cout << "list2:  " << list2 << "\n";
    list1.merge(list2);
    std::cout << "merged: " << list1 << "\n";
}
```

```
list1:   0 1 3 5 9
list2:   2 4 6 7 8
merged:  0 1 2 3 4 5 6 7 8 9
```

很重要的一个函数`splice`

```c++
//从 other 转移所有元素到 *this 中。元素被插入到 pos 所指向的元素之前。
void splice( const_iterator pos, list& other );
// 从 other 转移 it 所指向的元素到 *this 。元素被插入到 pos 所指向的元素之前。
void splice( const_iterator pos, list& other, const_iterator it );
//从 other 转移范围 [first, last) 中的元素到 *this 。
void splice( const_iterator pos, list& other,const_iterator first, const_iterator last);
```

```c++
#include <iostream>
#include <list>
 
std::ostream& operator<<(std::ostream& ostr, const std::list<int>& list)
{
    for (auto &i : list) {
        ostr << " " << i;
    }
    return ostr;
}
 
int main ()
{
    std::list<int> list1 = { 1, 2, 3, 4, 5 };
    std::list<int> list2 = { 10, 20, 30, 40, 50 };
 
    auto it = list1.begin();
    std::advance(it, 2);
 
    list1.splice(it, list2);
 
    std::cout << "list1: " << list1 << "\n";
    std::cout << "list2: " << list2 << "\n";
 
    list2.splice(list2.begin(), list1, it, list1.end());
 
    std::cout << "list1: " << list1 << "\n";
    std::cout << "list2: " << list2 << "\n";
}
```

```
list1:  1 2 10 20 30 40 50 3 4 5
list2: 
list1:  1 2 10 20 30 40 50
list2:  3 4 5
```









## 第十七章 标准库特殊设施



### 17.3 正则表达式

```c++
#include <iostream>
#include <regex>

using namespace std;

int main()
{
    string pattern = "[^c]ei";
    pattern = "[[:alpha:]]*" + pattern + "[[:alpha:]]*";
    smatch result;
    regex r(pattern);

    string test = "receipt freiend theif receieve";

    for (sregex_iterator it(test.begin(), test.end(), r), end_it;
        it != end_it; ++it)
        cout << it -> str() << endl;

    return 0;
}
```

```shell
# run result
freiend
theif
```



```c++
#include <iostream>
#include <regex>

using namespace std;

int main()
{
    string phone = "(\\()?(\\d{3})(\\))?([-. ])?(\\d{3})([-. ])?(\\d{4})";
    regex r(phone);
    smatch m;

    string fmt = "$2.$5.$7";
    string number = "(908) 555-1800";
    cout << regex_replace(number, r, fmt) << endl;

    return 0;
}
```

```shell
# run result
908.555.1800
```



## 第十九章 特殊工具与技术



### 19.2 运行时类型识别



#### 19.2.1 `dynamic_cast`运算符









## C++11新特性

* long long 类型

long long的最小尺寸至少和long一样大，最小尺寸为64位。

* 列表初始化

C++11新标准用花括号来初始化变量，这种初始化的形式称为**列表初始化**（list initialization）。

* 空指针

**空指针（null pointer）**不指向任何对象，得到空指针最直接的办法是用字面值`nullptr`来初始化指针，过去还会用一个名为`NULL`的**预处理变量（preprocessor variable）**来给指针赋值，c++11新标准下最好使用`nullptr`。

```c++
int *p1 = nullptr; //等价于int *p1 = 0;此种推荐使用
int *p2 = 0;
int *p3 = NULL; //等价于int *p3 = 0;
```

* `constexpr`变量

C++11新标准规定，允许将变量声明为`constexpr`类型以便由编译器来验证变量的值是否是一个常量表达式。声明为`constexpr`的变量一定是一个常量，而且必须用常量表达式初始化：

```c++
constexpr int sz = get_size(); //get_size()为constexpr函数时候正确
```

* 类型别名声明

C++11使用了**别名声明（alias declaration）**来定义类型别名：

```c++
using wages = double; //wages是double的同义词
```

* `auto`类型说明符

C++11新标准引入了auto类型说明符，用它就能让编译器替我们去分析表达式所属的类型。和原来那些只对应一种特定类型的说明符（比如double）不同，auto让编译器通过初始值来推算变量的类型。显然，<u>auto定义的变量必须有初始值</u>。

`auto`一般会忽略顶层`const`，保留底层`const`：

```c++
const int ci=i，&cr=ci；
auto b = ci；//b是一个整数（ci的顶层const特性被忽略掉了）
auto c = cr；//c是一个整数（cr是ci的别名，ci本身是一个顶层const）
auto d = si；//d是一个整型指针（整数的地址就是指向整数的指针）
auto e = &ci；//e是一个指向整数常量的指针（对常量对象取地址是一种底层const）
```

如果希望推断出来的auto类型是顶层const需要明确指出：

```c++
const auto f = ci; //等价于const int f
```

* `decltype`类型指示符

C++11新标准引入了第二种类型说明符decltype，它的作用是选择并返回操作数的数据类型。

```c++
int i = 42, *p = &i, &r = i;
const int ci = 1; &cj = ci;
int x = 0;

decltype(r) y = x; //这里推断出y的类型是int &,y绑定到x
decltype(cj) z = x; //这里z的类型是const int &, z绑定到x
decltype(r + 0) b; //r的类型可以与0相加，r是i的别名，所以结果是int，所以b的类型是int
```

特殊情况：变量名加上括号会被认为是一个表达式，会得到引用类型：

```c++
datatype((i)) d; //这种变量定义错误，d的类型是int &，需要初始化
decltype(i) d; //正确，d的类型是int
```

如果表达式的求值结果是左值，`decltype`作用于该表达式（不是变量）得到一个引用类型。举个例子，假定p的类型是`int`，因为解引用运算符生成左值，所以`decltype(*p）`的结果是`int &`。另一方面，因为取地址运算符生成右值，所以`decltype（&p）`的结果是`int**`，也就是说，结果是一个指向整型指针的指针。

* 范围for语句

```c++
string str = "some string";
for(auto c : str)
    cout << c << '\t';
for(auto &a : str) //改变字符串中的字符需要引用
    a = toupper(a);
```

