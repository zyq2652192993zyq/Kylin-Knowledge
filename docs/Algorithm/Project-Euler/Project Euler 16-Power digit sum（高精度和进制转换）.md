> # Project Euler 16-Power digit sum（高精度和进制转换）

Tags: `Easy`

Links: https://www.hackerrank.com/contests/projecteuler/challenges/euler016/problem

------

This problem is a programming version of [Problem 16](https://projecteuler.net/problem=16) from [projecteuler.net](https://projecteuler.net/)

$2^9 = 512$ and the sum of its digits is $5+1+2=8$

What is the sum of the digits of the number $2^N$ ?

**Input Format**

The first line contains an integer $T$, i.e., number of test cases.
Next $T$ lines will contain an integer $N$.

**Constraints**

* $1 \leq T \leq 100$
* $1 \leq N \leq 10^4$

**Output Format**

Print the values corresponding to each test case.

**Sample Input**

```
3
3
4
7
```

**Sample Output**

```
8
7
11
```

-----

这道题其实有很多种思路：

* 直接利用高精度计算出结果，中间过程利用快速幂加速
* 进制转换的方法，把结果$2^N$转成一个大的基数表示的数字

解法一：进制转换方法

我们将基数设为$10^5$，实际上相当于把数字的4位数字合并起来存入数组，通过计算，$2^{10^4}$转化后数组长度为603，对于每个测试用例，需要计算次数$10^4 \times 600$，不会超时。

```c++
#include <bits/stdc++.h>

using namespace std;

const int BASE = 100000;

vector<int> seq(100005, 0);

int solve(int n)
{
    fill(seq.begin(), seq.end(), 0);
    seq[0] = 1;
    int len = 0;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= len; ++j) {
            seq[j] <<= 1;
        }

        for (int j = 0; j <= len; ++j) {
            if (seq[j] >= BASE) {
                seq[j] %= BASE;
                ++seq[j + 1];
            }
        }
        if (seq[len + 1] > 0) ++len;
    }

    int sum = 0;
    for (int i = 0; i <= len; ++i) {
        for (int j = 10000; j >= 1; j /= 10) {
            sum += seq[i] / j;
            seq[i] %= j;
        }
    }

    return sum;
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        int n; cin >> n;
        cout << solve(n) << endl;
    }

    return 0;
}
```

