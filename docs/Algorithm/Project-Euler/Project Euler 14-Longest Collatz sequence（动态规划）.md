> # Project Euler 14-Longest Collatz sequence（动态规划）

Tags: `Easy` 

Links: https://www.hackerrank.com/contests/projecteuler/challenges/euler014/problem

------

This problem is a programming version of [Problem 14](https://projecteuler.net/problem=14) from [projecteuler.net](https://projecteuler.net/)

The following iterative sequence is defined for the set of positive integers:
$$
n \rightarrow \frac{n}{2} \quad \text{n is even} \\
n \rightarrow 3n + 1 \quad \text{n is odd}
$$
Using the rule above and starting with 13, we generate the following sequence:
$$
13 \rightarrow 40 \rightarrow 20 \rightarrow 10 \rightarrow 5 \rightarrow 16 \rightarrow 8 \rightarrow 4 \rightarrow 2 \rightarrow 1
$$
It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

Which starting number, $\leq N$ produces the longest chain? If many possible such numbers are there print the maximum one.

**Note:** Once the chain starts the terms are allowed to go above $N$ .

**Input Format**

The first line contains an integer $T$ , i.e., number of test cases.
Next $T$ lines will contain an integers $N$.

**Constraints**

* $1 \leq T \leq 10^4$
* $1 \leq N \leq 5 \times 10^6$

**Output Format**

Print the values corresponding to each test case.

**Sample Input**

```
3
10 
15
20
```

**Sample Output**

```
9
9
19
```

**Explanation**

Collatz sequence for $n = 9$ is,
$$
9 \rightarrow 28 \rightarrow 14 \rightarrow 7 \rightarrow 22 \rightarrow 11 \rightarrow 34 \rightarrow 17 \rightarrow 52 \rightarrow 26 \rightarrow 13 \rightarrow 40 \rightarrow 20 \rightarrow 10 \rightarrow 5 \rightarrow 16 \rightarrow 8 \rightarrow 4 \rightarrow 2 \rightarrow 1
$$
containing $19$ steps and is the longest for $n \leq 10$.

-----

最直接的想法是对从1到`n`的数字进行暴力计算，算出最大值，但是这样会存在很多重复计算，就以题目中的例子为例，假如我计算数字7，当我计算9的时候又计算了一次7，实际上我们可以用一个数组存储7的计算结果，当计算9的时候，中间步骤出现了7，那么直接就可以得到结果。

另外本题是算出小于等于`n`的数字中，那个数字的链的长度最长，我们用数组`seq[i]`存储数字`i`的链的长度，初始化为`-1`表示当前数字还没有进行计算，用数组`maxNum[i]`存储数字小于等于`i`的数字中最大链的长度，用`maxVal[i]`表示小于等于`i`的数字中，在哪一个数字取到最大链长。

注意到题目给的多组数据达到$10^4$，我们可以预处理从1到$5 \times 10^6$ 的所有数字，预先计算出结果，这样对每个测试用例都是$O(1)$出结果.

```c++
#include <bits/stdc++.h>

using namespace std;

int n;
vector<int> seq(5e6 + 5, -1), maxNum(5e6 + 5), maxVal(5e6 + 5);
const int limit = 5000000;

void countTerm(long long num)
{
    long long tmp = num;

    int cnt = 1;
    while (num != 1) {
        if (num & 1) { num = 3 * num + 1; ++cnt; }
        else {
            num >>= 1;
            if (num <= limit && seq[num] > 0) { cnt += seq[num]; break; }
            else ++cnt;
        }
    }

    seq[tmp] = cnt;
    if (seq[tmp] >= maxNum[tmp - 1]) {
        maxNum[tmp] = seq[tmp];
        maxVal[tmp] = tmp;
    }
    else {
        maxNum[tmp] = maxNum[tmp - 1];
        maxVal[tmp] = maxVal[tmp - 1];
    }
}

inline int solve()
{
    return maxVal[n];
}

void init()
{
    seq[1] = 1;
    maxNum[1] = 1;
    maxVal[1] = 1;
    for (int i = 2; i <= 5000000; ++i) {
        countTerm(i);
    }
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    init();

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        cin >> n;
        cout << solve() << endl;
    }

    return 0;
}
```



