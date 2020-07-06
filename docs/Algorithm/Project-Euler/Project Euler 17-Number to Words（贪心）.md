> # Project Euler 17-Number to Words（贪心）

Tags: `Easy`

Links: https://www.hackerrank.com/contests/projecteuler/challenges/euler017/problem

-----

This problem is a programming version of [Problem 17](https://projecteuler.net/problem=17) from [projecteuler.net](https://projecteuler.net/)

The numbers $1$ to $5$ written out in words are $One, Two, Three, Four, Five$

First character of each word will be capital letter for example:

$104382426112$ is 

```
One Hundred Four Billion Three Hundred Eighty Two Million Five Hundred Forty Six Thousand One Hundred Twelve
```

Given a number, you have to write it in words.

**Input Format**

The first line contains an integer $T$ , i.e., number of test cases.
Next $T$ lines will contain an integer $N$.

**Constraints**

* $1 \leq T \leq 10$
* $0 \leq N \leq 10^{12}$

**Output Format**

Print the values corresponding to each test case.

**Sample Input**

```
2
10
17
```

**Sample Output**

```
Ten
Seventeen
```

**Explanation**

Follow the rules given in statement.

-----

这道题给出的难度分类竟然是`Easy`，其实就是LeetCode的273题，分类可是Hard。

```c++
#include <bits/stdc++.h>

using namespace std;

string digits[20] = {"Zero", "One", "Two", "Three", "Four", "Five", 
                    "Six", "Seven", "Eight", "Nine", "Ten", 
                    "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", 
                    "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

string tens[10] = {"Zero", "Ten", "Twenty", "Thirty", "Forty", "Fifty", 
                    "Sixty", "Seventy", "Eighty", "Ninety"};

string int2string(long long n) 
{
    if (n >= 1000000000) {
        return int2string(n / 1000000000) + " Billion" + int2string(n % 1000000000);
    } else if (n >= 1000000) {
        return int2string(n / 1000000) + " Million" + int2string(n % 1000000);
    } else if (n >= 1000) {
        return int2string(n / 1000) + " Thousand" + int2string(n % 1000);
    } else if (n >= 100) {
        return int2string(n / 100) + " Hundred" + int2string(n % 100);
    } else if (n >= 20) {
        return  " " + tens[n / 10] + int2string(n % 10);
    } else if (n >= 1) {
        return " " + digits[n];
    } else {
        return "";
    }
}

string solve(long long n)
{
    if (n == 0) return "Zero";

    string ret = int2string(n);
    return ret.substr(1, ret.length() - 1);
}


int main()
{
    std::ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int caseNum; cin >> caseNum;
    while (caseNum--) {
        long long n; cin >> n;
        cout << solve(n) << endl;
    }

    return 0;
}
```

另外这道题和Project Euler存在的一点区别是，原题采用英式写法，多了连字符，但是连字符并不计算在内，另外当数字超过100，需要加上`and`，但是整百的情况不用。

```c++
#include <bits/stdc++.h>

using namespace std;

string digits[20] = {"Zero", "One", "Two", "Three", "Four", "Five", 
					"Six", "Seven", "Eight", "Nine", "Ten", 
					"Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", 
					"Sixteen", "Seventeen", "Eighteen", "Nineteen"};

string tens[10] = {"Zero", "Ten", "Twenty", "Thirty", "Forty", "Fifty", 
					"Sixty", "Seventy", "Eighty", "Ninety"};

string int2string(long long n) 
{
	if (n >= 1000000000) {
	    return int2string(n / 1000000000) + " Billion" + int2string(n % 1000000000);
	} else if (n >= 1000000) {
	    return int2string(n / 1000000) + " Million" + int2string(n % 1000000);
	} else if (n >= 1000) {
	    return int2string(n / 1000) + " Thousand" + int2string(n % 1000);
	} else if (n >= 100) {
	    return int2string(n / 100) + " Hundred" + (n % 100 == 0 ? "" : " and" + int2string(n % 100));
	} else if (n >= 20) {
	    return  " " + tens[n / 10] + int2string(n % 10);
	} else if (n >= 1) {
	    return " " + digits[n];
	} else {
	    return "";
	}
}

string generate(long long n)
{
	if (n == 0) return "Zero";

    string ret = int2string(n);
    return ret.substr(1, ret.length() - 1);
}

int calculate(const string & s)
{
	int n = s.size();
	int cnt = 0;
	for (int i = 0; i < n; ++i) {
		if (s[i] == ' ') ++cnt;
	}

	return n - cnt;
}

int solve(int start, int end)
{
	int sum = 0;
	for (int i = start; i <= end; ++i) {
		string tmp = generate(i);
		sum += calculate(tmp);
	}

	return sum;
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cout << solve(1, 1000) << endl;

	return 0;
}
```

