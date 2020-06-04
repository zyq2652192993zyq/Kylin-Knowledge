> # Project Euler #4: Largest palindrome product

Tags: `Medium`

Links: https://www.hackerrank.com/contests/projecteuler/challenges/euler004/problem

------

This problem is a programming version of [Problem 4](https://projecteuler.net/problem=4) from [projecteuler.net](https://projecteuler.net/)

A palindromic number reads the same both ways. The smallest 6 digit palindrome made from the product of two 3-digit numbers is $101101=143 \times 707$.

Find the largest palindrome made from the product of two 3-digit numbers which is less than $N$.

**Input Format**

First line contains $T$ that denotes the number of test cases. This is followed by $T$ lines, each containing an integer, $N$

**Constraints**

* $1 \leq T \leq 100$
* $101101 < N < 1000000$

**Output Format**

Print the required answer for each test case in a new line.

**Sample Input 0**

```
2
101110
800000
```

**Sample Output 0**

```
101101
793397
```

**Explanation 0**

* $101101$ is product of $143$ and $707$
* $793397$ is product of $869$ and $913$

-----

首先进行预处理，遍历从999到100之间所有的三位数相乘的结果，存入数组`num`，因为可能存在重复值，所以使用`unique`去重，并用`len`保留无重复值的长度；检验是否是回文数，数值最大不会超过8位，可以认为是$O(1)$的检验。在没有去重时，数组`num`的长度是1269，近似认为是$10^3$，预处理时间复杂度$10^6$，排序时间复杂度$O(n \log n)$，也不会超时。

因为数组已经有序，接下来就可以利用二分查找加速，利用`lower_bound`去寻找第一个不小于目标值的数，它的前一个位置就是最后一个小于目标值的数，这样最多100个数，每个数的查找是$\log 10^3$，时间复杂度是$O(T \log 10^3 + 10^3 \log 10^3 + 10^6)$.

```c++
#include <bits/stdc++.h>

using namespace std;

vector<int> num;
int len;

bool isPalindrome(int x)
{
    string s = to_string(x);
    int end = s.size() - 1, start = 0;
    
    while(start <= end){
        if (s[start] == s[end]){
            ++start;
            --end;
        }
        else{
            return false;
        }
    }
    
    return true;
}

void init()
{
    for (int i = 999; i >= 100; --i){
        for (int j = i; j >= 100; --j){
            int tmp = i * j;
            if (isPalindrome(tmp)){
                num.push_back(tmp);
            }
        }
    }

    sort(num.begin(), num.end());
    len = unique(num.begin(), num.end()) - num.begin();
}

int solve(int target)
{
    int pos = lower_bound(num.begin(), num.begin() + len, target) - num.begin();
    return num[pos - 1];
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
    }
       
   return 0;
}
```



