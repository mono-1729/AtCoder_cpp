#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;


vector<int> Z_algorithm(string S) {
	int c = 0, n = S.size();
	vector<int> Z(n, 0);
	for (int i = 1; i < n; i++) {
		int l = i - c;
		if (i + Z[l] < c + Z[c]) {
			Z[i] = Z[l];
		}
		else {
			int j = max(0, c + Z[c] - i);
			while (i + j < n && S[j] == S[i + j])j++;
			Z[i] = j;
			c = i;
		}
	}
	Z[0] = n;
	return Z;
}