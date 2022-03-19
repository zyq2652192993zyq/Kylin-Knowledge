// 洛谷-P3374 【模板】树状数组 1
#include <bits/stdc++.h>

using namespace std;


class SegmentTreee {
	inline int lowbit(int x) { return x & (-x); }
public:
	int n;
	vector<int> tree;

	SegmentTreee(int num): n(num + 5) {
		tree.resize(n, 0);
	}

	void init(vector<int> & seq) {
		for (int i = 1; i <= n; ++i) {
			tree[i] += seq[i - 1];
			int j = i + lowbit(i);
			if (j <= n) tree[j] += tree[i];
		}
	}

	int query(int pos)
	{
		int res = 0;
		while (pos) {
			res += tree[pos];
			pos -= lowbit(pos);
		}

		return res;
	}


	int rangeQuery(int l, int r) {
		return query(r) - query(l - 1);
	}


	void add(int pos, int val)
	{
		while (pos <= n) {
			tree[pos] += val;
			pos += lowbit(pos);
		}
	}

};


class Solution {
public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        std::ios_base::sync_with_stdio(false);
        cin.tie(NULL);
        cout.tie(NULL);

        int n = nums1.size();
        unordered_map<int, int> um;
        for (int i = 0; i < n; ++i) {
        	um[nums2[i]] = i;
        }

        vector<long long> d(n, 0), f(n, 0);
        SegmentTreee t1(n);
        for (int i = 0; i < n - 1; ++i) {
        	int pos = um[nums1[i]] + 1;
        	if (i == 0) {
        		t1.add(pos, 1);
        		continue;
        	}
        	else {
        		d[i] = t1.rangeQuery(1, pos - 1);
        		t1.add(pos, 1);
        	}
        }

        fill(t1.tree.begin(), t1.tree.end(), 0);
        for (int i = n - 1; i > 0; --i) {
        	int pos = um[nums1[i]] + 1;
        	if (i == n - 1) {
        		t1.add(pos, 1);
        	}
        	else {
        		d[i] = t1.rangeQuery(pos + 1, n);
        		t1.add(pos, 1);
        	}
        }

        long long res = 0;
        for (int i = 0; i < n; ++i) {
        	res += d[i] * f[i];
        }

        return res;
    }
};
