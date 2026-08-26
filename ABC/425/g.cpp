#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <stdlib.h>
#include <atcoder/all>
using namespace atcoder;
using namespace std;
#define rep(i, a, n) for(ll i = a; i < n; i++)
#define rrep(i, a, n) for(ll i = a; i >= n; i--)
#define inr(l, x, r) (l <= x && x < r)
#define ll long long
#define ld long double
#define pii pair<int, int>
#define pll pair<ll, ll>
#define all(x) (x).begin(), (x).end()
//constexpr ll MOD = 1000000007;
constexpr ll MOD = 998244353;
constexpr int IINF = 1001001001;
constexpr ll INF = 1LL<<60;
template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

using mint = modint998244353;

int main() {
    ll n, m; cin >> n >> m;
    vector<ll> a(n);
    rep(i,0,n) cin >> a[i];
    auto f = [&](auto f,vector<ll>& b, ll ma, ll k) -> ll {
        if(k == 0) return 0;
        vector<vector<ll>> bb(2);
        ll bit = 1LL<<(k-1);

        for(auto x: b){
            ll y = (x>>(k-1))&1;
            bb[y].push_back(x^(y<<(k-1)));
        }
        ll mid = bit;

        if(ma == bit*2){
            if(bb[0].size() && bb[1].size()) return f(f,bb[0],mid,k-1)+f(f,bb[1],mid,k-1);
            return 2*f(f,b,mid,k-1)+mid*mid;
        }
        if(ma <= mid){
            if(bb[0].size()) return f(f,bb[0],ma,k-1);
            else return f(f,bb[1],ma,k-1)+ma*mid;
        }
        ll ans = 0;
        if(bb[0].size()) ans += f(f,bb[0],mid,k-1);
        else ans += f(f,bb[1],mid,k-1)+mid*mid;
        if(bb[1].size()) ans += f(f,bb[1],ma-mid,k-1);
        else ans += f(f,bb[0],ma-mid,k-1)+(ma-mid)*mid;

        return ans;
    };
    cout << f(f,a,m,30) << endl;
    return 0;
}