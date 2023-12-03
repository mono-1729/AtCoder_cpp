#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
template <typename X>
struct SegTree {
	using FX = function<X(X, X)>; // X•X -> X となる関数の型
	ll n;
	FX fx;
	const X ex;
	vector<X> dat;
	SegTree(ll n_, FX fx_, X ex_) : n(), fx(fx_), ex(ex_), dat(n_ * 4, ex_) {
		ll x = 1;
		while (n_ > x) {
			x *= 2;
		}
		n = x;
	}
	void set(ll i, X x) { dat[i + n - 1] = x; }
	void build() {
		for (ll k = n - 2; k >= 0; k--) dat[k] = fx(dat[2 * k + 1], dat[2 * k + 2]);
	}
	void update(ll i, X x) {
		i += n - 1;
		dat[i] = x;
		while (i > 0) {
			i = (i - 1) / 2;  // parent
			dat[i] = fx(dat[i * 2 + 1], dat[i * 2 + 2]);
		}
	}
	X query(ll a, ll b) { return query_sub(a, b, 0, 0, n); }
	X query_sub(ll a, ll b, ll k, ll l, ll r) {
		if (r <= a || b <= l) {
			return ex;
		} else if (a <= l && r <= b) {
			return dat[k];
		} else {
			X vl = query_sub(a, b, k * 2 + 1, l, (l + r) / 2);
			X vr = query_sub(a, b, k * 2 + 2, (l + r) / 2, r);
			return fx(vl, vr);
		}
	}
};


constexpr int B = 5;
int mod[B] = {998244353, 1000000007, 1000000009, 1000000021, 1000000033};
int base[B];
struct Hash {
  long long h1, pw;
};
using T = array<Hash, B>;
T op(T lhs, T rhs) {
  T res;
  for (int i = 0; i < B; i++) {
    res[i].h1 = (lhs[i].h1 * rhs[i].pw + rhs[i].h1) % mod[i];
    res[i].pw = lhs[i].pw * rhs[i].pw % mod[i];
  }
  return res;
}
T e() {
  T res;
  for (int i = 0; i < B; i++) res[i] = {0, 1};
  return res;
}
T gen(char c) {
  T res;
  for (int i = 0; i < B; i++) res[i].h1 = c, res[i].pw = base[i];
  return res;
}

int main() {
	mt19937_64 rng(time(0));
	for (int i = 0; i < B; i++) base[i] = rng() % mod[i];
	ll n,q;cin>>n>>q;
	string s;cin>>s;
	vector<T> init1(n),init2(n);
	for (int i = 0; i < n; i++){
		init1[i] = gen(s[i]);
		init2[n-i-1] = gen(s[i]);
	}
	SegTree<T> seg1(init1.size(), op, e());
	SegTree<T> seg2(init2.size(), op, e());
	for(int i = 0; i < n; i++){
		seg1.set(i, init1[i]);
		seg2.set(i, init2[i]);
	}
	seg1.build();
	seg2.build();
	return 0;
}

// struct Hash {
//   long long h1, h2, pw;
// };
// using T = array<Hash, B>;
// T op(T lhs, T rhs) {
//   T res;
//   for (int i = 0; i < B; i++) {
//     res[i].h1 = (lhs[i].h1 * rhs[i].pw + rhs[i].h1) % mod[i];
//     res[i].h2 = (lhs[i].h2 + lhs[i].pw * rhs[i].h2) % mod[i];
//     res[i].pw = lhs[i].pw * rhs[i].pw % mod[i];
//   }
//   return res;
// }
// T e() {
//   T res;
//   for (int i = 0; i < B; i++) res[i] = {0, 0, 1};
//   return res;
// }
// using SegTree = atcoder::segtree<T, op, e>;
// T gen(char c) {
//   T res;
//   for (int i = 0; i < B; i++) res[i].h1 = res[i].h2 = c, res[i].pw = base[i];
//   return res;
// }