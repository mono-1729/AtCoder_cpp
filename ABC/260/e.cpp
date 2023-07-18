#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(int i = a; i < n; i++)
#define rrep(i, a, n) for(int i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

int gcd(int a, int b){
	if(a%b == 0){
	  return b;
	}else{
	  return gcd(b, a%b);
	}
}

int lcm(int a, int b){
	return a*b / gcd(a, b);
}

ll powMod(ll x, ll n) {
	if (n == 0) return 1 % MOD;
	ll val = powMod(x, n / 2);
	val *= val;
	if (n % 2 == 1) val *= x;
	return val % MOD;
}

int main() {
  int n,m;
  cin >> n >> m;
  vector<int> a(n), b(n);
  rep(i,0,n) cin >> a[i] >> b[i];
  vector<vector<int>> inv(m + 1);
  rep(i,0,n) {
    inv[a[i]].push_back(i);
    inv[b[i]].push_back(i);
  }
  vector<int> cnt(n), ans(m + 3);
  int cnt_zero = n;
  for (int i = 1, j = 1; i <= m;i++) {
    while (j <= m and cnt_zero != 0) {
      for (auto& x : inv[j]) {
        if (cnt[x] == 0) cnt_zero--;
        cnt[x]++;
      }
      j++;
    }
    if (cnt_zero != 0) break;
    ans[j - i]++, ans[m+ 1 - i + 1]--;
    for (auto& x : inv[i]) {
      cnt[x]--;
      if (cnt[x] == 0) cnt_zero++;
    }
  }
  for (int i = 1; i <= m; i++) {
    ans[i] += ans[i - 1];
    cout << ans[i] << " \n"[i == m];
  }
}