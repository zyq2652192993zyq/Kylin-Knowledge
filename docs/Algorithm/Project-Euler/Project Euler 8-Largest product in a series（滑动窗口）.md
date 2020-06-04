> # Project Euler #8: Largest product in a series（滑动窗口）

Tags: `Easy`

Links: https://www.hackerrank.com/contests/projecteuler/challenges/euler008/problem

-----

This problem is a programming version of [Problem 8](https://projecteuler.net/problem=8) from [projecteuler.net](https://projecteuler.net/)

Find the greatest product of consecutive $K$ digits in the $N$ digit number.

**Input Format**

First line contains $T$ that denotes the number of test cases.
First line of each test case will contain two integers $N$ & $K$.
Second line of each test case will contain a $N$ digit integer.

**Constraints**

* $1 \leq T \leq 100$
* $1 \leq K \leq 7$
* $K \leq N \leq 1000$

**Output Format**

Print the required answer for each test case.

**Sample Input 0**

```
2
10 5
3675356291
10 5
2709360626
```

**Sample Output 0**

```
3150
0
```

------

解法一，因为`k <= 7`，所以直接暴力遍历也可以，也是$O(n)$的算法，另外仅仅7个数连乘，不会超出`int`，但是Project Euler网站是13位连乘，需要改写成`long long`类型才能得到正确结果。

```c++
#include <bits/stdc++.h>

using namespace std;

int n, k;
vector<int> seq(1005);

int solve()
{
	int res = 0, tmp = 1;
	for (int i = 0; i < n; ++i) {
		tmp = 1;
		bool flag = false;
		for (int j = i; j < i + k; ++j) {
			if (i + k > n) { tmp = 0; flag = true; break; }
			tmp *= seq[j];
		}
		if (!flag) res = max(res, tmp);
	}

	return res;
}


int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int caseNum; cin >> caseNum;
	char digit;
	while (caseNum--) {
		cin >> n >> k;
		for (int i = 0; i < n; ++i) {
			cin >> digit;
			seq[i] = (digit - '0');				
		}
                
		cout << solve() << endl;
	}

	return 0;
}
```

解法二，很显然这是一个滑动窗口的问题，但是因为存在0，所以变得会稍微有些麻烦，因为有0存在，我们就不能单纯的乘上下一个数字，除掉开头的数字。解决办法就是在数据读取的时候，利用一个数组`interval`保存不存在0的区间的左右端点，并计算出长度，然后我们对区间长度大于等于$K$的范围利用滑动窗口来解决，时间复杂度$O(n)$。

卡掉上面暴力遍历的办法是让`K <= 10`，然后数据范围是$N \leq 10^7$。

