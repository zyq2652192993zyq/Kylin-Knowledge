#include <bits/stdc++.h>

using namespace std;

vector<string> seq;


int main()
{
	std::ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	string line;
	while (getline(cin, line)) {
		seq.push_back(line);
	}

	sort(seq.begin(), seq.end());
	int n = seq.size();
	for (int i = 0; i < n; ++i) {
		int len = seq[i].size();
		
		cout << seq[i].substr(0, len - 3) << ": ";
		cout << "Algorithm/LeetCode/" << seq[i] << endl;
	}

	return 0;
}