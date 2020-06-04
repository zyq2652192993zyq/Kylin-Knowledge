> # Project Euler #6: Sum square difference（等差数列求和+平方和公式）

Tags: `Easy`

Links: https://www.hackerrank.com/contests/projecteuler/challenges/euler006/problem

------

This problem is a programming version of [Problem 6](https://projecteuler.net/problem=6) from [projecteuler.net](https://projecteuler.net/)

The sum of the squares of the first ten natural numbers is, $1^2 +2 ^2 + \cdots + 10^2 = 385$. The square of the sum of the first ten natural numbers is, $(1+2+\cdots +10)^2=3025$. 

Hence the absolute difference between the sum of the squares of the first ten natural numbers and the square of the sum is $3025 - 385 = 2640$

Find the absolute difference between the sum of the squares of the first $N$ natural numbers and the square of the sum.

**Input Format**

First line contains $T$ that denotes the number of test cases. This is followed by $T$ lines, each containing an integer,$N$.

**Constraints**

* $1 \leq T \leq 10^4$
* $1 \leq N \leq 10^4$

**Output Format**

Print the required answer for each test case.

**Sample Input 0**

```
2
3
10
```

**Sample Output 0**

```
22
2640
```

------

等差数列求和公式：
$$
\sum_{i=1}^ n i = \frac{n(n+1)}{2}
$$
平方和公式：
$$
\sum_{i = 1} ^n i^2 = \frac{n(n+1)(2n+1)}{6}
$$
证明方法就是升幂法，比如平方和公式：
$$
(n+1)^3 = n^3 +3n^2+3n+1 \\
(n+1)^3 - n^3 = 3n^2 + 3n + 1 \\
\cdots \\
2^3 - 1^3 = 3 \times 1^2 + 3 \times 1 + 1 \\
\therefore (n+1)^3 - 1 = 3 \times \sum_{i = 1} ^n i^2 + 3 \times \sum_{i=1}^ n i + n
$$
从而可得到平方和公式，立方和公式的求法同理。例外使用C++求解的时候，计算平方和公式的分子时，选用`int`类型可能存在溢出风险，保险起见选用`long long`。$O(1)$求得结果

```c++
#include <bits/stdc++.h>

using namespace std;

inline long long solve(long long n)
{
    return (n * (1 + n) / 2) * (n * (1 + n) / 2) - n * (2 * n + 1) * (n + 1) / 6;
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int caseNum; cin >> caseNum;
    long long n;
    while (caseNum--) {
        cin >> n;
        cout << solve(n) << endl;
    }

    return 0;
}
```



