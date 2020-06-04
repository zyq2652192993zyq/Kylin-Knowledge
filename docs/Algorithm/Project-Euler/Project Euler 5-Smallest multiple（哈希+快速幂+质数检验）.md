> # Project Euler #5: Smallest multiple

Tags: `Medium`

Links: https://www.hackerrank.com/contests/projecteuler/challenges/euler005/problem

------

This problem is a programming version of [Problem 5](https://projecteuler.net/problem=5) from [projecteuler.net](https://projecteuler.net/)

$2520$  is the smallest number that can be divided by each of the numbers from $1$ to $10$ 

without any remainder.
What is the smallest positive number that is evenly divisible(divisible with no remainder) by all of the numbers from $1$ to $N$ ?

**Input Format**

First line contains $T$ that denotes the number of test cases. This is followed by $T$ lines, each containing an integer, $N$.

**Constraints**

* $1 \leq T \leq 10$
* $1 \leq N \leq 40$

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
6
2520
```

**Explanation 0**

- You can check $6$ is divisible by each of $\{ 1, 2, 3\}$, giving quotient of $\{ 6,3,2\}$ respectively.

- You can check $2520$ is divisible by each of $\{ 1,2,3,4,5,6,7,8,9,10\}$, giving quotient of $\{ 2520,1260,840,630,504,420,360,315,280,252\}$ respectively.

-------

首先来看当`n == 10`的时候，结果为什么是2520：

```
2 = 2
3 = 3
4 = 2 * 2
5 = 5
6 = 2 * 3
7 = 7
8 = 2 * 2 * 2
9 = 3 * 3
10 = 2 * 5

2520 = 2^3 * 3^2 * 5 * 7
```

也就是对10以内的数字进行质因数分解，最后统计每个质因数的最大个数，结果乘起来即可。

那么很自然的需要统计质因数的频率信息，我们将总体每个质因数的最大频率存储在数组$freq$中，用`tmp`去记录每一个数字的统计信息，最后只需要对比`tmp`和`freq`的对应位置的数值大小即可，让`freq`每次取最大值，注意`tmp`在每次计算之前要初始化，`freq`再计算新的数字之前也需要初始。

当我们对`n`内的数字进行质因数分解的时候，很显然，比如我得到一个质因子5，那么需要找到它在`tmp`中的下标，于是为了加速这个下标查找过程，我们利用`unordered_map`来存储对应信息，其中`primeToPos`记录每个质因数对应的下标，`posToPrime`记录下标对应的质因数。之所以需要`posToPrime`，是因为计算最终结果的时候，我们需要通过`freq`计算，而`freq`只有下标信息，所以需要也建立一个映射关系。

另外最后在计算结果的时候，肯定要进行幂运算，所以想到利用快速幂进行加速。

```c++
#include <bits/stdc++.h>

using namespace std;

unordered_map<int, int> primeToPos, posToPrime; //to fasten the find process
vector<int> freq, tmp; //calculate the frequency of prime number
int len;

bool isPrime(int n)
{
    if (n == 2) return true;
    if (!(n & 1)) return false;
    int limit = sqrt(n) + 1;
    for (int i = 3; i <= limit; i += 2) {
        if (!(n % i)) return false; 
    }

    return true;
}

void init()
{
    int cnt = 0;
    for (int i = 2; i <= 40; ++i) {
        if (isPrime(i)) {
            primeToPos[i] = cnt;
            posToPrime[cnt] = i;
            ++cnt;
        }
    }

    len = cnt;
    freq.resize(len, 0);
    tmp.resize(len, 0);
}

long long myPower(long long base, long long exp)
{
    if (!exp) return 1;

    long long res = 1;
    do {
        if (exp & 1) res *= base;
        base *= base;
        exp >>= 1;
    } while (exp);

    return res;
}

void calculate(int n)
{
    for (int i = 2; i <= n; ++i) {
        while (n != i) {
            if (!(n % i)) {
                ++tmp[primeToPos[i]];
                n /= i;
            }
            else break;
        }
    }
    ++tmp[primeToPos[n]];
}

inline void countFreq()
{
    for (int i = 0; i < len; ++i) {
        freq[i] = max(freq[i], tmp[i]);
    }
}


long long solve(int n)
{
    for (int i = 2; i <= n; ++i) {
        fill(tmp.begin(), tmp.end(), 0);
        calculate(i);
        countFreq();
    }

    long long res = 1;
    for (int i = 0; i < len; ++i) {
        res *= myPower(posToPrime[i], freq[i]);
    }

    return res;
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    init();

    int caseNum; cin >> caseNum;
    int n;
    while (caseNum--) {
        cin >> n;
        cout << solve(n) << endl;
        fill(freq.begin(), freq.end(), 0);
    }

    return 0;
}
```













