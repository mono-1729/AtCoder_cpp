#include <bits/stdc++.h>
#include <stdlib.h>
using namespace std;
#define rep(i, a, n) for(int i = a; i < n; i++)
#define ll long long
constexpr ll MOD = 998244353;
int maxnum=200005;
vector<ll> fac(maxnum), inv(maxnum), finv(maxnum);
void init_fac(){
	fac[0] = fac[1] = 1;
	inv[1] = 1;
	finv[0] = finv[1] = 1;
	rep(i, 2, maxnum){
		fac[i] = fac[i-1]*i%MOD;
		inv[i] = MOD-MOD/i*inv[MOD%i]%MOD;
		finv[i] = finv[i-1]*inv[i]%MOD;
	}
}
ll nCr(ll n, ll r){
	if(n < 0 or n-r < 0 or r < 0) return 0;
	return fac[n]*(finv[n-r]*finv[r]%MOD)%MOD;
}
ll nHr(ll n, ll r){
	return nCr(n+r-1, r);
}

std::vector<std::vector<long long>> comb(int n, int r) {
  std::vector<std::vector<long long>> v(n + 1,std::vector<long long>(n + 1, 0));
  for (int i = 0; i < v.size(); i++) {
    v[i][0] = 1;
    v[i][i] = 1;
  }
  for (int j = 1; j < v.size(); j++) {
    for (int k = 1; k < j; k++) {
      v[j][k] = (v[j - 1][k - 1] + v[j - 1][k]);
    }
  }
  return v;
}
