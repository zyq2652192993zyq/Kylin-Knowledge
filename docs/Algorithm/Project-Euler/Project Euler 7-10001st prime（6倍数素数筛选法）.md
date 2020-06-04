> # Project Euler #7: 10001st prime

Tags: `Easy`

Links: https://www.hackerrank.com/contests/projecteuler/challenges/euler007/problem

------

This problem is a programming version of [Problem 7](https://projecteuler.net/problem=7) from [projecteuler.net](https://projecteuler.net/)

By listing the first six prime numbers: $2,3,5,7,11,13$, we can see that the $6^{th}$ prime is $13$.

What is the $N^{th}$ prime number?

**Input Format**

First line contains $T$ that denotes the number of test cases. This is followed by $T$ lines, each containing an integer, $N$.

**Constraints**

* $1 \leq T \leq 10^3$
* $1 \leq N \leq 10^4$

**Output Format**

Print the required answer for each test case.

**Sample Input 0**

```
2
3
6
```

**Sample Output 0**

```
5
13
```

------

方法是采用预处理，用一个数组`seq`存储素数，因为数据范围为$10^4$，所以不会超过内存限制。这样预处理之后，每个查询是$O(1)$的时间复杂度。

分析一下预处理的时间复杂度，第$10^4$个素数是104729，在$10^5$级别，判定素数的时间复杂度是$O(\sqrt n)$，所以是$10^4 / 6 \times \sqrt{10^5}$，是$10^7$级别，一般评测机还是可以通过的。

```c++
#include <bits/stdc++.h>

using namespace std;

vector<long long> seq;

bool isPrime(long long n)
{
    long long limit = sqrt(n) + 1;
    for (long long i = 3; i <= limit; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

void calculate()
{
    long long number = 5;
    while (true) {
        if ((int)seq.size() >= 1e4) break;
        if (isPrime(number)) seq.push_back(number);
        if (isPrime(number + 2)) seq.push_back(number + 2);
        number += 6;
    }
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    seq.push_back(2), seq.push_back(3);
    calculate();

    int caseNum; cin >> caseNum;
    int n;
    while (caseNum--) {
        cin >> n;
        cout << seq[n - 1] << endl;
    }

    return 0;
}
```

