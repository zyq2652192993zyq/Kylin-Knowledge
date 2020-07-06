> # Project Euler 15-Lattice paths（Pascal三角形，组合数计算）

Tags: `Easy`

Links: https://www.hackerrank.com/contests/projecteuler/challenges/euler015/problem

------

This problem is a programming version of [Problem 15](https://projecteuler.net/problem=15) from [projecteuler.net](https://projecteuler.net/)

Starting in the top left corner of a $2\times 2$ grid, and only being able to move to the right and down, there are exactly $6$ routes to the bottom right corner.

![img](https://hr-challenge-images.s3.amazonaws.com/2641/2641.gif)

How many such routes are there through a $N \times M$ grid? As number of ways can be very large, print it modulo $(10^9 + 7)$.

**Constraints**

* $1 \leq T \leq 10^3$
* $1 \leq N \leq 500$
* $1 \leq M \leq 500$

**Output Format**

Print the values corresponding to each test case.

**Sample Input**

```
2
2 2
3 2
```

**Sample Output**

```
6
10
```

------

实际上就是计算组合数$\text{C}_{m+n}^n$，并且对大数取模，于是联想到LeetCode 118和119的Pascal三角形，于是对于每组测试用例，都是$O(1)$得到结果。

```c++
#include <bits/stdc++.h>

using namespace std;

const long long MODE = 1e9 + 7;

vector<vector<long long> > d(1005);

long long solve(int n, int m)
{
    return d[m + n][n];
}

void init()
{
    for (int i = 0; i <= 1000; ++i) {
        d[i].resize(i + 1, 1);
        for (int j = 1; j < i; ++j) {
            d[i][j] = (d[i - 1][j - 1] + d[i - 1][j]) % MODE;
        }
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
        int n, m; cin >> n >> m;
        cout << solve(n, m) << endl;
    }

    return 0;
}
```

