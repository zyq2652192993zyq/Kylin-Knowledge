> # Project Euler #3: Largest prime factor

Tags: `Medium`

Links: https://www.hackerrank.com/contests/projecteuler/challenges/euler003/problem

-----

This problem is a programming version of [Problem 3](https://projecteuler.net/problem=3) from [projecteuler.net](https://projecteuler.net/)

The prime factors of $13195$ are $5, 7, 13$ and $29$.

What is the largest prime factor of a given number $N$?

**Input Format**

First line contains $T$ the number of test cases. This is followed by $T$ lines each containing an integer .

**Constraints**

- $1 \leq T \leq 10$
- $10 \leq N \leq 10^{12}$

**Output Format**

For each test case, display the largest prime factor of .

**Sample Input 0**

```
2
10
17
```

**Sample Output 0**

```
5
17
```

**Explanation 0**

- Prime factors of $ 10 $ are $\{2, 5 \}$, largest is $5$.
- Prime factor of $17$ is $17$ itself, hence largest is $17$.

------

这道题如果算法不经过优化，会在最后一个测试用例超时。数据范围在$10^{12}$，算法需要是$\log n$或者$\sqrt n$级别的，类似于判断一个数是否是质数的方法：

* 首先如果这个数是偶数的化，一直除以2，如果最后$n == 1$，那么最大质因子一定是2
* 接下来从3开始计算，每次增加2，因为最大因子不会超过$\sqrt n$，所以只需要对$[3, \sqrt n]$范围内的数进行枚举，更新最大质因数
* 如果枚举范围内都不存在因子，说明数字本身就是质数，直接返回即可。

时间复杂度$O(\max(\log n, \sqrt n))$，空间复杂度$O(1)$.

```c++
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;


long long maxFactor(long long n)
{
    long long res = 2;
    while (!(n & 1)) n >>= 1;
    if (n == 1) return res;

    long long limit = sqrt(n) + 1;
    for (long long i = 3; i <= limit; i += 2) {
        while (n != i) {
            if (n % i == 0) {
                res = max(res, i);
                n /= i;
            }
            else break;
        }
    }
    res = max(res, n);

    return res;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int caseNum; cin >> caseNum;
    long long n;
    while (caseNum--) {
        cin >> n;
        cout << maxFactor(n) << endl;
    }

    return 0;
}
```

