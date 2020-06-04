> # 《STL 源码解析》



# 第6章 算法（Algorithm）

## 6.4 基本用法

### 6.4.2 iter_swap

```c++
template <class Iterator>
inline typename iterator_traits<Iterator>::value_type *
value_type(const Iterator &)
{
    return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

template <class ForwardIteratorl, class ForwardIterator2>
inline void my_iter_swap(ForwardIteratorl a, ForwardIterator2 b)
{
    typename iterator_traits<ForwardIteratorl>::value_type tmp = *a;
    *a = *b;
    *b = tmp;
}
```

在`Cpp Reference`里的写法是：

```c++
template<class ForwardIt1, class ForwardIt2>
constexpr void iter_swap(ForwardIt1 a, ForwardIt2 b) // C++20 起为 constexpr
{
   using std::swap;
   swap(*a, *b);
}
```

应用实例

```c++ 
#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
 
template<class ForwardIt>
void selection_sort(ForwardIt begin, ForwardIt end)
{
    for (ForwardIt i = begin; i != end; ++i)
        std::iter_swap(i, std::min_element(i, end));
}
 
int main()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-11, 11);
    std::vector<int> v;
    generate_n(back_inserter(v), 20, bind(dist, gen));
 
    std::cout << "Before sort: ";
    for(auto e : v) std::cout << e << " ";
 
    selection_sort(v.begin(), v.end());
 
    std::cout << "\nAfter sort: ";
    for(auto e : v) std::cout << e << " ";
    std::cout << '\n';
}
```

```shell
# run result
Before sort: 1 -4 -10 11 10 5 -5 0 -9 4 -6 3 5 -4 -2 -7 0 9 6 -6 
After sort: -10 -9 -7 -6 -6 -5 -4 -4 -2 0 0 1 3 4 5 5 6 9 10 11 
```

这里值得一提的是在`Cpp Reference`里实现要比书中的实现更简洁一些，并未采用双层架构。





## 6.7 其他算法

### 6.7.1 reverse

书中仍是一如既往的采用双层架构，在`Cpp Reference`里有更简洁的写法：

```c++
template<class BidirIt>
void reverse(BidirIt first, BidirIt last)
{
    while ((first != last) && (first != --last)) {
        std::iter_swap(first++, last);
    }
}
```

应用实例

```c++
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>
 
int main()
{
    std::vector<int> v{1,2,3};
    std::reverse(std::begin(v), std::end(v));
    for(auto e : v) std::cout << e;
    std::cout << '\n';
 
    int a[] = {4, 5, 6, 7};
    std::reverse(std::begin(a), std::end(a));
    for(auto e : a) std::cout << e;
}
```

```shell
# run result
321
7654
```







### 6.7.5 next_permutation

书中的程序是版本一，版本二和版本一的区别在于：版本一决定排列组合顺序是通过less-than(<)操作符，版本二是通过仿函数comp来决定。

算法描述：首先，从最尾端开始往前寻找两个相邻元素，令第一元素为`*i`，第二元素为`*ii`，且满足`*i<*ii`。找到这样一组相邻元素后，再从最尾端开始往前检验，找出第一个大于`*i`的元素，令为`*j`，将`i，j`元素对调，再将`ii`之后的所有元素颠倒排列。此即所求之“下一个”排列组合。

上述更多的是对算法过程的描述，我们应该证明此算法的正确性。一下通过一个简单例子来进行一个不太严密的证明，旨在说明此思路：

考虑一个数12354，它的下一个全排列。下一个全排列应该是和12354最高位重合的越多越好，那么从最高位开始搜索显然不合理，所以应该从尾端开始搜索。

1. 考虑数字4，前面四个数字固定，那么没有下一个排列
2. 考虑数字54，前三个数字固定，也没有下一个排列
3. 考虑数字354，前两个数字固定，肯定存在下一个排列，如12435，12543等

从中可以发现规律，从尾端开始搜索，如果搜索的序列是降序的，就不会存在下一个排列，需要继续搜索，所以搜索停止只有两种可能：搜索到最前面，搜索到一个升序的数对。

找到这个数对以后，此数对前面的数字应该是固定不动的，此例子中就是12不动，354排列组合。这个数对中不符合降序规律的数字肯定排在最前面，也就是最高位，那么很自然考虑的一种选择是找除了它以外的比她大的数字中最小的一个来代替，也就是在54中寻找比3大的最小的数字，此例子就是4，然后交换，就成为了453。此时4就不应该再变动了，但是还没有结束，因为很明显，交换之后，即最高位后面的序列是降序的，显然它的逆序是全排列里最小的，所以应排为435，最终结果就是12435。

```c++
template<class BidirIt>
bool next_permutation(BidirIt first, BidirIt last)
{
    if (first == last) return false; //空区间
    BidirIt i = first;
    ++i;
    if (i == last) return false; //只有一个元素
    i = last;
    --i;
 
    for ( ; ; ){
        //锁定两个相邻元素
        BidirIt ii = i;
        --i;

        if (*i < *ii){ //找到前一个元素小于后一个元素
            BidirIt j = last; //从尾端开始寻找第一个大于*i的位置
            while (!(*i < *--j));
            iter_swap(i, j); //交换i，j
            reverse(ii, last); //将ii及以后的元素全部逆序排列

            return true;
        }

        if (i == first){ //i搜寻到最前面，即整个序列为降序
            reverse(first, last); //全部逆向
            return false;
        }
    }
}
```

一个简单的应用例子：

```c++
#include <algorithm>
#include <string>
#include <iostream>
 
int main()
{
    std::string s = "aba";
    std::sort(s.begin(), s.end());
    do {
        std::cout << s << '\n';
    } while(std::next_permutation(s.begin(), s.end()));
}
```

```shell
# run result
aab
aba
baa
```

