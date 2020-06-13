> # Project Euler 10-Summation of primes（前缀和+二分）

Tags: `Medium`

Links: https://www.hackerrank.com/contests/projecteuler/challenges/euler010/problem

-----

This problem is a programming version of [Problem 10](https://projecteuler.net/problem=10) from [projecteuler.net](https://projecteuler.net/)

The sum of the primes below $10$ is $2+3+5+7=17$.

Find the sum of all the primes not greater than given $N$.

**Input Format**

The first line contains an integer $T$ i.e. number of the test cases.
The next $T$ lines will contains an integer $N$.

**Constraints**

* $1 \leq T \leq 10^4$
* $1 \leq N \leq 10^6$

**Output Format**

Print the value corresponding to each test case in separate line.

**Sample Input 0**

```
2
5
10
```

**Sample Output 0**

```
10
17
```

------

```c++
#include <bits/stdc++.h>

using namespace std;

vector<int> seq;
int n = 0;
vector<long long> preSum;

bool isPrime(int n)
{
    int limit = sqrt(n) + 1;
    for (int i = 3; i <= limit; i += 2) {
        if (n % i == 0) return false;
    }

    return true;
}


void generate()
{
    seq.push_back(2), seq.push_back(3);
    n = 2;

    int i = 5;
    while (i <= 1e6 + 5) {
        if (isPrime(i)) { seq.push_back(i); ++n; }
        if (isPrime(i + 2)) { seq.push_back(i + 2); ++n; }
        i += 6;
    }

    preSum.resize(n + 1, 0);
    for (int i = 1; i <= n; ++i) preSum[i] = preSum[i - 1] + seq[i - 1];
}

long long solve(int target)
{
    int pos = upper_bound(seq.begin(), seq.end(), target) - seq.begin();
    return preSum[pos];    
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    generate();

    int caseNum; cin >> caseNum;
    int number;
    while (caseNum--) {
        cin >> number;
        cout << solve(number) << endl; 
    }

    return 0;
}
```

通过预处理预先生成$10^6$以内的素数，采用6倍数素数检验的方法来生成素数，然后对于每个样例采用二分的方法查找小于等于目标值对应的下标，然后直接返回前缀和。这样最坏的情况计算次数是$10^4 \times \log{10^6}$，也完全不会超时。