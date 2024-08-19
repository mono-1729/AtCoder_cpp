#include <bits/stdc++.h>
#include <unordered_map>
#include <stdlib.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <atcoder/all>
using namespace atcoder;
using namespace boost::multiprecision;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint998244353;

ll gcd(ll a, ll b){
    if(a%b == 0){
      return b;
    }else{
      return gcd(b, a%b);
    }
}

ll lcm(ll a, ll b){
    return a*b / gcd(a, b);
}

ll powMod(ll x, ll n) {
    if (n == 0) return 1 % MOD;
    ll val = powMod(x, n / 2);
    val *= val;
    val %= MOD;
    if (n % 2 == 1) val *= x;
    return val % MOD;
}

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

int main() {
    string s, t; cin >> s >> t;
    ll n = s.size(), m = t.size();
    string ts = string(6000000,'a');
    rep(i,0,3000000) ts[i] = t[i%m], ts[i+3000000] = s[i%n];
    vector<int> vec = Z_algorithm(ts);
    ll num1 = 0, num2 = 0;
    rep(i,3000000,4500000) chmax(num1,vec[i]/m);
    rep(i,4500000,6000000) chmax(num2,vec[i]/m);
    if(num1 != num2) cout << -1 << endl;
    else cout << num1 << endl;
    return 0;
}