> # Project Euler 9-Special Pythagorean triplet

Tags: `Easy`

Links: https://www.hackerrank.com/contests/projecteuler/challenges/euler009/problem

-----

This problem is a programming version of [Problem 9](https://projecteuler.net/problem=9) from [projecteuler.net](https://projecteuler.net/)

A Pythagorean triplet is a set of three natural numbers, $a < b < c$, fro which,
$$
a^2 + b^2 = c^2
$$
Given $N$, Check if there exists any Pythagorean triplet for which $a+b+c=N$
Find maximum possible value of $abc$ among all such Pythagorean triplets, If there is no such Pythagorean triplet print $-1$.

**Input Format**

The first line contains an integer $T$ i.e. number of test cases.
The next $T$ lines will contain an integer $N$.

**Constraints**

* $1 \leq T \leq 3000$
* $1 \leq N \leq 3000$

**Output Format**

Print the value corresponding to each test case in separate lines.

**Sample Input 0**

```
2
12
4
```

**Sample Output 0**

```
60
-1
```

-----

解法一：暴力求解，首先应该明确，总和$N$一定是偶数，这个可以通过枚举三个都是奇数，两个奇数，一个奇数，以及没有奇数的情况来进行验证。于是第一步应该判定$N$的奇偶性。

另外根据限制条件$a < b < c$，可以知道$a < \frac{N}{3}$，转化成代码就是`(n-2)/3`，同样由$b < c$得到$b < \frac{n -a}{2}$，转化成代码就是`(n- a - 1) / 2`，然后暴力遍历求解即可。

另外$a \geq 3$，如果`a=1`，那么$(c-b)(c+b) = 1$，则`c=1, b=0`，不符合；如果`a=2`，那么$(c-b)(c+b) = 4$，也是无和理解，所以可以从3开始暴力遍历，这样时间复杂度是$O(n^2)$。在第5**个测试用例超时**，其他都能通过。

```c++
#include <bits/stdc++.h>

using namespace std;

long long solve(int n)
{
    long long res = -1;
    if (n & 1) return res;

    for (long long a = 3; a <= (n - 3) / 3; ++a) {
        for (long long b = a + 1; b <= (n - 1 - a) / 2; ++b) {
            long long c = n - a - b;
            if (c > b && c * c == a * a + b * b) {
                res = max(res, a * b * c);
            }
        }
    }

    return res;
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int caseNum; cin >> caseNum;
    int n;
    while (caseNum--) {
        cin >> n;
        cout << solve(n) << endl;
    }

    return 0;
}
```

解法二：将毕达哥拉斯三元组进行参数化表示，一个小技巧是将$a, b, c$表示成：
$$
a = m ^2-n^2 , b = 2mn, c = m^2+n^2 \\
可以满足a < b < c
$$
考虑毕达哥拉斯三元组的最小表示形式，也就是说$\text{GCD}(a, b, c)=1$，这样的集合组成一个最小表示，其他的都可以认为是$a, b, c$乘上一个相同的倍数$d(d \geq 1)$。

这样$a, b, c$可以表示成：
$$
a = (m^2 - n^2)d, b = 2mnd, c = (m^2+n^2)d
$$
首先有一个结论，如果$a^2 + b^2 = c^2$，并且$\text{GCD}(a, b) = 1$， 那么$\text{GCD}(a, b, c) = 1$。

证明：
$$
如果\text{GCD}(a, b) = 1 \\
那么\text{GCD}(a^2, b^2) = 1 \\
首先如果\text{GCD}(a^2, c^2) \neq 1\\
则存在大于1的正整数d使得： \\
a^2 = d \times k_1, c^2 = d \times k_2 \\
因为c^2 = a^2 + b^2 = d \times k_1 + b^2 = d \times k_2 \\
则b^2 = d \times(k_2 - k_1) \\
说明a,b存在大于1的公因数d，与假设矛盾了。\text{GCD}(b, c)同理可证 \\
于是\text{GCD}(a, b) = \text{GCD}(b, c) = \text{GCD}(a, c) = 1 \\
\therefore \text{GCD}(a,b,c) = 1
$$
 然后我们来根据不等关系缩小搜索范围：
$$
a+b+c=2m(m+n)d = N \geq 2m^2 \\
\therefore m \leq \sqrt{\frac{N}{2}} \\
\text{def} \quad k = m + n \\
显然k > m \\
另外应为m > n \\
所以k < 2m \\
$$
这样我们只需对`m, k`进行枚举，保证$GCD(m, k)=1$，并且$N / 2mk$可以整除即可得到结果。

因为`m`的枚举范围是$\sqrt n$， `k`的枚举范围是$\sqrt n$，算法的时间复杂度是$O(n)$。

```c++
#include <bits/stdc++.h>

using namespace std;

long long sum;

long long GCD(long long a, long long b)
{
    return b == 0 ? a : GCD(b, a % b);
}


long long solve()
{
    if (sum & 1) return -1;

    long long res = -1;
    long long mLimit = sqrt(sum >> 1) + 1;
    for (long long m = 2; m <= mLimit; ++m) {
        for (long long k = m + 1; k < 2 * m; ++k) {
            if (GCD(k, m) == 1 && sum % (2 * m * k) == 0) {
                long long n = k - m, d = sum / (2 * m * k);
                long long a = (m * m - n * n) * d;
                long long b = 2 * m * n  *d;
                long long c = (m * m + n * n) * d;
                res = max(res, a * b * c);
            }
        }
    }

    return res;
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        cin >> sum;
        cout << solve() << endl;
    }

    return 0;
}
```

注意这里我们不需要保证$a < b$，因为总可以通过交换数值满足条件。