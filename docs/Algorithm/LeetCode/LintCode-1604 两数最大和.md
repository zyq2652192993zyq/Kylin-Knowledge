> # LintCode-1604 两数最大和

Tags: `Medium` `Hash Table`

Links: https://www.lintcode.com/problem/maximum-sum-of-two-numbers/description

----

给定一个由N个整数组成的数组A，返回两个数字的最大总和，规定这两个数的所有位加起来相等。 如果没有两个数字的各个位相加和相等，则该函数应返回-1。

### 样例

```
示例1:
输入:
A = [51, 71, 17, 42]
输出: 93
解释：这里有两对各个位相加和相等的数：(51, 42) 和 (17,71)，第一对的和是93
示例2:
输入:
A = [42, 33, 60]
输出: 102
解释：所有的数各个位相加的和都相等，选择42 + 60 = 102
示例3:
输入:
A = [51, 32, 43]
输出: -1
解释: 所有数的各个位相加和都不一样，因此返回-1
```

### 注意事项

- N的范围是 [1, 200000]
- A中的每一个参数的范围是 [1, 1000000000]

-----

```c++
class Solution {
public:
    /**
     * @param A: An Integer array
     * @return: returns the maximum sum of two numbers
     */
    int MaximumSum(vector<int> &A) {
        std::ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);
        
        unordered_map<int, vector<int>> m;
        int n = A.size();
        for (int i = 0; i < n; ++i) {
            int sum = cal(A[i]);
            if (m.find(sum) != m.end()) {
                m[sum].push_back(A[i]);
            }
            else {
                m[sum] = {A[i]};
            }
        }
        
        int res = -1;
        for (auto e : m) {
            if (e.second.size() >= 2) {
                sort(e.second.begin(), e.second.end());
                int len = e.second.size();
                res = max(res, e.second[len - 1] + e.second[len - 2]);
            }
        }
        
        return res;
    }
    
    int cal(int n)
    {
        int sum = 0;
        while (n) {
            sum += n % 10;
            n /= 10;
        }
        return sum;
    }
};
```

