> # Project Euler #1: Multiples of 3 and 5

Tags: `Easy`

Links: https://www.hackerrank.com/contests/projecteuler/challenges/euler001/problem

-----

This problem is a programming version of [Problem 1](https://projecteuler.net/problem=1) from [projecteuler.net](https://projecteuler.net/)

If we list all the natural numbers below 10 that are multiples of 3 or 5 , we get 3, 5, 6 and 9. The sum of these multiples is 23.

Find the sum of all the multiples of  3 or 5 below N.

# Input Format

First line contains T that denotes the number of test cases. This is followed by T lines, each containing an integer, N.

# Constraints

* $1 \leq T \leq 10^ 5$
* $1 \leq N \leq 10^9$

# Output Format

For each test case, print an integer that denotes the sum of all the multiples of 3 or 5 below N

# Sample Input

```
2
10
100
```

# Sample Output

```
23
2318
```

---

```c++
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

inline long long cal(int n)
{
    return (long long)n * (long long)(1 + n) / 2;
}

inline int num(const int & n, const int & mode)
{
    return n % mode == 0 ? n / mode - 1 : n / mode;
}

int main(){
    int t;
    cin >> t;
    for(int a0 = 0; a0 < t; a0++){
        int n;
        cin >> n;
        int threeNum = num(n, 3);
        int fiveNum = num(n, 5);
        int fifteenNum = num(n, 15);
        long long result = 3 * cal(threeNum) + 5 * cal(fiveNum) - 15 * cal(fifteenNum);
        cout << result << endl;
    }

    return 0;
}


```

只需要注意3和5的倍数被计算了两次，需要从最后结果中去掉。考虑可以整除3或5或15的情形，只考虑不超过N 的数值。