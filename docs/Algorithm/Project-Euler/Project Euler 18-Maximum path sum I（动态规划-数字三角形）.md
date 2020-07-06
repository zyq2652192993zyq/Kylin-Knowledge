> # Project Euler 18-Maximum path sum I（动态规划-数字三角形）

Tags: `Easy`

Links: https://www.hackerrank.com/contests/projecteuler/challenges/euler018/problem

-----

This problem is a programming version of [Problem 18](https://projecteuler.net/problem=18) from [projecteuler.net](https://projecteuler.net/)

By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is $23$. The path is denoted by numbers in bold.
$$
\begin{array}{c}
3 \\
74 \\
246 \\
8593
\end{array}
$$
That is $3+4+7+9=23$.

Find the maximum total from top to bottom of the triangle given in input.

**Input Format**

First line contains $T$, the number of testcases. For each testcase:
First line contains $N$, the number of rows in the triangle.
For next $N$ lines, $i$'th line contains $i$ numbers.

**Constraints**

* $1 \leq T \leq 10$
* $1 \leq N \leq 15$

* $\text{numbers} \in [0, 100)$

**Output Format**

For each testcase, print the required answer in a newline.

**Sample Input**

```
1
4
3
7 4
2 4 6
8 5 9 3
```

**Sample Output**

```
23
```

**Explanation**

As shown in statement.

------

动态规划里数字三角形的板子题。

```c++
#include <bits/stdc++.h>

using namespace std;

vector<vector<int> > d(20, vector<int>(20, 0)), seq(20, vector<int>(20, 0));
int n;

void init()
{
    for (int i = 0; i < 20; ++i) 
        fill(d[i].begin(), d[i].end(), 0);
}


int solve()
{
    init();

    d[0][0] = seq[0][0];
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (j == 0) d[i][j] = d[i - 1][j];
            else if (j == i) d[i][j] = d[i - 1][j - 1];
            else d[i][j] = max(d[i - 1][j], d[i - 1][j - 1]);
            d[i][j] += seq[i][j];
        }
    }

    return *max_element(d[n - 1].begin(), d[n - 1].begin() + n);
}

int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        cin >> n;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= i; ++j) {
                cin >> seq[i][j];
            }
        }

        cout << solve() << endl;
    }

    return 0;
}
```

