> # Project Euler 13-Large sum（高精度或者模拟竖式加法）

Tags: `Easy`

Links: https://www.hackerrank.com/contests/projecteuler/challenges/euler013/problem

-----

This problem is a programming version of [Problem 13](https://projecteuler.net/problem=13) from [projecteuler.net](https://projecteuler.net/)

Work out the first ten digits of the sum of $N 50-\text{digit}$ numbers.

**Input Format**

First line contains $N$, next $N$ lines contain a 50 digit number each.

**Constraints**

* $1 \leq N \leq 10^3$

**Output Format**

Print only first 10 digit of the final sum

**Sample Input**

```
5
37107287533902102798797998220837590246510135740250
46376937677490009712648124896970078050417018260538
74324986199524741059474233309513058123726617309629
91942213363574161572522430563301811072406154908250
23067588207539346171171980310421047513778063246676
```

**Sample Output**

```
2728190129
```

---

题目的样例解释给出了运算的最终结果，一个很自然的想法就是使用高精度，计算出结果，取前十位，利用python这种天然带高精度的，很方便。

但是注意到因为只取前十位，我们可以模拟竖式加法，也就是将50位的数字分成5块，每块包含10个数字，最开始计算所有数字的后10位相加的结果，最多就$10^{12}$位，用`long long`就可以，然后我们对这个结果除以$10^{10}$，也就是后10位数字已经完成了加法，不会对接下来的计算产生影响，我们只取出进位的部分。

注意的一点是，最高的10位数字计算完`sum`不用再除以$10^{10}$了，转成字符串取前十位即可，这样极大的节省了空间。

```c++
#include <bits/stdc++.h>

using namespace std;

int n;
vector<string> seq;

string solve()
{
    long long sum = 0;
    for (int cnt = 4; cnt >= 0; --cnt) {
        for (int i = 0; i < n; ++i) {
            sum += stoll(seq[i].substr(cnt * 10, 10));
        }
        if (cnt) sum /= (long long)10000000000;
    }

    // long long base = 1;
    // while (base * 10 <= sum) base *= 10;
    // int gap = to_string(base).size() - 10;
    // sum = floor(sum * 1.0 / pow(10, gap) + 0.5);

    return to_string(sum).substr(0, 10);
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    string line;
    for (int i = 0; i < n; ++i) {
        cin >> line;
        seq.push_back(line);
    }

    cout << solve() << endl;

    return 0;
}
```

