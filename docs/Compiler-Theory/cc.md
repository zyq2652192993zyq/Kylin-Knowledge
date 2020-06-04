> # 1456.Maximum Number of Vowels in a Substring of Given Length

Tags: `Medium` `String` `Sliding Window`

Links: https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/

-----

Given a string `s` and an integer `k`.

Return *the maximum number of vowel letters* in any substring of `s` with length `k`.

**Vowel letters** in English are (a, e, i, o, u).

 

**Example 1:**

```
Input: s = "abciiidef", k = 3
Output: 3
Explanation: The substring "iii" contains 3 vowel letters.
```

**Example 2:**

```
Input: s = "aeiou", k = 2
Output: 2
Explanation: Any substring of length 2 contains 2 vowels.
```

**Example 3:**

```
Input: s = "leetcode", k = 3
Output: 2
Explanation: "lee", "eet" and "ode" contain 2 vowels.
```

**Example 4:**

```
Input: s = "rhythms", k = 4
Output: 0
Explanation: We can see that s doesn't have any vowel letters.
```

**Example 5:**

```
Input: s = "tryhard", k = 4
Output: 1
```

 

**Constraints:**

- `1 <= s.length <= 10^5`
- `s` consists of lowercase English letters.
- `1 <= k <= s.length`

------

题意是统计长度为`k`的连续子串内元音的最多个数，很明显的滑动窗口问题。

最开始先计算前`k`个字符里元音的个数，然后窗口每次向右移动一个单位，然后窗口的首部去掉一个字符。用`maxVal`来保存最大值，用`tmpMax`来存储每个窗口的元音的个数。

时间复杂度$O(n)$。

```c++
class Solution {
	unordered_set<char> us{'a', 'e', 'i', 'o', 'u'};
public:
    int maxVowels(string s, int k) {
    	std::ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);

        int n = s.size();
        int maxVal = 0, tmpMax = 0;
        for (int i = 0; i < k; ++i) {
        	if (isVowel(s[i])) ++tmpMax;
        }
        maxVal = tmpMax;

        for (int i = k; i < n; ++i) {
        	if (isVowel(s[i - k])) --tmpMax;
        	if (isVowel(s[i])) ++tmpMax;
        	maxVal = max(maxVal, tmpMax);
        }

        return maxVal;
    }

    inline bool isVowel(const char & ch)
    {
    	return us.find(ch) != us.end();
    }
};
```

